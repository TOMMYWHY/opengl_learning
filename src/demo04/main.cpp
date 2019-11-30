//#include <glad/glad.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <math.h>
#include "Shader.h"


void processInput(GLFWwindow *);

float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f,0,0,
        0.5f, -0.5f, 0.0f,  0,1.0f,0,
        0.0f, 0.5f, 0.0f,   0,0,1.0f,

        /*0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,*/
        0.8f, 0.8f, 0.0f, 1.0f,0.0f,1.0f
};
GLuint indices[] ={
        0,1,2,
        2,1,3
};
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 6) in vec3 aPos;\n"
                                 "layout (location = 7) in vec3 aColor;\n"
                                 "out vec4 vertexColor; \n"
                                 "void main(){\n"
                                 "vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0 ); \n"
                                 "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec4 vertexColor;\n"
//                                   "uniform vec4 outsideColor;\n"
                                   "void main(){\n"
//                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);} ";
                                   "    FragColor = vertexColor;} ";
using namespace std;

int main() {
    Shader myShader = Shader("vertexShaderSource.txt","fragmentShaderSource.txt");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "demo 04", nullptr, nullptr);

    glfwMakeContextCurrent(window); // 绑定上下文
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT); // 逆时针 为正面
    glCullFace(GL_BACK);


// ===============
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     unsigned int EBO; //element buffer
     glGenBuffers(1,&EBO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&vertexShaderSource,NULL);
    glCompileShader(fragmentShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    unsigned  int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glVertexAttribPointer(6,3,GL_FLOAT,GL_FALSE,6* sizeof(float),(void*)0);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(7,3,GL_FLOAT,GL_FALSE,6* sizeof(float),(void *)(3* sizeof(float)));
    glEnableVertexAttribArray(7);
// ===============


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(.2f, .5f, .5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        float timeValue = glfwGetTime();
        float blueValue = (sin(timeValue) /2)+0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"outsideColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation,0,0,blueValue,1.0f);

        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        glDrawArrays(GL_TRIANGLES,0,6);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
