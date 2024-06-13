import adcm
import os
import shutil

adcm.new_project("PBR Viewer")

def mkdir_build():
    if not os.path.exists("build"):
        os.mkdir("build")

def copy_assets():
    if os.path.exists("build/assets"):
        shutil.rmtree("build/assets")
    shutil.copytree("assets", "build/assets")

def buildrun():
    adcm.do_task("build")
    adcm.do_task("run")

adcm.add_task(
    "generate",
    [
        mkdir_build,
        "cd build && cmake .. -G Ninja -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_EXPORT_COMPILE_COMMANDS=ON"
    ]
)

adcm.add_task(
    "build",
    [
        "cd build && cmake --build .",
        copy_assets
    ]
)

adcm.add_task(
    "run",
    ["cd build && .\\PBR-Viewer.exe"]
)

adcm.add_task(
    "br",
    [buildrun]
)

adcm.add_trigger(
    "cmake-generate-support",
    [
        "CMakeLists.txt",
        "thirdparty/CMakeLists.txt"
    ],
    ["generate"]
)

adcm.launch()