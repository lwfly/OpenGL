#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const  char* vertexShaderSource = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"layout(location=1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos,1.0);\n"
"   ourColor = aColor;\n"
"}\0";
const  char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor,1.0);\n"
"}\n\0";

const  char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

    
int main()
{
    //glfw:initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LW is your dad", NULL, NULL);
    if(window == NULL){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    

    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    //当窗口调整大小时调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    

    //定义顶点
    float firstVertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f,0.0f,0.0f,  // 右上角
        0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f, // 右下角
        1.0f, -0.5f, 0.0f, 0.0f,0.0f,1.0f,// 左下角
    };
    float secondVertices[] = {
        -0.5f, 0.5f, 0.0f,   // 右上角
        -0.5f, -0.5f, 0.0f,  // 右下角
        -1.0f, -0.5f, 0.0f, // 左下角
    };
    


    //顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    //检测编译是否成功
    int vertex_success;
    char vertex_infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_success);
    if (!vertex_success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertex_infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertex_infolog << endl;
    }


    //编译片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    

    //检测编译是否成功
    int fragment_success;
    char fragment_infolog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_success);
    if (!fragment_success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << fragment_infolog << endl;
    }

    
    //着色器程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    

    //检测链接是否成功
    int Link_success;
    char Link_infolog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Link_success);
    if (!Link_success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, Link_infolog);
        cout << "ERROR::PROGRAM::LINK_FAILED\n" << Link_infolog << endl;
    }

    

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    
    
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);


    //删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //VAO顶点数组对象
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);
    

    //顶点缓冲对象
    unsigned int VBO[2];
    glGenBuffers(2, VBO);

    //绘制第一个三角形
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//启用顶点属性(位置为0)
    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);//启用顶点属性(位置为1)


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);

    //链接顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);//启用顶点属性

   
    //索引缓冲对象
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        //检测是否按下了ESC键，如果按下了，窗口将关闭
        processInput(window);

        //清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

       /* float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);*/


        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES,0,3);




        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);//交换颜色缓冲
        glfwPollEvents();//检查有没有触发什么事件，更新窗口状态，并调用回调函数
    }

    glDeleteVertexArrays(2,VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();//释放分配的所有资源
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}