//
// Created by Tommy on 2019-11-18.
//

#ifndef OPENGL_START_03_DISPLAY_H
#define OPENGL_START_03_DISPLAY_H


class DisplayMode{
public:
    int width;
    int height;
    DisplayMode():width(0),height(0){}; // 初始化列表
    DisplayMode(int w, int h):width(w),height(h){};
};

class ContextAttribute{
public:
    int major;
    int minor;
    bool bProfileCore;
    ContextAttribute():major(0),minor(0),bProfileCore(false){}
    ContextAttribute(int _major, int _minor):major(_major),minor(_minor),bProfileCore(false){}
    void withProfileCore(bool bUseProfile){bProfileCore = bUseProfile;}
};

class Display {
private:
    DisplayMode mDisplayMode;
    const char* title;
    struct GLFWwindow* mWindow;
    void processEvent();
public:
    Display():title(""),mWindow(nullptr){};

    void create(ContextAttribute attr);
    void update();
    void destroy();
    bool isRequestClosed();
    void setDisplayMode(DisplayMode );
    void setTitle(const char* _title);
    static void frameBufferSizeCallback(GLFWwindow* , int,int);

};


#endif //OPENGL_START_03_DISPLAY_H
