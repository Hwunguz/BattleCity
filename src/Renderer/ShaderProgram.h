#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace Renderer{
    class shader{

        GLuint shader_program; //shader program

        GLuint m_ID;
        bool is_compiled;
    public:
        shader(std::string& vertexShader, std::string& fragmentShader);
        ~shader();
        shader() = delete;
        shader(shader&) = delete;
        shader& operator=(const shader&) = delete;
        shader& operator=(shader&& shader);
        shader(shader&&);

        bool createshader(std::string& source, GLenum shaderType, GLuint& shaderID);
        void use();
        bool isCompile(){return is_compiled;};

        GLuint get_program(){return shader_program;};
    };
}
