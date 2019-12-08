#include <iostream>
#include <glew.h>
#include <GLUT/GLUT.h>
#include<cmath>

using namespace std;
float xs = 0.0;
float ys = 0.0;
float xe = 0.0;
float ye = 0.0;

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

void lineSegment()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    LineDDA(xs, ys, xe, ye);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);

    cout << "输入线段起始和终点坐标（范围为 0 - 500, 0-500）:";
    cin >> xs >> ys >> xe >> ye;

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA画线算法");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500, 0.0, 500.0);
    glutDisplayFunc(lineSegment);
    glutMainLoop();

    return 0;
}