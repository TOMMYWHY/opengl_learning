//
// Created by Tommy on 2019-11-18.
//

#include "Display.h"
#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;


void Display::create(ContextAttribute attr){
    if (!glfwInit()){
        cout<< "init failed"<<endl;
        return ;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, attr.major); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, attr.minor); // 次版本号
    if(attr.bProfileCore){
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);

//    GLFWwindow* mWindow= glfwCreateWindow(mDisplayMode.width,mDisplayMode.height,title, nullptr, nullptr);
    // 在 头文件 中定义了 GLFWwindow* 的结构体， 直接将 mWindow 赋值
    mWindow= glfwCreateWindow(mDisplayMode.width,mDisplayMode.height,title, nullptr, nullptr);
    if(!mWindow){
        cout<< " window create failed~!" <<endl;
        return;
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

};
void Display::update(){
    processEvent();
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
};
void Display::destroy(){
    glfwDestroyWindow(mWindow);
    glfwTerminate();
    mWindow = nullptr;
};
bool Display::isRequestClosed(){
    if (glfwWindowShouldClose(mWindow)){
        destroy();
        return true;
    }
    return false;
};
void Display::setDisplayMode(DisplayMode mode){
    mDisplayMode = mode;
};

void Display::setTitle(const char* _title){
    title = _title;
};

 void Display::frameBufferSizeCallback(GLFWwindow* _window, int w,int h){
 };

 // private private
void Display::processEvent(){
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE)== GLFW_PRESS){
        glfwSetWindowShouldClose(mWindow,true);
    }
};