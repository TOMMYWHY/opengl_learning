#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
using namespace std;

float position[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
};
const float triangle[] = {
//     ---- 位置 ----
        -0.5f, -0.5f, 0.0f,   // 左下
        0.5f, -0.5f, 0.0f,   // 右下
        0.0f,  0.5f, 0.0f    // 正上
};

const char *vertex_shader_source =
        "#version 330 core\n"
        "layout (location = 0) in vec4 position;\n"           // 位置变量的属性位置值为0
        "void main()\n"
        "{\n"
        "    gl_Position = position;\n"
        "}\n\0";
const char *fragment_shader_source =
        "#version 330 core\n"
        "layout (location = 0) out vec4 FragColor;\n"                           // 输出的颜色向量
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

static int compilerShaderFun(GLuint type,const string& source){
    GLuint  id = glCreateShader(type); //GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    const char* src = &source[0];//source.c_str();
    //    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);
    //TODO: error handling
    int result;
    int logLength;
    glGetShaderiv(id,GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &logLength);
        char* msg = (char*)alloca(logLength* sizeof(char));
        glGetShaderInfoLog(id,GL_INFO_LOG_LENGTH,&logLength,msg);
        std::cout << "COMPILATION_FAILED\n" <<(type ==GL_VERTEX_SHADER?"GL_VERTEX_SHADER" : "GL_FRAGMENT_SHADER")
        << msg << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return  id;
}
static unsigned int createProgrammeFun(const char* vertex_shader_source, const char* fragment_shader_source){
    GLuint programme = glCreateProgram();
    GLuint vertexShader = compilerShaderFun(GL_VERTEX_SHADER,vertex_shader_source);
    GLuint fragmentShader = compilerShaderFun(GL_FRAGMENT_SHADER,fragment_shader_source);


//    glAttachShader(shader_program, vertex_shader);
    glAttachShader(programme,vertexShader);
    glAttachShader(programme,fragmentShader);
    glLinkProgram(programme);
    glValidateProgram(programme); //???

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return  programme;
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    auto window = glfwCreateWindow(800,600,"demo06",NULL,NULL);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }*/

    GLuint buffer; // VBO
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float),position,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FLOAT,8, (void*)0); // ??
    glBindBuffer(GL_ARRAY_BUFFER,0);

    GLuint shaderProgramme =  createProgrammeFun(vertex_shader_source,fragment_shader_source);




    while(!glfwWindowShouldClose(window)){

        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgramme);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shaderProgramme);
    glfwTerminate();
    return 0;
}
