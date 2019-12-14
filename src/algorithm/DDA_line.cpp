#include <GLFW/glfw3.h>
#include<cmath>
#include <iostream>

using namespace std;

/*
 * 该算法 有 bug！!~~~！！
 *
 * 问题在于 当 起始点 大于 重点时（ x1- x0 <0 || y1-y0 < 0） 算法中依然使用  y = y0;
 * 并没有将起始点进行交换。
 */

/*float xs = 10.0;
float ys = 10.0;
float xe = 370.0;
float ye = 190.0;
float ye = 390.0;*/

float xe = 10.0;
float ye = 10.0;
float xs = 370.0;
float ys = 190.0;
//float ys = 390.0;

void LineDDA(int a0, int b0, int a1, int b1) {
    float dx, dy, x, y;
    float k;
    dx = a1 - a0;
    dy = b1 - b0;
    k = dy / dx;

    if (abs(k) < 1) {  // 斜率 小于 1
        if (a0 > a1) {
            swap(a0,a1); // 交换 起始点 与 终点
            swap(b0,b1);
        }
        y = b0;
        for (x = a0; x < a1; x++) {
            glVertex2i(x, (int)(y + 0.5));
            y += abs(k); //???????
        }
    } else{
        if (b0 > b1) {
            swap(a0,a1); // 交换 起始点 与 终点
            swap(b0,b1);
        }
        x =a0;
        for (y=b0; y < b1; y++) {
            glVertex2i((int)(x + 0.5), y);
            x += 1.0 / k;
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
    window = glfwCreateWindow(500, 500, "xxxxxx", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window~~~~!!!!!\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1);

    glViewport(0, 0, 500, 500);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();

    glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 1.0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10);
        glLineWidth(2.5);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);

        // Draw gears
//        render_loop();
        LineDDA(xs, ys, xe, ye);


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

