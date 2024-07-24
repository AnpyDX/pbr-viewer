#define MAS_UTYPE_FLOAT
#include <stdexcept>
#include <fstream>
#include <string>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <mas/mas.hpp>

#include "utils/console.h"
#include "utils/imgui_utils.h"
#include "utils/ticker.h"

#include "core/shader.h"
#include "core/vertexbuffer.h"
#include "core/indexbuffer.h"
#include "core/texture.h"
#include "core/framebuffer.h"

#include "Camera.h"
#include "SceneManager.h"

// default app settings
constexpr uint32_t DEFAULT_WIDTH = 1920;
constexpr uint32_t DEFAULT_HEIGHT = 1080;
constexpr float    DEFAULT_MAX_FPS = 60.0f;
// -------------------

constexpr float MIN_DELTATIME = 1.0f / DEFAULT_MAX_FPS;

struct VertexType {
    mas::vec3 position;
    mas::vec2 texCoord;
};

class PBRViewerApplication {
public:
    PBRViewerApplication() {
        init_window();
        create_resource();
        prepare_postprocess();
        main_loop();
    }

    ~PBRViewerApplication() {
        PBRV::clean_imgui();

        glDeleteRenderbuffers(1, &pp_shared_rbo);

        if (app_window) {
            glfwTerminate();
            app_window = nullptr;
        }
    }
    
private:
    /* Main Application Functions */
    void init_window() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        app_window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "PBR Viewer", nullptr, nullptr);
        if (app_window == nullptr) {
            glfwTerminate();
            throw std::runtime_error("failed to create window!");
        }
        glfwMakeContextCurrent(app_window);
        glfwSetFramebufferSizeCallback(app_window, framebuffer_resize_callback);

        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            glfwTerminate();
            throw std::runtime_error("failed to initialize GLAD!");
        }

        glfwSwapInterval(false);
        glfwSetWindowUserPointer(app_window, reinterpret_cast<void*>(this));

        // get profiler information
        const GLubyte *temp_glubv;
        std::vector<std::string> temp_str_vector{};
        temp_glubv = glGetString(GL_VERSION);
        temp_str_vector = PBRV::split_by_blank(reinterpret_cast<const char*>(temp_glubv));
        backend_version = temp_str_vector[0] + " " + temp_str_vector[1];
        temp_glubv = glGetString(GL_RENDERER);
        gpu_info = std::string(reinterpret_cast<const char*>(temp_glubv));
        gpu_info = PBRV::split_by_count(gpu_info, 11);

        PBRV::setup_imgui(app_window);
    }

    void create_resource() {
        app_scene = std::make_unique<PBRV::SceneManager>();

        app_scene->new_shader("default", "assets/shaders/universal_soild.shader");

        app_scene->new_model(
            "model1",
            PBRV::Model::Builder()
            .from_file("assets/models/WaterBottle/WaterBottle.gltf")
            .build(),
            "default",
            PBRV::Transform {
                .translate = mas::vec3(0.0, 0.0, -1.0),
                .scale = mas::vec3(0.5f),
            }
        );
        
        // create camera
        app_camera = std::make_unique<PBRV::Camera>(
            app_window,
            mas::vec3(0.0, 0.0, 0.0), 
            mas::vec3(0.0, 0.0, -2.0), 
            mas::vec3(0.0, 1.0, 0.0)
        );

        app_camera->speed = 0.4f;
        app_camera->sensitivity = 1.0f;
    }

    void prepare_postprocess() {
        std::vector<VertexType> square_vertices = {
            { { 1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
            { { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
            { { -1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
            { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } }
        };
        std::vector<unsigned int> square_indices = { 0, 1, 2, 2, 3, 0 };
        
        PBRV::Core::VertexBufferInfo vb_info{};
        vb_info.set_buffer(square_vertices.data(), square_vertices.size() * sizeof(VertexType))
                .add_attribute(0, 3, GL_FLOAT, GL_FALSE, 20, 0)
                .add_attribute(1, 2, GL_FLOAT, GL_FALSE, 20, 12);
        pp_square_vb = std::make_unique<PBRV::Core::VertexBuffer>(vb_info);

        pp_square_ib = std::make_unique<PBRV::Core::IndexBuffer>(square_indices.data(), square_indices.size() * sizeof(unsigned int), square_indices.size());

        pp_present_shader = load_shader("assets/shaders/frame_present.shader");
        pp_blur_shader = load_shader("assets/shaders/gaussian_blur.shader");

        create_framebuffer_resource(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }

    void main_loop() {  
        float time_ticker = 0;

        while (!glfwWindowShouldClose(app_window)) {

            auto current_time = static_cast<float>(glfwGetTime());
            float delta_time = current_time - time_ticker;
            if (delta_time < MIN_DELTATIME) continue;
            fps_ticker.set_tick(1.0f / delta_time);
            time_ticker = current_time;

            detect_input();

            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);
            glDepthFunc(GL_LESS);
            glDisable(GL_STENCIL_TEST);

            /** Draw Scene */
            pp_framebuffer1->bind();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glStencilMask(0xFF);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            app_scene->render(app_camera.get(), pp_framebuffer1.get());

            /** Post-Process */
            // clear all depth & stencil info generated by stage "Draw Scene"
            glDisable(GL_DEPTH_TEST);
            glStencilMask(0xFF);
            glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            // copy color_buffer from fb1 to fb2
            pp_framebuffer2->bind();
            glClear(GL_COLOR_BUFFER_BIT);

            pp_present_shader->use();
            pp_color_attach1->bind_sampler(GL_TEXTURE1);
            pp_present_shader->set_int("frame_tex", 1);

            pp_square_vb->bind();
            pp_square_ib->bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // get gui frame stencil info
            glEnable(GL_STENCIL_TEST);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            draw_gui(true);

            // blur gui background
            glStencilMask(0x00);
            glStencilFunc(GL_EQUAL, 1, 0xFF);

            int max_gui_blur_times = ui_context.enable_blur ? 200 : 2;
            for (int i = 1; i < max_gui_blur_times + 1; i++) {
                if (i & 2) {
                    pp_framebuffer1->bind();
                    pp_blur_shader->use();
                    pp_color_attach2->bind_sampler(GL_TEXTURE1);
                    pp_blur_shader->set_int("frame_texture", 1);
                    pp_blur_shader->set_bool("is_horizontal", false);
                }
                else {
                    pp_framebuffer2->bind();
                    pp_blur_shader->use();
                    pp_color_attach1->bind_sampler(GL_TEXTURE1);
                    pp_blur_shader->set_int("frame_texture", 1);
                    pp_blur_shader->set_bool("is_horizontal", true);
                }

                pp_square_vb->bind();
                pp_square_ib->bind();
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            
            /* Present */
            PBRV::Core::Framebuffer::bind_default();
            glDisable(GL_STENCIL_TEST);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            pp_present_shader->use();
            pp_color_attach1->bind_sampler(GL_TEXTURE1);
            pp_present_shader->set_int("frame_texture", 1);

            pp_square_vb->bind();
            pp_square_ib->bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            draw_gui(false);

            glfwSwapBuffers(app_window);
            glfwPollEvents();
        }
    }

private:
    /* Utils Functions */
    static void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
        // resize viewport
        glViewport(0, 0, width, height);
        
        // recreate all framebuffer resources
        auto app_ptr = reinterpret_cast<PBRViewerApplication*>(glfwGetWindowUserPointer(window));
        app_ptr->recreate_framebuffers(width, height);
    }

    void detect_input() {
        if (glfwGetKey(app_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(app_window, true);
        }

        if (PBRV::UGetOnceKey<0>(ImGuiKey_M)) {
            ui_context.draw_inspector = !ui_context.draw_inspector;
        }

        app_camera->update_input(std::clamp(1.0f / fps_ticker.get_avg(), 0.00001f, 1.0f));
    }

    static std::unique_ptr<PBRV::Core::Shader> load_shader(const std::string& path) {
        PBRV::UConsole::debug("loading shader: " + path);
        std::fstream shader_file {};
        shader_file.exceptions(std::ifstream::badbit);
        shader_file.open(path);
        if (!shader_file.is_open()) {
            throw std::runtime_error("failed to open shader: " + path + "!");
        }

        return std::move(std::make_unique<PBRV::Core::Shader>(shader_file));
    }

    void recreate_framebuffers(int width, int height) {
        destroy_framebuffer_resource();
        create_framebuffer_resource(width, height);
    }

    void create_framebuffer_resource(int width, int height) {
        PBRV::Core::TextureInfo frame_tex_info {};
        frame_tex_info.wrap_s = GL_MIRRORED_REPEAT;
        frame_tex_info.wrap_t = GL_MIRRORED_REPEAT;

        pp_color_attach1 = std::make_unique<PBRV::Core::Texture>(frame_tex_info, width, height);
        pp_color_attach2 = std::make_unique<PBRV::Core::Texture>(frame_tex_info, width, height);

        pp_framebuffer1 = std::make_unique<PBRV::Core::Framebuffer>(pp_color_attach1->get_id());
        pp_framebuffer2 = std::make_unique<PBRV::Core::Framebuffer>(pp_color_attach2->get_id());

        glGenRenderbuffers(1, &pp_shared_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, pp_shared_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        pp_framebuffer1->bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pp_shared_rbo);
        pp_framebuffer2->bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pp_shared_rbo);
        PBRV::Core::Framebuffer::bind_default();
    }

    void destroy_framebuffer_resource() {
        pp_framebuffer1.reset();
        pp_framebuffer2.reset();
        pp_color_attach1.reset();
        pp_color_attach2.reset();
        glDeleteRenderbuffers(1, &pp_shared_rbo);
    }

    void draw_gui(bool frame_only) {
        PBRV::begin_imgui_frame();

        ImGui::ShowDemoWindow();

        if (ui_context.draw_inspector)
            DIMGUI_Inspector();

        if (ui_context.draw_profiler)
            DIMGUI_Profiler();

        if (ui_context.draw_settigs)
            DIMGUI_SettingsWindow();
        
        PBRV::render_imgui(frame_only);
    }

    void DIMGUI_Inspector() {

        ImGui::SetNextWindowPos(ImVec2(8, 156), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(488, 525), ImGuiCond_Once);
        if (!ImGui::Begin("inspector", nullptr, ImGuiWindowFlags_MenuBar)) {
            ImGui::End();
            return;
        }

        {
            PBRV::UIDTicker btn_ticker {};
        
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("Menu")) {

                    if (ImGui::MenuItem("Open (.scene)")) {
                        std::cout << "open scene" << std::endl;
                    }

                    if (ImGui::MenuItem("Settings")) {
                        ui_context.draw_settigs = true;
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Exit", "Esc")) {
                        glfwSetWindowShouldClose(app_window, true);
                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("New")) {

                    ImGui::SeparatorText("Resources");
                    if (ImGui::MenuItem("Shader")) {}

                    ImGui::SeparatorText("Node objects");
                    if (ImGui::MenuItem("Model")) {}
                    if (ImGui::MenuItem("Light")) {}
                    if (ImGui::MenuItem("Skybox")) {}

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            if (ImGui::BeginTabBar("##tab")) {
                if (ImGui::BeginTabItem("Scene", nullptr, ImGuiTabItemFlags_None)) {
                    if (ImGui::BeginTable("##scene_split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
                    {
                        ImGui::TableSetupScrollFreeze(0, 1);
                        ImGui::TableSetupColumn("Nodes");
                        ImGui::TableSetupColumn("Attributes");
                        ImGui::TableHeadersRow();

                        

                        ImGui::EndTable();
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Resources", nullptr, ImGuiTabItemFlags_None)) {
                    ImGui::SeparatorText("Shaders");
                    
                    for (auto& shader_object : app_scene->shaders) {
                        ImGui::PushID(btn_ticker.get());

                        ImGui::BulletText("%s", shader_object.first.c_str());
                        ImGui::SameLine();
                        ImGui::TextDisabled("-> %s", shader_object.second.path.c_str());

                        if (ImGui::Button("reload")) {
                            app_scene->new_shader(shader_object.first, shader_object.second.path, true);
                        }

                        ImGui::SameLine();
                        if (ImGui::Button("delete")) {
                            std::cout << shader_object.first << std::endl;
                            app_scene->remove_shader(shader_object.first);
                            ImGui::PopID();
                            break;
                        }

                        ImGui::Separator();

                        ImGui::PopID();
                    }

                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        
        }
        ImGui::End();
    }

    void DIMGUI_Profiler() {
        ImGui::SetNextWindowPos(ImVec2(8, 8), ImGuiCond_None);
        ImGui::SetNextWindowSize(ImVec2(180, 142), ImGuiCond_None);
        ImGuiWindowFlags profiler_window_flags = 0;
        profiler_window_flags |= ImGuiWindowFlags_NoMove;
        profiler_window_flags |= ImGuiWindowFlags_NoTitleBar;
        profiler_window_flags |= ImGuiWindowFlags_NoResize;

        if(!ImGui::Begin("profiler", nullptr, profiler_window_flags)) {
            ImGui::End();
            return;
        }

        {
            ImGui::Text("@profiler");
            ImGui::Text("OpenGL %s", backend_version.c_str());
            ImGui::Text("GPU: %s", gpu_info.c_str());
            ImGui::Text("FPS: %i", static_cast<int>(fps_ticker.get_avg()));

            static float values[90] = {};
            static int values_offset = 0;
            static double refresh_time = 0.0;
            while (refresh_time < ImGui::GetTime())
            {
                values[values_offset] = fps_ticker.get_avg();
                values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
                refresh_time += 1.0f / 60.0f;
            }

            ImGui::PlotLines("avg", values, IM_ARRAYSIZE(values), values_offset, nullptr, 0.0f, FLT_MAX, ImVec2(0.0f, 30.0f));
        }
        ImGui::End();
    }

    void DIMGUI_SettingsWindow() {
        ImGui::SetNextWindowSize(ImVec2(488, 525), ImGuiCond_Once);
        if (!ImGui::Begin("settings", &ui_context.draw_settigs)) {
            ImGui::End();
            return;
        }

        {
            if(!ImGui::CollapsingHeader("General")) {
                if (ImGui::BeginTable("general_split", 2))
                {
                    ImGui::TableNextColumn(); ImGui::Checkbox("enable profiler", &ui_context.draw_profiler);
                    ImGui::TableNextColumn(); ImGui::Checkbox("enable window blur", &ui_context.enable_blur);
                    ImGui::EndTable();
                }
            }

            if (!ImGui::CollapsingHeader("Rendering")) {

            }
        }
        ImGui::End();
    }

    void DIMGUI_DrawNodeModel() {

    }

private:
    GLFWwindow* app_window = nullptr;

    // drawing resources
    std::unique_ptr<PBRV::SceneManager> app_scene;
    std::shared_ptr<PBRV::Camera> app_camera;

    // post-process resources
    std::unique_ptr<PBRV::Core::Shader> pp_present_shader;
    std::unique_ptr<PBRV::Core::Shader> pp_blur_shader;
    std::unique_ptr<PBRV::Core::VertexBuffer> pp_square_vb;
    std::unique_ptr<PBRV::Core::IndexBuffer> pp_square_ib;

    std::unique_ptr<PBRV::Core::Texture> pp_color_attach1;
    std::unique_ptr<PBRV::Core::Texture> pp_color_attach2;
    std::unique_ptr<PBRV::Core::Framebuffer> pp_framebuffer1;
    std::unique_ptr<PBRV::Core::Framebuffer> pp_framebuffer2;
    GLuint pp_shared_rbo = 0;

    // application resouces
    std::string backend_version {};
    std::string gpu_info {};
    PBRV::UFPSTicker<64> fps_ticker {};

    struct {
        bool draw_inspector = true;
        bool draw_profiler = true;
        bool draw_settigs = false;
        bool enable_blur = true;
    } ui_context {};
};

int main() {
    try {
        PBRViewerApplication application{};
    }
    catch (const std::exception& e) {
        PBRV::UConsole::warning(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}