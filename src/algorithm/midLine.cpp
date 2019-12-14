#include <GLFW/glfw3.h>
#include<cmath>
#include <iostream>

using namespace std;


float xs = 10.0;
float ys = 30.0;
float xe = 270.0;
//float ye = 150.0;
float ye = 490.0;

/*float xe = 10.0;
float ye = 20.0;
float xs = 370.0;
//float ys = 50.0;
float ys = 490.0;*/



void MidpointLine1(int x0, int y0, int x1, int y1) {

    if (x0 > x1 && y0 > y1) {
        swap(x0, x1); // 确保划线方向 从左往右 从下往上 画
        swap(y0, y1);
    }

    if ((x0 != x1) && (y0 != y1)) {
        int a, b, delta1, delta2, d, x, y;
        float k = (float) (y1 - y0) / (float) (x1 - x0);

        if (k >= 0 && k <= 1) {
            a = y0 - y1;
            b = x1 - x0;
            d = 2 * a + b;
            delta1 = 2 * a;
            delta2 = 2 * (a + b);
            x = x0;
            y = y0;
            while (x < x1) {
                if (d < 0) {
                    x++;
                    y++;
                    d += delta2;
                    cout << "d: d < 0 :::-----:::" << d << "; x0: " << x0 << "; y0: " << y0 << "; x: " << x << "; y: "
                         << y << endl;

                } else {
                    x++;
                    d += delta1;
                    cout << "d: d < 0 :-:" << d << "; x0: " << x0 << "; y0: " << y0 << "; x: " << x << "; y: " << y
                         << endl;

                }
                glVertex2i(x, y);
            }
        } else  //if(k>1)
        {
            cout << "fuck" << endl;

            a = y0 - y1;
            b = x1 - x0;
            d = a + 2 * b;
            delta1 = 2 * (a + b);
            delta2 = 2 * b;
            x = x0;
            y = y0;
            while (y < y1) {
                if (d < 0) {
                    y++;
                    d += delta2;
                    cout << "d: d < 0 :::-----:::" << d << "; x0: " << x0 << "; y0: " << y0 << "; x: " << x << "; y: "
                         << y << endl;

                } else {
                    y++;
                    x++;
                    d += delta1;
                    cout << "d: d < 0 :-:" << d << "; x0: " << x0 << "; y0: " << y0 << "; x: " << x << "; y: " << y
                         << endl;

                }
                glVertex2i(x, y);
            }
        }
    } else {
        int min, d;
        if (x0 == x1) {
            int x = x0, y;
//            y = (y0 <= y1) ? y0 : y1;
            y = y0; //最一开始判断 且 交换 y0 与 y1
            d = fabs((double) (y0 - y1));
            while (d >= 0) {
                glVertex2i(x, y);
                y++;
                d--;
            }
        }
        if (y0 == y1) {
            int x, y = y0;
//            x = (x0 <= x1) ? x0 : x1;
            x = x0;
            d = fabs((double) (x0 - x1));
            while (d >= 0) {
                glVertex2i(x, y);
                x++;
                d--;
            }
        }
    }
}

/*int main(){


    cout <<"==="  <<endl;
    MidpointLine1(xs,ys,xe,ye);
    return 0;
}*/

int main(int argc, char *argv[]) {
    GLFWwindow *window;
    glfwInit();


    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(500, 500, "bresenham line", NULL, NULL);


    glfwMakeContextCurrent(window);
    glViewport(0, 0, 500, 500);

    glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 1.0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10);
        glLineWidth(2.5);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);

        MidpointLine1(xs, ys, xe, ye);

        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
