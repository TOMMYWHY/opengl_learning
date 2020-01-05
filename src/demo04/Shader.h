//
// Created by Tommy on 2019-11-30.
//

#ifndef OPENGL_START_03_SHADER_H
#define OPENGL_START_03_SHADER_H

#include <string>
using namespace std;

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    string vertexString;
    string fragmentString;
    const char* vertexSource;
    const char* fragmentSource;
    void test();

};


#endif //OPENGL_START_03_SHADER_H
