#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Renderer/source.h"

GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";



int g_windowSizeX = 640;
int g_windowSizeY = 400;

void glfwWindowSizeCallback(GLFWwindow* pwindow, int width, int height){
    width = g_windowSizeX;
    height = g_windowSizeY;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY); //1 и 2 параметр - это координаты левого верхнего угла 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}


int main(int argc, char *argv[])
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // проверяем версию OPENGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow: failed" << std::endl;

        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
     
    //устанавливаем окно в котором будем работать
    glfwMakeContextCurrent(pWindow);

    // инициализируем Glad
    if (!gladLoadGL()) { 
        std::cout << "Can't load Glad" << std::endl;
        return -1;
    }
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Opengl version: "<< glGetString(GL_VERSION) << std::endl;

    std::cout << "Opengl" << GLVersion.major << '.' << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 1);

    source src(argv[0]);
    src.loadFile("shader/vs.txt", "vs");
    src.loadFile("shader/fs.txt", "fs");

    std::string vertexShader(src.getShader("vs"));
    // std::string vertexShader(vertex_shader);
    std::string fragmentShader(src.getShader("fs"));
    // std::string fragmentShader(fragment_shader);
    Renderer::shader shaderprogram( vertexShader, fragmentShader);

    if(!shaderprogram.isCompile()){
        std::cerr << "Can't compile shader program";
        return -1;
    }
    

    GLuint point_vbo = 0;
    glGenBuffers(1, &point_vbo); // сгенерировали буфер
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo); // подключили буфер
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW); // загрузили данные в буфер

    GLuint color_vbo = 0;
    glGenBuffers(1, &color_vbo); // сгенерировали буфер
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo); // подключили буфер
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); // загрузили данные в буфер
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(0); // выбираем вектор  vbo
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo); // включаем вершинный буфер 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Цикл отрисовки 
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderprogram.use();

        // glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        // проверяет были ли вызваны какие-то события (ввод с клавиатуры, или движение мыши)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}