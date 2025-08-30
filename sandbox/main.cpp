    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <iostream>
    #include "file_manager/FileManager.h"



int main()
    {
        glfwInit();
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        constexpr int window_width = 800;
        constexpr int window_height = 600;
        FileManager* fileManager;
        GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Triangle", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        gladLoadGL();
        glViewport(0, 0, window_width, window_height);

        std::string vertex_stage_text = FileManager::readFile("assets/shaders/temp-shader.vs");
        std::string fragment_stage_text = FileManager::readFile("assets/shaders/temp-shader.fs");

        GLuint vertex_stage = glCreateShader(GL_VERTEX_SHADER);
        const char* vertex_src = vertex_stage_text.c_str();
        glShaderSource(vertex_stage, 1, &vertex_src, nullptr);
        glCompileShader(vertex_stage);

        GLuint fragment_stage = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragment_src = fragment_stage_text.c_str();
        glShaderSource(fragment_stage, 1, &fragment_src, nullptr);
        glCompileShader(fragment_stage);

        GLuint shader = glCreateProgram();
        glAttachShader(shader, vertex_stage);
        glAttachShader(shader, fragment_stage);
        glLinkProgram(shader);

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        GLuint vao, vbo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteShader(vertex_stage);
        glDeleteShader(fragment_stage);
        glDeleteProgram(shader);

        glfwDestroyWindow(window);
        glfwTerminate();

        return 0;
    }