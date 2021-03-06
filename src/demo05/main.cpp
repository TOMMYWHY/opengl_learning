#include <glad.h>
#include <glfw3.h>
#include <iostream>

float vertices[] = {
        // 第一个三角形
        0.5f, 0.5f, 0.0f,     // 右上
        0.5f, -0.5f, 0.0f,    // 右下
        -0.5f, -0.5f, 0.0f,   // 左下
        // 第二个三角形
        -0.5f, -0.5f, 0.0f,   // 左下
        0.5f, 0.5f, 0.0f,     // 右上
        -0.5f, 0.5f, 0.0f     // 左上
};


unsigned int indices[] = {
        0, 1, 5,              // 第一个三角形
        1, 2, 5               // 第二个三角形
};


// 顶点着色器源码
const char *vertex_shader_source =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos, 1.0);\n" "}\n\0";

const char *fragment_shader_source =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" "}\n\0";


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    auto window = glfwCreateWindow(800,600,"demo05", nullptr, nullptr);

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);

//    VAO VBO EBO
    unsigned int vertex_buffer_object; // VBO
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    GLuint vertex_array_object;  // VAO
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    GLuint element_buffer_object; // == EBO
    glGenBuffers(1, &element_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// glVertexAttribPointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //================// 生成并编译着色器


    int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);  // 创建 vertex shader
    glShaderSource(vertexShaderId, 1, &vertex_shader_source, nullptr); // 声明 id 指向 shader source
    glCompileShader(vertexShaderId);  // 编译。。。

    int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragmentShaderId);

    int shaderProgramId = glCreateProgram();    // 创建 gpu 程序
    glAttachShader(shaderProgramId, vertexShaderId);  // 添加
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);     // 连接

    glUseProgram(shaderProgramId);

//.........

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindVertexArray(vertex_array_object);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}