//
// Created by Tommy on 2019-11-18.
//

#ifndef OPENGL_START_03_DISPLAYMANAGER_H
#define OPENGL_START_03_DISPLAYMANAGER_H

#include "Display.h"

class DisplayManager {
private:
    Display mDisplay;

public:
    DisplayManager();

    void createDisplay();
    void updateDisplay();
    void closeDisplay();

    bool isRequestClosed();
};


#endif //OPENGL_START_03_DISPLAYMANAGER_H
