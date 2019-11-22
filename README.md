## openGL

*****

### basic
#### openGL 相关尝试
1. glew（The OpenGL Extension Wrangler Library）是对底层OpenGL接口的封装，可以让你的代码跨平台。
2. glad与glew作用相同，可以看作它的升级版。--- 所以配置 glad 花费了不少时间。。。原因后文叙。
3. Freeglut（OpenGL Utility Toolkit）主要用于创建OpenGL上下文、接收一些鼠标键盘事件等等。
4. glfw（Graphics Library Framework）是Freeglut升级版，作用基本一样。 所以从开始学习就用 glfw。
5. 通常来说glad和glfw配合使用。 glew和Freeglut配合使用。

#### macOS clion 下 glad + glfw 配置

[https://www.cnblogs.com/shayue/p/Mac-CLion-xiaOpenGL-huan-jing-pei-zhi.html](https://www.cnblogs.com/shayue/p/Mac-CLion-xiaOpenGL-huan-jing-pei-zhi.html)
1. 安装 glew glfw3 
2. 下载 glad， 需要官方配置后下载 
 [https://glad.dav1d.de/](https://glad.dav1d.de/)
 
3. 文件位置（重头）
      *  glad 头文件 放到 /usr/local/include.
      >  不能单独将 glad 和 KHR 文件夹拷贝。
      如果这样会出现 #include <KHR/khrplatform.h> 找不到的问题。
      * 我的解决反感是创建 /usr/local/include/glad_KHR 文件夹。
      * 设置层级 glad >  KHR > khrplatform.h 来解决头文件相互引用问题。
      * 最后将 glad.c 拖拽至项目目录。
  
4.   配置CMakeLists文件
     > 参考CMakeLists.txt

至此， glad + glfw  在 mac 下使用 clion 的配置就完成了。

### learning


#### 工作流
1. 初始化，创建窗口 -- 应该都一样吧。
```cpp
 glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(800, 600, "hello demo-03", nullptr, nullptr);
```

2. 引擎   -- 无限循环的输出效果
```cpp
    glfwMakeContextCurrent(window); // 绑定上下文
    while (!glfwWindowShouldClose(window)) {
            glClearColor(.2f, .3f, .3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
    
            glUseProgram(shaderProgramId);  // 使用 gpu program
            glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
            glfwPollEvents(); // 处理事件，如鼠标等
            glfwSwapBuffers(window);
        }
    glfwTerminate();
```

3. 使用 shader -- 将写好的 shader 加载入 gpu

```$xslt
    int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);  // 创建 vertex shader
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr); // 声明 id 指向 shader source
    glCompileShader(vertexShaderId);  // 编译。。。
    
    int shaderProgramId = glCreateProgram();    // 创建 gpu 程序
    glAttachShader(shaderProgramId, vertexShaderId);  // 添加
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);     // 连接

```


   



