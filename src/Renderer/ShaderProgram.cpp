#include "ShaderProgram.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <string>
#include <iostream>
std::string loadFile(std::string Name){
    std::string buf, tmpbuf;
    std::ifstream file;
    file.open("../../Res/shader/" + Name);
    while(!file.eof()){
        getline(file, tmpbuf);
        buf += tmpbuf;
    }
    file.close(); 
    return buf;   
}


Renderer::shader::shader(std::string& vertexShader, std::string& fragmentShader)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if(!createshader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)){
        std::cerr << "FRAGMENT SHADER time error" << std::endl;
        glDeleteShader(vertexShaderID);
        return;
    }

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if(!createshader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)){
        std::cerr << "FRAGMENT SHADER time error" << std::endl;
        glDeleteShader(fragmentShaderID);
        return;
    }
    this->m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID); // добавляем в программу вершинный шейдер
    glAttachShader(m_ID, fragmentShaderID); // добавляем в программу фрагментный шейдер
    glLinkProgram(m_ID); 

    GLint success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if(!success){
        GLchar inflog[1024];
        glGetShaderInfoLog(m_ID, 1024, nullptr, inflog);
        std::cerr << "ERROE::SHADER Link time error:\n" << inflog << std::endl;
    }else{
        is_compiled = true;
    }
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

bool Renderer::shader::createshader(std::string& source, GLenum shaderType, GLuint& shaderID){
    shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);
    
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        GLchar inflog[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, inflog);
        std::cerr << "ERROE::SHADER Compile time error:\n" << inflog << std::endl;
        return false;
    }
    return true;
}

void Renderer::shader::use(){
    glUseProgram(m_ID);
}

Renderer::shader::shader(shader &&){

}

Renderer::shader::~shader(){
    glDeleteProgram(m_ID);
}
