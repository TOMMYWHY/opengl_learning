#include <glad/glad.h>
#include <glfw3.h>
#include <cmath>
#include <iostream>
#include <math.h>

float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1,0,0,//三  0
        0.5f, 0.5f, 0.0f,   0,1,0,//一  1
        -.5f, .5f, 0.0f,    0,0,1,//   二  2

        0.5f, -0.5f, 0.0f,  1,0,0, //  四  3
};

// EBO 索引顺序， 有 VBO 的地方就有 EBO
GLuint indices[] = {
        0, 1, 2, // 三一二
        0, 3, 1  // 三四一

};


GLFWwindow *window;
int vertexColorLocation ;

void init();

void vaoSet();

int shadersSet();

using namespace std;

int main() {
    init();
    vaoSet();
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    int shaderProgramId = shadersSet();
    while (!glfwWindowShouldClose(window)) {

        // 定义变色 时间
        float  timeValue = (float)glfwGetTime();
        float  redValue = (float)(sin(timeValue)/1.2f);

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);  // 使用 gpu program


        glUniform4f(vertexColorLocation,redValue,0.0f,0.0f,1.0f);

//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwPollEvents(); // 处理事件，如鼠标等
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}


int shadersSet() {
    // 顶点 shader - 确定顶点位置


    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
//                                     ===="out vec4 gl_Position;\n" // gl_Position 不能定义
                                     "out vec3 ourColor;\n" // 输出 rgb

                                     "void main(){\n"
                                     "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
                                     "ourColor = vec3(aColor.x, aColor.y, aColor.z);}";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
//                                       "uniform vec4 outsideColor;\n"
                                       "in vec3 ourColor;\n" // 输入 rgb
                                       "void main(){\n"
                                       "FragColor = vec4(ourColor,1);} ";

    /* const char *vertexShaderSource = "#version 400 core\n"
                                      "layout (location = 0) in vec3 aPos;\n" //
                                      "out vec4 vertexColor;\n"
                                      "void main(){\n"
                                      "vertexColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                      "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}"; //
     // 片面 shader - 每个像素着色
     const char *fragmentShaderSource = "#version 400 core\n"
                                        "out vec4 FragColor;\n"
                                        "in vec4 vertexColor;\n"
                                        "void main(){\n"
                                        "    FragColor = vertexColor;} ";
 //                                       "    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);} ";*/


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

//  =====  outsideColor   =====
    vertexColorLocation = glGetUniformLocation(shaderProgramId, "outsideColor"); // 找位置
    glUseProgram(shaderProgramId);
//    glUniform4f(vertexColorLocation,0.0f,1.0f,0.0f,1.0f);

    return shaderProgramId;

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

    //told gpu structure 位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0); // layout (location = 0)

    // 颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3* sizeof(float)));
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

