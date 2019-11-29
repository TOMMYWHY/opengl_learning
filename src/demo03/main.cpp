#include <glad/glad.h>
#include "Shader.h"

#include <glfw3.h>
#include <iostream>
#include "stb_image.h"

float vertices[] = {
        -0.5f, -0.5f, 0.0f,0,0, //三  0
        0.5f, 0.5f, 0.0f, 1,0,  //一  1
        -.5f, .5f, 0.0f, 1,1,//   二  2

        0.5f, -0.5f, 0.0f,0,1 //  四  3
};

// EBO 索引顺序， 有 VBO 的地方就有 EBO
GLuint indices[] = {
        0, 1, 2, // 三一二
        0, 3, 1  // 三四一

};


GLFWwindow *window;

void init();

void vaoSet();


using namespace std;

int main() {
    init();
    vaoSet();
    Shader myShader;

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    // loading image
    int width,height,nrChannels;
    unsigned char* data = stbi_load("src/demo03/box.jpg",&width,&height,&nrChannels,0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0, GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.useShader();
//        glUseProgram(shaderProgramId);  // 使用 gpu program
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwPollEvents(); // 处理事件，如鼠标等
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void vaoSet() {
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(800, 600, "hello demo-03", nullptr, nullptr);

    glfwMakeContextCurrent(window); // 绑定上下文

    // glad 初始化后， 就不再需要 libGLEW.2.1.dylib or gl32.dl
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "glad loading error" << endl;

    }
}

