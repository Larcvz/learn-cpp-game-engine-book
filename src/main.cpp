// main.cpp
#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include <minwindef.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <shader.hpp>

#include <array>

constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 640;

int main(void) {
    std::cout << "current path is : ";
    std::cout << std::filesystem::current_path() << std::endl;
    GLFWwindow *window = nullptr;
    /* 初始化glfw */
    if (!glfwInit())
        return -1;
    /* 创建一个Window 和 OpenGL上下文 */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        // 创建失败就退出
        glfwTerminate();
        return -1;
    }
    /* 激活上面创建的OpenGL上下文 */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    // 顶点数据
    std::array<float, 9> vertices = {
        -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f,0.0f,  
        0.0f,  0.5f, 0.0f};
    unsigned int VAO{};
    unsigned int VBO{};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    // 创建shader
    Shader vertexShader{"../asset/res/shaders/vertexshader.vs",
                        GL_VERTEX_SHADER};
    vertexShader.CreateShader();
    vertexShader.CompileShader();

    Shader fragmentSahder{"../asset/res/shaders/fragmentshader.fs",
                          GL_FRAGMENT_SHADER};
    fragmentSahder.CreateShader();
    fragmentSahder.CompileShader();
    // 创建shader program
    GLuint shaderProgram{};
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getId());
    glAttachShader(shaderProgram, fragmentSahder.getId());
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    vertexShader.DeleteShader();
    fragmentSahder.DeleteShader();

    /* 进入游戏引擎主循环 */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);
        // 绘制三角形
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* 处理鼠标 键盘事件 */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}