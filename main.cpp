#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

using namespace std;

int main(int argc, const char * argv[]) {
    if (!glfwInit()){
        cout<< "init fialed"<<endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "hello Tommy", nullptr, nullptr);

    if(!window) {
        glfwTerminate();
        cout<< " window create failed" <<endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<< " laoding opengl failed" <<endl;
        return -1;
    }
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
