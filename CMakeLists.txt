cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version
project(advent)  # Project name
set(CMAKE_BUILD_TYPE Release)

# Find SFML package
# find_package(SFML 3.0.0 COMPONENTS Graphics Window System REQUIRED)
add_subdirectory(vendor/SFML)

FILE(GLOB_RECURSE TARGET_SRC "src/*.cpp")
message("${TARGET_SRC}")

add_executable(${PROJECT_NAME} ${TARGET_SRC})
# Link SFML to the target
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
