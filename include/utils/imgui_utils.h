/**
 * @file imgui_utils.h
 * @brief IMGUI Utility
 */

#pragma once
#include <string>
#include <vector>
#include <sstream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <fontcpp/IconsFontAwesome6.h>

#include <GLFW/glfw3.h>

namespace PBRV {
    static void setup_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsRocky();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");

    // replace default font to Font Awesome
    float baseFontSize = 16.0f;
    float iconFontSize = baseFontSize * 2.0f / 3.0f;
    ImFont* font = io.Fonts->AddFontFromFileTTF("assets/fonts/consolab.ttf", baseFontSize, nullptr, io.Fonts->GetGlyphRangesChineseFull());

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig icons_config; 
    icons_config.MergeMode = true; 
    icons_config.PixelSnapH = true; 
    icons_config.GlyphMinAdvanceX = iconFontSize;
    std::string icon_font_path = "assets/fonts/" FONT_ICON_FILE_NAME_FAS;
    io.Fonts->AddFontFromFileTTF(icon_font_path.c_str(), iconFontSize, &icons_config, icons_ranges );
    }

    static void begin_imgui_frame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    static void render_imgui(bool frame_only) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData(), frame_only);
    }

    static void clean_imgui() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    static std::string split_by_count(std::string in_str, int count) {
        std::string out_string{};
        int counter = 0;
        for (auto c : in_str) {
            if (counter == count) {
                out_string.append("\n");
                counter = 0;
            }
            out_string.append(std::string(1, c));
            counter++;
        }

        return out_string;
    }

    static std::vector<std::string> split_by_blank(const char *cstr) {
        std::vector<std::string> result{};

        std::stringstream ss;
        ss << cstr;
        std::string temp_s;
        while (ss >> temp_s) {
            result.push_back(temp_s);
        }

        return result;
    }
}
