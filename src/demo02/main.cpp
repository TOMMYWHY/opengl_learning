#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

using namespace std;

#define R 0.5f
#define n  100
#define Pi  3.141592657519

/*
 * https://www.bilibili.com/video/av18762006
 */

void loadAndUseShader();


int main(void) {
    GLFWwindow *window;
    if (!glfwInit()) {
        return -1;
    }
    window = glfwCreateWindow(640, 480, "日了狗~！", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "glad loader fail~!" << endl;
    }

    float vertices[] = {
            0, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    loadAndUseShader();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(.2f, .5f, .5f, 1.0f);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void loadAndUseShader() {
    const char *vertexCode = "#version 330 core\n"
                             "layout (location = 0) in vec3 aPos;\n"
                             "void main(){\n"
                             "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";

    const char *fragmentCode = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main(){\n"
                               "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);} ";

    GLuint vertex, fragment;

//vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    int success;
    char infoLog[512];

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        cout << " compile vertex fail \n" << infoLog << endl;
    }

//fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        cout << " compile fragment fail \n" << infoLog << endl;
    }

    GLuint PID = glCreateProgram();
    glAttachShader(PID, vertex);
    glAttachShader(PID, fragment);
    glLinkProgram(PID);

    glGetProgramiv(PID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(PID, 512, nullptr, infoLog);
        cout << " Program fail \n" << infoLog << endl;
    }
//    glDeleteBuffers(vertex);
//    glDeleteBuffers(fragment);
    glUseProgram(PID);

}