@echo off
IF NOT EXIST build (
    mkdir build 
) 


git checkout --recurse-submodules
git submodule update --init --recursive --remote
IF NOT EXIST vcpkg/vcpkg.exe (
    echo install vcpkg
    ./vcpkg/bootstrap-vcpkg.bat
    if %errorlevel%==1 (
        del ./vcpkg/vcpkg.exe
        ./vcpkg/bootstrap-vcpkg.bat
    )
)
cd build 
cmake ..
cd ..
pause