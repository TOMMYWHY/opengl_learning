//#include <glad/glad.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include <iostream>
using namespace std;

#define R 0.5f
#define n  100
#define Pi  3.141592657519

/*
 * https://www.bilibili.com/video/av70144328
 */
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "日了狗~！", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        cout<< "glew init error" << endl;
    }

    float position[6] = {
            0,0.5f,
            0.5f,-0.5f,
            -0.5f,-0.5f
    };
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float),position,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,8,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    /* Loop until the user closes the windo w */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // =================================== //

        /*
        glBegin(GL_TRIANGLES);
        glVertex2d(0,.5f); //Vertex 定点 //此处 glew 的 gl 库
        glVertex2d(.5f,-.5f);
        glVertex2d(-.5f,-.5f);
         */
        /*
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; ++i) {
            glVertex2f(R*sin(2*Pi/i*n),R*cos(2*Pi/i*n));
//            glVertex2f(R*cos(2*Pi/n*i),R*sin(2*Pi/n*i));
        }
         glEnd();

         */

        glDrawArrays(GL_TRIANGLES,0,3);

        // =================================== //
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}