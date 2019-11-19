//#include <glad/glad.h>
#include <glfw3.h>
#include <math.h>

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

    /* Loop until the user closes the window */
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
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; ++i) {
            glVertex2f(R*sin(2*Pi/i*n),R*cos(2*Pi/i*n));
//            glVertex2f(R*cos(2*Pi/n*i),R*sin(2*Pi/n*i));
        }


        glEnd();
        // =================================== //
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}