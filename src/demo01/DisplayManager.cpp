//
// Created by Tommy on 2019-11-18.
//

#include "DisplayManager.h"
DisplayManager::DisplayManager(){};
void DisplayManager::createDisplay(){
    mDisplay.setTitle("<== hello world ==>");
    mDisplay.setDisplayMode(DisplayMode(800,600));
    ContextAttribute attr(3,3);
    mDisplay.create(attr);
};
void DisplayManager::updateDisplay(){
    mDisplay.update();
};
void DisplayManager::closeDisplay(){
    mDisplay.destroy();
};

bool DisplayManager::isRequestClosed(){
    return mDisplay.isRequestClosed();
};