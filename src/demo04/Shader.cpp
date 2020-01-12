//
// Created by Tommy on 2019-11-30.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


Shader::Shader(const char* vertexPath, const char* fragmentPath){
    ifstream vertexFile;
    ifstream fragmentFile;
    stringstream vertexSSream;
    stringstream fragmentSSrveam;

    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    vertexFile.exceptions(ifstream::failbit|| ifstream::badbit);
    fragmentFile.exceptions(ifstream::failbit|| ifstream::badbit);


    try {
        if(!vertexFile.is_open() || !fragmentFile.is_open()){
//            throw exception("vertexFile open fail~!");
            throw "vertexFile or fragmentFile open fail~!";
//            throw exception();？？？？
        }

        vertexSSream << vertexFile.rdbuf(); // 读到的 buffer 存入 vertexSSream 中
        fragmentSSrveam << fragmentFile.rdbuf();

        /*if(vertexFile.rdbuf()){
            printf("有值");
        }else{
            printf("空");

        }*/

        vertexString = vertexSSream.str(); // 获得字符串
        fragmentString = fragmentSSrveam.str();

        vertexSource = vertexString.c_str(); // 将字符串 转成 char*
        fragmentSource = fragmentString.c_str();

        printf(vertexSource);
        printf(fragmentSource);
        cout <<"aaa:" << vertexString <<endl;

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
