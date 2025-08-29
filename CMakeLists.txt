#=======================================================================================================================

cmake_minimum_required(VERSION 3.30)
project(MulletEngine LANGUAGES CXX)
enable_language(C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Engine library
# -------------------------
file(GLOB_RECURSE ENGINE_SOURCES
        ${CMAKE_SOURCE_DIR}/engine/*.cpp
        ${CMAKE_SOURCE_DIR}/engine/*.hpp
)

add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC ${CMAKE_SOURCE_DIR}/engine)

# -------------------------
# Third-party (manual include)
# -------------------------
target_include_directories(engine PUBLIC
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
        ${CMAKE_SOURCE_DIR}/third_party/glad/include    # veya glew/include
        ${CMAKE_SOURCE_DIR}/third_party/glm
        ${CMAKE_SOURCE_DIR}/third_party/imgui
        ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
        ${CMAKE_SOURCE_DIR}/third_party/bullet/src
        ${CMAKE_SOURCE_DIR}/third_party/assimp/include
)

# GLAD (örnek)
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/third_party/glad/include)

# ImGui
set(IMGUI_SRC
        ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
        ${CMAKE_SOURCE_DIR}/third_party/imgui
        ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
        ${CMAKE_SOURCE_DIR}/third_party/glfw/include
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glfw)

# Platform-specific
if (WIN32)
    set(PLATFORM_LIBS opengl32)
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    set(PLATFORM_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
else()
    find_package(X11 REQUIRED)
    set(PLATFORM_LIBS X11 pthread dl)
endif()

# Engine links
target_link_libraries(engine
        PUBLIC
        glfw
        opengl32
        ${PLATFORM_LIBS}
        PRIVATE
        glad
        imgui
)

# -------------------------
# Sandbox app
# -------------------------
add_subdirectory(sandbox)
