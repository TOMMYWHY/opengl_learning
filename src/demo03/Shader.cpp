//
// Created by Tommy on 2019-11-29.
//

#include "Shader.h"
#include <string>
#include <iostream>
using namespace std;


Shader::Shader() {
//    cout <<"aaaa" <<endl;
    // 顶点 shader - 确定顶点位置
    const char *vertexShaderSource = "#version 400 core\n"
                                     "layout (location = 0) in vec3 aPos;\n" //
                                     "layout (location = 1) in vec2 aTexCoordinate;\n" //
                                     "out vec2 TexCoordinate;\n"
                                     "void main(){\n"
                                     "TexCoordinate = aTexCoordinate;\n" //
                                     "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}"; //
    // 片面 shader - 每个像素着色
    const char *fragmentShaderSource = "#version 400 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec2 TexCoordinate;\n"
                                       "uniform sampler2D ourTexture;\n"
                                       "void main(){\n"
                                       "FragColor = texture(ourTexture,TexCoordinate);} ";


    int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);  // 创建 vertex shader
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr); // 声明 id 指向 shader source
    glCompileShader(vertexShaderId);  // 编译。。。

    int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId);

    int shaderProgramId = glCreateProgram();    // 创建 gpu 程序
    glAttachShader(shaderProgramId, vertexShaderId);  // 添加
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);     // 连接

//    return shaderProgramId;
}


void Shader::useShader(){
//    cout<<shaderProgramId<<endl;
    glUseProgram(shaderProgramId);
}

Shader::~Shader() {}