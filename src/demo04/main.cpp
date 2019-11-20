#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>



using namespace std;
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "demo 04", nullptr, nullptr);

    glfwMakeContextCurrent(window); // 绑定上下文

    // glad 初始化后， 就不再需要 libGLEW.2.1.dylib or gl32.dl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<< "glad loading error" << endl;
    }

    while (!glfwWindowShouldClose(window)){
        glClearColor(.2f,.3f,.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


