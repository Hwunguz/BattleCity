#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

int main(void)
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

    // Цикл отрисовки 
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        // проверяет были ли вызваны какие-то события (ввод с клавиатуры, или движение мыши)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}