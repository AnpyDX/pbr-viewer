import os
import shutil

cmake_flags: str = "-DCMAKE_BUILD_TYPE=Release"
build_flags: str = "-j8"

""" clean pervious directories """
if os.path.exists("build"):
    shutil.rmtree("build")

if os.path.exists("binary"):
    shutil.rmtree("binary")

""" create necessary directories """
print("> creating directories...")
os.mkdir("build")
os.mkdir("binary")

""" build project """
print("> generating cmake project...")
os.system("cd build && cmake .. {0}".format(cmake_flags))

print("> building project...")
os.system("cd build && cmake --build . {0}".format(build_flags))

""" generate binary directory """
shutil.copytree("assets", "binary/assets")

if os.path.exists("build/PBRV.exe"): # clang on Windows
    shutil.copy("build/PBRV.exe", "binary/PBRV.exe")

elif os.path.exists("build/Debug/PBRV.exe"): # MSVC on Windows
    shutil.copy("build/Debug/PBRV.exe", "binary/PBRV.exe")

elif os.path.exists("build/PBRV"): # Linux and Unix
    shutil.copy("build/PBRV", "binary/PBRV")

else:
    raise RuntimeError("> error! Failed to find executable in build directory. It seems that project building was failed.")

print("\n> successfully build project! output is in ~/binary directory.")