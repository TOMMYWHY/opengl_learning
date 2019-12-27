//
// Created by Tommy on 2019-11-30.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
using namespace std;


Shader::Shader(const char* vertexPath, const char* fragmentPath){
    ifstream vertexFile;
    ifstream fragmentFile;

    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    vertexFile.exceptions(ifstream::failbit|| ifstream::badbit);
    fragmentFile.exceptions(ifstream::failbit|| ifstream::badbit);


    try {
        if(!vertexFile.is_open() || fragmentFile.is_open()){
//            throw exception("vertexFile open fail~!");
            throw "vertexFile or fragmentFile open fail~!";
//            throw exception();？？？？
        }
    }catch (const char* msg){
        cout << msg <<endl;
    }

    vertexFile.close();
}
Shader::~Shader(){}

/*
void Shader::test(){
    cout << "shader testing..."<<endl;
}*/
