# MulletEngine
A lightweight game engine written in C++ using modern graphics and utility libraries.  
This repository documents the development progress and provides instructions for building the project.
## References
During the development of MulletEngine, I am actively following and learning from these resources (work in progress):
- *Game Engine Architecture* by Jason Gregory  
- [LearnOpenGL](https://learnopengl.com/) – Modern OpenGL tutorials and examples

## Technologies Used

- **C++**
- **OpenGL** (Rendering)
- **GLEW** (OpenGL Extension Wrangler)
- **GLFW** (Window/context/input)
- **Assimp** (Model loading)
- **ImGui** (Immediate GUI)
- *(More technologies may be added as the engine evolves)*

---

## Development Progress

Below is a checklist of the engine modules, showing what's completed and what's planned:

| Module              | Status    |
|---------------------|:---------:|
| File Manager        | ☑️ Done   |
| Shader              | ☑️ Done   |
| Camera              | ☑️ Done   |
| Animation           | ⬜ Todo   |
| Character Controller| ⬜ Todo   |
| Input Manager       | ⬜ Todo   |
| Material            | ⬜ Todo   |
| Mesh                | ⬜ Todo   |
| Model               | ⬜ Todo   |
| Particle Manager    | ⬜ Todo   |
| Physics World       | ⬜ Todo   |
| Post Process        | ⬜ Todo   |
| Render Manager      | ⬜ Todo   |
| Resource Manager    | ⬜ Todo   |
| Shadow Manager      | ⬜ Todo   |
| Sound Engine        | ⬜ Todo   |
| UI                  | ⬜ Todo   |
| ...                 |           |

---

## Build Instructions

MulletEngine is written in C++ and uses **CMake** as its build system.

### Prerequisites

- **C++ compiler** (GCC, Clang, MSVC, etc.)
- **CMake** (version 3.10 or higher recommended)
- **Git** (to clone the repository)
- Required libraries (OpenGL, GLEW, GLFW, Assimp, ImGui, etc. – see project for details)

### Steps

1. **Clone the repository:**
    ```sh
    git clone https://github.com/muhammedfurkangok/MulletEngine.git
    cd MulletEngine
    ```

2. **Create a build directory and configure the project:**
    ```sh
    mkdir build
    cd build
    cmake ..
    ```

3. **Build the engine:**
    ```sh
    cmake --build .
    ```

4. **Run the engine (if executable produced):**
    ```sh
    ./MulletEngine
    ```

#### Notes

- Make sure required dependencies are installed and discoverable by CMake.
- On Windows, you may use CMake GUI or pass generator parameters for Visual Studio.
- For additional configuration, see CMakeLists.txt and documentation in the repo.

---

## Contribution

Feel free to open issues, submit pull requests, or suggest new modules.  
Development progress is tracked above.

---
