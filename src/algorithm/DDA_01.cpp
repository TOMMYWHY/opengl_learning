#include <GLFW/glfw3.h>
#include<cmath>


float xs = -0.9;
float ys = -0.8;
float xe = 0.9;
float ye = 0.7;

void LineDDA(int x0, int y0, int x1, int y1)
{
    float x = 0.0;
    float y = 0.0;
    float m = 0.0;
    float dx = x1 - x0;
    float dy = y1 - y0;
    if (dx != 0)
    {
        m = dy/dx;
        if (m <= 1 && m >= -1)
        {
            y = y0;
            for (x = x0; x <= x1; x++)
            {
                glVertex2i(x, int(y+0.5));
                y += m;
            }
        }
        if (m>1 || m<-1)
        {
            m = 1/m;
            x = x0;
            for (y=y0; y<=y1; y++)
            {
                glVertex2i(int(x+0.5), y);
                x += m;
            }
        }
    }
    else
    {
        int x = x0;
        int y = 0;
        y = (y0 <= y1) ? y0 : y1;
        int d = fabs((double) (y0 - y1));
        while (d >= 0)
        {
            glVertex2i(x, y);
            y++;
            d--;
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
        LineDDA(xs, ys, xe, ye);


//        glVertex2f(0.0f, 0.0f);
//        glVertex2f(0.5f, 0.5f);
//        glVertex2f(-0.9,-0.9);
//        glVertex2f(0.9,0.8);

        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}