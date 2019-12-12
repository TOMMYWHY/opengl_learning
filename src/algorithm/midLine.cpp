#include <GLFW/glfw3.h>
#include<cmath>
#include <iostream>

using namespace std;


float xs = 10.0;
float ys = 10.0;
float xe = 370.0;
float ye = 50.0;
//float ye = 390.0;

/*float xe = 10.0;
float ye = 10.0;
float xs = 370.0;
float ys = 150.0;
//float ye = 190.0;*/


void MidpointLine1(int a0, int b0, int a1, int b1) {
    float dx, dy, x, y, k, d;
    dx = a1 - a0;
    dy = b1 - b0;
    k = dy / dx;
    // Ax + By +C = 0
    // k = - (B/A) = dy/dx => B = -dy; A = dx

    if(abs(k) < 1){
        int A = a0- a1;
        int B = -(b0 -b1);

        d = A + 0.5*B;
        int d1 = A+B;
        int d2 = A;
        if (a0 > a1) {
            swap(a0,a1); // 交换 起始点 与 终点
            swap(b0,b1);
        }
        x = a0;
        y = b0;
        glVertex2i((float)x, (float)y);
//        cout << "d: " <<d <<  endl;


        while(x<a1) {
            if(d< 0){
                x++;
                y++;
                d += d1;
                cout << "x: " << x << " ; y: " << y <<  endl;
                cout << "-----d: " <<d <<  endl;

            } else{
                x++;
                y++;
                d+= d2;
            }
            glVertex2i((float)x, (float)y);
            cout << "x: " << x << " ; y: " << y <<  endl;

        }


    }else{
        int A = a0- a1;
        int B = -(b0 -b1);
        d = A + 0.5*B;
        int d1 = A+B;
        int d2 = B;
        x = a0;
        y = b0;

        for (y = b0;  y<= b1; y++) {
            if(d< 0){
//                cout << "&&&&&&&&7" <<d <<  endl;

                x++;
                d += d1;
                cout << "-----d: " <<d <<  endl;

            } else{
                x++;
                d+= d2;
            }
            glVertex2i((float)x, (float)y);
            cout << "x: " << x << " ; y: " << y <<  endl;

        }
    }






}


void MidpointLine(int x0,int y0,int x1,int y1)
{
    if((x0!=x1)&&(y0!=y1))
    {
        int a,b,delta1,delta2,d,x,y;
        float k=(float)(y1-y0)/(float)(x1-x0);
        if(k>=0&&k<=1)
        {
            a=y0-y1;
            b=x1-x0;
            d=2*a+b;
            delta1=2*a;
            delta2=2*(a+b);
            x=x0;
            y=y0;
            glVertex2i(x,y);
            while(x<x1)
            {
                if(d<0)
                {
                    x++;
                    y++;
                    d+=delta2;
                }
                else
                {
                    x++;
                    d+=delta1;
                }
                glVertex2i(x,y);
            }
        }
        else //if(k>1)
        {
            a=y0-y1;
            b=x1-x0;
            d=a+2*b;
            delta1=2*(a+b);
            delta2=2*b;
            x=x0;
            y=y0;
            glVertex2i(x,y);
            while(y<y1)
            {
                if(d<0)
                {
                    y++;
                    d+=delta2;
                }
                else
                {
                    y++;
                    x++;
                    d+=delta1;
                }
                glVertex2i(x,y);
            }
        }
    }
    else
    {
        int min,d;
        if(x0==x1)
        {
            int x=x0,y;
            y=(y0<=y1)?y0:y1;
            d=fabs((double)(y0-y1));
            while(d>=0)
            {
                glVertex2i(x,y);
                y++;
                d--;
            }
        }
        if(y0==y1)
        {
            int x,y=y0;
            x=(x0<=x1)?x0:x1;
            d=fabs((double)(x0-x1));
            while(d>=0)
            {
                glVertex2i(x,y);
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

        MidpointLine1(xs,ys,xe,ye);

        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
