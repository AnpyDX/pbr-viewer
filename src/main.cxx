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

#include "core/shader.h"
#include "core/vertexbuffer.h"
#include "core/indexbuffer.h"
#include "core/texture.h"
#include "core/framebuffer.h"

#include "Camera.h"
#include "SceneManager.h"

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

        app_window = glfwCreateWindow(1920, 1080, "PBR Viewer", nullptr, nullptr);
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

        glfwSwapInterval(false); // enable v-sync
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
        // create shader object
        app_shader = load_shader("assets/shaders/universal_soild.shader");

        // create scene & load models
        app_scene = std::make_unique<PBRV::SceneManager>();
        app_scene->add_mesh(
            PBRV::Model::Builder()
            .from_file("assets/models/WaterBottle/WaterBottle.gltf")
        );
        
        // create camera
        app_camera = std::make_unique<PBRV::Camera>(mas::vec3(0.0, 0.0, 2.0), mas::vec3(0.0, 0.0, -2.0), mas::vec3(0.0, 1.0, 0.0));

    }

    void prepare_postprocess() {
        std::vector<VertexType> square_vertices = {
            { { 1.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
            { { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
            { { -1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
            { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } }
        };
        std::vector<unsigned int> square_indices = { 0, 1, 2, 2, 3, 0 };
        
        PBRV::VertexBufferInfo vb_info{};
        vb_info.set_buffer(square_vertices.data(), square_vertices.size() * sizeof(VertexType))
                .add_attribute(0, 3, GL_FLOAT, GL_FALSE, 20, 0)
                .add_attribute(1, 2, GL_FLOAT, GL_FALSE, 20, 12);
        pp_square_vb = std::make_unique<PBRV::VertexBuffer>(vb_info);

        pp_square_ib = std::make_unique<PBRV::IndexBuffer>(square_indices.data(), square_indices.size() * sizeof(unsigned int), square_indices.size());

        pp_present_shader = load_shader("assets/shaders/frame_present.shader");
        pp_blur_shader = load_shader("assets/shaders/gaussian_blur.shader");

        create_framebuffer_resource(1920, 1080);
    }

    void main_loop() {  
        float time_ticker = 0;
        int max_gui_blur_times = 2;

        while (!glfwWindowShouldClose(app_window)) {
            auto current_time = static_cast<float>(glfwGetTime());
            float delta_time = current_time - time_ticker;
            frame_per_second = 1.0f / delta_time;
            time_ticker = current_time;

            detect_input(delta_time);

            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);
            glDepthFunc(GL_LESS);
            glDisable(GL_STENCIL_TEST);

            /** Draw Scene */
            pp_framebuffer1->bind();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glStencilMask(0xFF);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            int w, h;
            glfwGetWindowSize(app_window, &w, &h);
            mas::mat4 model(1.0f);
            model = mas::translate(model, mas::vec3(0.0, 0.0, -2));
            model = mas::scale(model, mas::vec3(5.0));
            // model = mas::rotate(model, mas::vec3(0.0f, 0.0f, 1.0f), glfwGetTime());
            mas::mat4 view = app_camera->get_lookat();
            mas::mat4 projection = mas::perspective(45.0f, static_cast<float>(w)/static_cast<float>(h), 0.001f, 100.0f);
            
            app_shader->use();
            app_shader->set_mat4("PBRV_Transform_Model", model);
            app_shader->set_mat4("PBRV_Transform_View", view);
            app_shader->set_mat4("PBRV_Transform_Projection", projection);

            app_scene->render(app_shader.get(), pp_framebuffer1.get());

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
            PBRV::Framebuffer::bind_default();
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

    void detect_input(float delta_time) {
        if (glfwGetKey(app_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(app_window, true);
        }

        mas::vec2 camera_movement(0.0f);
        if (glfwGetKey(app_window, GLFW_KEY_W) == GLFW_PRESS) {
            camera_movement.y += 1.0f;
        }

        if (glfwGetKey(app_window, GLFW_KEY_S) == GLFW_PRESS) {
            camera_movement.y -= 1.0f;
        }

        if (glfwGetKey(app_window, GLFW_KEY_A) == GLFW_PRESS) {
            camera_movement.x -= 1.0f;
        }

        if (glfwGetKey(app_window, GLFW_KEY_D) == GLFW_PRESS) {
            camera_movement.x += 1.0f;
        }

        camera_movement = mas::normalize(camera_movement) * camera_speed * delta_time;
        app_camera->position_controller(camera_movement.y, camera_movement.x);

        if (glfwGetMouseButton(app_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!ImGui::IsAnyItemActive()) {
                glfwSetInputMode(app_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            
                double xpos, ypos;
                glfwGetCursorPos(app_window, &xpos, &ypos);
                if (!mouse_press_released) {
                    mas::vec2 view_offset(xpos - last_mouse_pos.x, last_mouse_pos.y - ypos);
                    view_offset = view_offset * camera_sensivity * delta_time;
                    app_camera->view_controller(view_offset.x, view_offset.y);
                }
                else {
                    mouse_press_released = false;
                }

                last_mouse_pos.x = static_cast<float>(xpos);
                last_mouse_pos.y = static_cast<float>(ypos);
            }
        }
        else {
            glfwSetInputMode(app_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouse_press_released = true;
        }
    }

    static std::unique_ptr<PBRV::Shader> load_shader(const std::string& path) {
        PBRV::UConsole::debug("loading shader: " + path);
        std::fstream shader_file {};
        shader_file.exceptions(std::ifstream::badbit);
        shader_file.open(path);
        if (!shader_file.is_open()) {
            throw std::runtime_error("failed to open shader: " + path + "!");
        }

        return std::move(std::make_unique<PBRV::Shader>(shader_file));
    }

    void recreate_framebuffers(int width, int height) {
        destroy_framebuffer_resource();
        create_framebuffer_resource(width, height);
    }

    void create_framebuffer_resource(int width, int height) {
        PBRV::TextureInfo frame_tex_info {};
        frame_tex_info.wrap_s = GL_MIRRORED_REPEAT;
        frame_tex_info.wrap_t = GL_MIRRORED_REPEAT;

        pp_color_attach1 = std::make_unique<PBRV::Texture>(frame_tex_info, width, height);
        pp_color_attach2 = std::make_unique<PBRV::Texture>(frame_tex_info, width, height);

        pp_framebuffer1 = std::make_unique<PBRV::Framebuffer>(pp_color_attach1->get_id());
        pp_framebuffer2 = std::make_unique<PBRV::Framebuffer>(pp_color_attach2->get_id());

        glGenRenderbuffers(1, &pp_shared_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, pp_shared_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        pp_framebuffer1->bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pp_shared_rbo);
        pp_framebuffer2->bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pp_shared_rbo);
        PBRV::Framebuffer::bind_default();
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

        // profiler
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(8, 8), ImGuiCond_None);
        ImGui::SetNextWindowSize(ImVec2(180, 142), ImGuiCond_None);
        {
            ImGuiWindowFlags profiler_window_flags = 0;
            profiler_window_flags |= ImGuiWindowFlags_NoMove;
            profiler_window_flags |= ImGuiWindowFlags_NoTitleBar;
            profiler_window_flags |= ImGuiWindowFlags_NoResize;

            bool pop_window = true;

            ImGui::Begin("profiler", &pop_window, profiler_window_flags);
            ImGui::Text("@profiler");
            ImGui::Text("OpenGL %s", backend_version.c_str());
            ImGui::Text("GPU: %s", gpu_info.c_str());
            ImGui::Text("FPS: %i", static_cast<int>(frame_per_second));

            static float values[90] = {};
            static int values_offset = 0;
            static double refresh_time = 0.0;
            while (refresh_time < ImGui::GetTime())
            {
                values[values_offset] = frame_per_second;
                values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
                refresh_time += 1.0f / 60.0f;
            }

            ImGui::PlotLines("avg", values, IM_ARRAYSIZE(values), values_offset, nullptr, 0.0f, FLT_MAX, ImVec2(0.0f, 30.0f));
            ImGui::End();
        }

        PBRV::render_imgui(frame_only);
    }

private:
    GLFWwindow* app_window = nullptr;

    // drawing resources
    std::unique_ptr<PBRV::Shader> app_shader;
    std::unique_ptr<PBRV::SceneManager> app_scene;

    // post-process resources
    std::unique_ptr<PBRV::Shader> pp_present_shader;
    std::unique_ptr<PBRV::Shader> pp_blur_shader;
    std::unique_ptr<PBRV::VertexBuffer> pp_square_vb;
    std::unique_ptr<PBRV::IndexBuffer> pp_square_ib;

    std::unique_ptr<PBRV::Texture> pp_color_attach1;
    std::unique_ptr<PBRV::Texture> pp_color_attach2;
    std::unique_ptr<PBRV::Framebuffer> pp_framebuffer1;
    std::unique_ptr<PBRV::Framebuffer> pp_framebuffer2 = nullptr;
    GLuint pp_shared_rbo = 0;

    // application resouces
    std::string backend_version {};
    std::string gpu_info {};
    float frame_per_second = 0;

    std::shared_ptr<PBRV::Camera> app_camera;
    float camera_speed = 0.5f;
    float camera_sensivity = 1.0f;
    bool mouse_press_released = true;
    mas::vec2 last_mouse_pos {0.0f};
};

int main() {
    int exit_success = 0;

    try {
        PBRViewerApplication application{};
    }
    catch (const std::exception& e) {
        PBRV::UConsole::warning(e.what());
        exit_success = -1;
    }

    return exit_success;
}