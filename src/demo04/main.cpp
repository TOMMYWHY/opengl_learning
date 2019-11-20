//#include <glad/glad.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>


void processInput(GLFWwindow*);

using namespace std;
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "demo 04", nullptr, nullptr);

    glfwMakeContextCurrent(window); // 绑定上下文
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,600);

    while (!glfwWindowShouldClose(window)){
        processInput(window);

//        glClearColor(.2f,.3f,.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window){

    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}
