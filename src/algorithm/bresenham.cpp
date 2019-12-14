#include <GLFW/glfw3.h>
#include<cmath>
#include <iostream>
#include <iomanip>

using namespace std;


/*float xs = 10.0;
float ys = 30.0;
float xe = 270.0;
float ye = 150.0;
//float ye = 490.0;*/

float xe = 10.0;
float ye = 20.0;
float xs = 370.0;
float ys = 50.0;
//float ys = 490.0;


void bresenham(int x0, int y0, int x1, int y1) {
    if (x0 > x1 && y0 > y1) {
        swap(x0, x1); // 确保划线方向 从左往右 从下往上 画
        swap(y0, y1);
    }
    float x = 0.0;
    float y = 0.0;
    float dx = x1-x0;
    float dy = y1-y0;
    float k = 0.0;
    float d = 0;
    float e = -dx;


    if(dx !=0){
        k = dy/dx;
        if(k < 1 && k >= -1){
            y = y0;
            for(x=x0;x<=x1;x++){
                if(d>0.5){
                    y = y+1;
                    d--;
                }else if(d<0.5){
                    y=y;
                }
                d=d+k;
                cout <<"d: "<< setprecision(3) <<d <<  "; x: " << x << "; y: " << y<<endl;
                glVertex2i(int(x),int (y));
            }

        }
        if(k>1 || k <-1){
            x = x0;
            for (y = y0;  y<y1 ; y++) {
                if(d>0.5){
                    x = x+1;
                    d--;
                }else if(d<0.5){
                    x=x;
                }
                d=d+ 1/k;
                cout <<"d: "<< setprecision(3) <<d <<  "; x: " << x << "; y: " << y<<endl;
                glVertex2i(int(x),int (y));
            }
        }

    }



}

/*int main(){
    cout <<"==="  <<endl;
    bresenham(xs,ys,xe,ye);
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

        bresenham(xs,ys,xe,ye);

        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
