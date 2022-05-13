cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(TinyMusic)


set(RELEASE_PATH "${PROJECT_SOURCE_DIR}/release")
set(DEBUG_PATH "${PROJECT_SOURCE_DIR}/debug")

find_package(SDL2 CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(EASTL CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")

set(PROJECT_PATH ${CMAKE_SOURCE_DIR}/TinyMusic)
set(SRC_PATH ${PROJECT_PATH}/src)
set(RESOURCE_PATH ${PROJECT_PATH}/res)

file(GLOB_RECURSE PROJECT_SOURCES ${SRC_PATH}/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS ${SRC_PATH}/*.h)
file(GLOB_RECURSE PROJECT_RESOURCES ${RESOURCE_PATH}/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt Readme.md .gitattributes .gitignore .gitmodules LICENSE)


source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_SOURCES})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_HEADERS})
source_group(TREE ${PROJECT_PATH} FILES ${PROJECT_RESOURCES})
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${PROJECT_CONFIGS})

add_executable(TinyMusic ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${RESOURCE_PATH})

set_property(TARGET TinyMusic PROPERTY CXX_STANDARD 11)

target_include_directories(TinyMusic PRIVATE ${STB_INCLUDE_DIRS} ) 

target_link_libraries(TinyMusic PRIVATE SDL2::SDL2 SDL2::SDL2main 
                                        PRIVATE asio asio::asio 
                                        PRIVATE Catch2::Catch2 
                                        PRIVATE glad::glad
                                        PRIVATE imgui::imgui 
                                        PRIVATE nlohmann_json nlohmann_json::nlohmann_json
                                        PRIVATE SDL2::SDL2_image 
                                        PRIVATE SDL2::SDL2_mixer 
                                        PRIVATE SDL2::SDL2_ttf 
                                        PRIVATE spdlog::spdlog spdlog::spdlog_header_only 
                                        PRIVATE OpenAL::OpenAL 
                                        PRIVATE EASTL
)

if (MSVC)
  set_target_properties(TinySDL PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${RELEASE_PATH})
elseif(UNIX AND NOT APPLE)
  target_link_libraries(TinyMusic PRIVATE  SDL2::SDL2-static Catch2::Catch2WithMain)
  target_link_libraries(TinyMusic PRIVATE  X11  Xext )

endif()

add_custom_command(TARGET TinyMusic POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy_directory 
                      ${CMAKE_SOURCE_DIR}/TinyMusic/res ${RELEASE_PATH}/res 
)

set_target_properties(TinyMusic PROPERTIES 
           ARCHIVE_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           LIBRARY_OUTPUT_DIRECTORY "${RELEASE_PATH}/lib" 
           RUNTIME_OUTPUT_DIRECTORY "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_DEBUG "${RELEASE_PATH}" 
           RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_PATH}" 
)
