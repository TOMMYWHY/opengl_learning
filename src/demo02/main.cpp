//#include <glad/glad.h>
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>

using namespace std;


float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};
GLFWwindow *window;

void init();

void vaoSet();


static int compilerShader(unsigned int type, const string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = &source[0];
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int result;

    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE){
        int errLength;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&errLength);
        char * msg = (char*)alloca(errLength* sizeof(char));
        glGetShaderInfoLog(id, GL_INFO_LOG_LENGTH,&errLength,msg);
        cout << "failed compile"<< (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") <<endl;
        cout << msg <<endl;
        glDeleteShader(id);
        return  0;
    }
    return id;
}

static unsigned int createShader(const string &vertexShader, const string &fragmentShader) {
    GLuint program = glCreateProgram();
    unsigned int vShader = compilerShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fShader = compilerShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glValidateProgram(program); // 未必须

    glDeleteShader(vShader); // 回收
    glDeleteShader(fShader); // 回收

    return program;

}



int main() {
    init();
//    vaoSet();
//===============================
    float position[6] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f, 0.5f
    };
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    =====shader====
    string vertexShaderSource = "#version 330 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main(){\n"
                                "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}";

    string fragmentShaderSource = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "void main(){\n"
                                  "FragColor = vec4(.05f, 0.2f, 0.2f, 1.0f);} ";

    unsigned int shader;
    shader = createShader(vertexShaderSource,fragmentShaderSource);
    glUseProgram(shader);


    while (!glfwWindowShouldClose(window)) {
        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwPollEvents(); // 处理事件，如鼠标等
        glfwSwapBuffers(window);
    }
    glDeleteShader(shader);
    glfwTerminate();
    return 0;
}

void vaoSet() {
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
}

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(800, 600, "hello Tommy", nullptr, nullptr);

    glfwMakeContextCurrent(window); // 绑定上下文

    // glad 初始化后， 就不再需要 libGLEW.2.1.dylib or gl32.dl
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<< "glad loading error" << endl;

    }*/

    // 如果 glfwMakeContextCurrent glewInit 自动初始化。
    if (glewInit() != GLEW_OK) {
        cout << "glew error" << endl;
    }
}