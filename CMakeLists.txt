cmake_minimum_required(VERSION 3.14)
project(opengl_start_03)

set(CMAKE_CXX_STANDARD 14)

set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3/include/GLFW)
#set(GLAD_H /usr/local/include/glad)
set(GLAD_H /usr/local/include/glad_KHR/glad)
#set(KH_H /usr/local/include/KHR)
set(KH_H /usr/local/include/glad_KHR/glad/KHR)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

################
include_directories(include/
        external/assimp/include/
        external/glad/include/
        external/glfw/include/
        external/glm
        external/stb
#        /usr/local/include/glad
        )

file(GLOB EXTERNAL_SOURCES external/glad/src/glad.c
        external/stb/stb_image.cpp)
file(GLOB PROJECT_HEADERS include/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS res/shader/*.vs
        res/shader/*.fs)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Externals" FILES ${EXTERNAL_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})
################

# 执行编译命令
# 这个glad.c在第2步中说过要拉到项目中，注意路径
#set(SOURCE_FILES "src/glad.c" "main.cpp")

# demo01 # oop
#set(
#    SOURCE_FILES "src/glad.c"
#    "src/demo01/main.cpp"
#    "src/demo01/Display.h" "src/demo01/Display.cpp"
#    "src/demo01/DisplayManager.h" "src/demo01/DisplayManager.cpp"
#    )

# demo02 https://www.bilibili.com/video/av70144328  #
set(SOURCE_FILES "src/glad.c" "src/demo02/main.cpp")

# demo03 https://www.bilibili.com/video/av57654623   # 阿西拜0328

#set(SOURCE_FILES "src/glad.c" "src/demo03/main.cpp"
#        "src/demo03/Shader.h" "src/demo03/Shader.cpp"
#        "src/demo03/stb_image.h" "src/demo03/stb_image.cpp"
#        "src/demo03/box.jpg"
#        "src/glm"
#        )

#set(SOURCE_FILES "src/glad.c" "src/demo03/main_p10.cpp" "src/demo04/Shader.h" "src/demo04/Shader.cpp")


# demo04 https://www.bilibili.com/video/av24353839  # 傅老师

#set(SOURCE_FILES "src/glad.c"
#        "src/demo04/main.cpp"
#        "src/demo04/Shader.h"
#        "src/demo04/Shader.cpp"
##        "vertexShaderSource.txt" //shader.txt 文件 需要放到二进制执行目录下，同 图片纹理一致。
#        )

#file(GLOB PROJECT_SHADERS vertexShaderSource.txt
#        fragmentShaderSource.txt)
#source_group("Shaders" FILES ${PROJECT_SHADERS})

# demo05 https://github.com/wanlin405/Computer_Graphics  # 万琳
#set(SOURCE_FILES "src/glad.c" "src/demo05/main.cpp" )

# DDA
#set(SOURCE_FILES "src/glad.c" "src/algorithm/DDA.cpp" )
#set(SOURCE_FILES "src/glad.c" "src/algorithm/DDA_line.cpp" )
#set(SOURCE_FILES "src/glad.c" "src/algorithm/bresenham.cpp" )
#set(SOURCE_FILES "src/glad.c" "src/algorithm/midLine.cpp" )



# demo02 艾孜尔江主讲  #
set(SOURCE_FILES "src/glad.c" "src/demo06/main.cpp")
add_executable(OpenGL ${SOURCE_FILES})





# mac下这步很重要
if (APPLE)
    target_link_libraries(OpenGL "-framework OpenGL")
    target_link_libraries(OpenGL "-framework GLUT")

endif()