//
// Created by Tommy on 2019-11-29.
//

#ifndef OPENGL_START_03_SHADER_H
#define OPENGL_START_03_SHADER_H

#include <glad.h>


class Shader {
public:
    int shaderProgramId;
    Shader(void);
    void useShader();
    ~Shader(void);
};


#endif //OPENGL_START_03_SHADER_H
