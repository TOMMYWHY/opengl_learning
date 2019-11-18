#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

//#include "Display.h"
#include "DisplayManager.h"

using namespace std;

int main(int argc, const char * argv[]) {
    DisplayManager mDisplayManager;
    mDisplayManager.createDisplay();
    while (!mDisplayManager.isRequestClosed()){

        mDisplayManager.updateDisplay();
    }
    mDisplayManager.closeDisplay();
    return 0;
}
