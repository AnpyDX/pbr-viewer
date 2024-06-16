-- "PBR Viewer Project"

-- general config
add_rules("mode.debug", "mode.release")
set_languages("c++17")

-- packages list
add_requires("glfw 3.4")
add_requires("glad 0.1.36")
add_requires("nlohmann_json 3.11.3")
add_requires("stb 2023.12.15")

-- local libraries targets
target("bmx")
    set_kind("static")
    add_files("thirdparty/bmx/src/bmx.cpp")
    add_includedirs("thirdparty/bmx/include", { public = true })

target("imgui")
    set_kind("static")
    add_files("thirdparty/imgui/include/imgui/*.cpp")
    add_includedirs("thirdparty/imgui/include", { public = true })
    add_packages("glfw")

-- project binary target
target("PBRV")
    set_kind("binary")

    add_files(
        "src/main.cxx",
        "include/*.cxx",
        "include/core/*.cxx")

    add_includedirs(
        "include",
        "thirdparty/mas/include",
        "thirdparty/fontcpp/include")

    add_deps("bmx", "imgui")

    add_packages("glfw", "glad", "nlohmann_json", "stb")

    if is_plat("windows") then
        add_links("bmx", "imgui", "opengl32")
    elseif is_plat("linux") then
        add_links("bmx", "imgui", "GL", "X11", "Xrandr", "Xi")
    end

    -- copy assets directory
    after_build(
        function (target) 
            os.cp("$(projectdir)/assets", format("$(projectdir)/%s/assets", target:targetdir()))
        end
    )