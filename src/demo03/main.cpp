#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

float vertices[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f,
};
GLFWwindow* window;
void init ();
void vaoSet();

using namespace std;
int main(){
    init();
    vaoSet();
    while (!glfwWindowShouldClose(window)){
        glClearColor(.2f,.3f,.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);



        glfwPollEvents(); // 处理事件，如鼠标等
        glfwSwapBuffers(window);
    }
        glfwTerminate();
    return 0;
}

void vaoSet(){
    unsigned int VBO,VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

void init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
     window = glfwCreateWindow(800, 600, "hello Tommy", nullptr, nullptr);

    glfwMakeContextCurrent(window); // 绑定上下文

    // glad 初始化后， 就不再需要 libGLEW.2.1.dylib or gl32.dl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<< "glad loading error" << endl;

    }
}