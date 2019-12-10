#include <GLFW/glfw3.h>
#include<cmath>
#include <iostream>

using namespace std;


float xs = 10.0;
float ys = 10.0;
float xe = 200.0;
float ye = 200.0;

void LineDDA(int x0, int y0, int x1, int y1) {
    float x = 0.0;
    float y = 0.0;
    float m = 0.0;
    float dx = x1 - x0;
    float dy = y1 - y0;
//    cout << "dx :" << dx << endl;
    if (dx != 0) {
//        cout << "111" << endl;
        m = dy / dx;
        if (m <= 1 && m >= -1) {
            y = y0;
            for (x = x0; x <= x1; x++) {
                glVertex2i(x, int(y + 0.5));
                y += m;
            }
        }
        if (m > 1 || m < -1) {
            m = 1 / m;
            x = x0;
            for (y = y0; y <= y1; y++) {
                glVertex2f(int(x + 0.5), y);
                x += m;
            }
        }
    } else {
        int x = x0;
        int y = 0;
        y = (y0 <= y1) ? y0 : y1;
        int d = fabs((double) (y0 - y1));
        while (d >= 0) {
            glVertex2f(x, y);
            cout << "x: " << x
                 << "y: " << y
                 << endl;
            y++;
            d--;
        }
    }
}

int main(int argc, char *argv[]) {
    GLFWwindow *window;
    glfwInit();
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(400, 400, "xxxxxx", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window~~~~!!!!!\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // set up view
    glViewport(0, 0, 400, 400);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    glOrtho(0.0, 400.0, 0.0, 400.0, 0.0, 1.0); // this creates a canvas you can do 2D drawing on


    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10);
        glLineWidth(2.5);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);

        // Draw gears
//        render_loop();
        LineDDA(xs,ys,xe,ye);


        glEnd();
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit(EXIT_SUCCESS);
}

/*
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
    glViewport(0,0,500,500);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
//        LineDDA(xs, ys, xe, ye);


//        glVertex2f(, );
        render_loop();

        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
*/
