# PBRV

## introduce
**PBR Viewer** is a glTF model viewer written in C++ and OpenGL, which has following features:

- Physically Based Rendering
- Component System
- Bloom
- Shadow (PCSS, SDFSS)
- Global Illumination (SSGI, SDFGI)

So basically this project is a graphics-tech toy and I do recommend you consider it as a study project only.

## how to build
### 1. clone project
```bash
git clone https://github.com/anpydx/pbr-viewer.git
```

### 2. build project
*NOTICE:* **Requires CMake and C++ compiler(C++17 at least)!**


**Windows**
```bash
cd pbr-viewer
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

**Debian**
```bash
# install dependence
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev

# build from source
cd pbr-viewer
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### 3. run project


## thirdparty
- [GLFW](https://github.com/glfw/glfw) cross-platform window creation.
- [GLAD](https://github.com/Dav1dde/glad) OpenGL context loading.
- [imgui](https://github.com/ocornut/imgui) provide fine GUI widget.
- [fontcpp](https://github.com/juliettef/IconFontCppHeaders) Awesome-Font icon loading.
- [stb](https://github.com/nothings/stb) image loading.
- [assimp](https://github.com/assimp/assimp) various model formats support.
- [json](https://github.com/nlohmann/json) scene format's json part parsing.
- [mas](https://github.com/anpydx/mas) simple math support.
- [bmx](https://github.com/anpydx/bmx) bmx shader format and scene format's bmx support.

**additional fonts:** `Cascadia`, `Font-Awesome`

## references
- [LearnOpenGL-CN](https://learnopengl-cn.github.io/)

## License
Licensed under the **MIT License**, read [LICENSE](LICENSE) for details.