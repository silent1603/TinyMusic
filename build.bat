@echo off
IF NOT EXIST build (
    mkdir build 
)
git submodule update --init --recursive
IF NOT EXIST vcpkg/vcpkg.exe (
    echo install vcpkg
    ./vcpkg/bootstrap-vcpkg.bat
)
cd build 
cmake ..
cd ..
pause