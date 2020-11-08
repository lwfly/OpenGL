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
    

    //��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    //�����ڵ�����Сʱ�����������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    

    //���嶥��
    float firstVertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f,0.0f,0.0f,  // ���Ͻ�
        0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f, // ���½�
        1.0f, -0.5f, 0.0f, 0.0f,0.0f,1.0f,// ���½�
    };
    float secondVertices[] = {
        -0.5f, 0.5f, 0.0f,   // ���Ͻ�
        -0.5f, -0.5f, 0.0f,  // ���½�
        -1.0f, -0.5f, 0.0f, // ���½�
    };
    


    //������ɫ��
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    //�������Ƿ�ɹ�
    int vertex_success;
    char vertex_infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_success);
    if (!vertex_success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertex_infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertex_infolog << endl;
    }


    //����Ƭ����ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    

    //�������Ƿ�ɹ�
    int fragment_success;
    char fragment_infolog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_success);
    if (!fragment_success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << fragment_infolog << endl;
    }

    
    //��ɫ���������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    

    //��������Ƿ�ɹ�
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


    //ɾ����ɫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //VAO�����������
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);
    

    //���㻺�����
    unsigned int VBO[2];
    glGenBuffers(2, VBO);

    //���Ƶ�һ��������
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
    //λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);//���ö�������(λ��Ϊ0)
    //��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);//���ö�������(λ��Ϊ1)


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);

    //���Ӷ�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);//���ö�������

   
    //�����������
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        //����Ƿ�����ESC������������ˣ����ڽ��ر�
        processInput(window);

        //����
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

        glfwSwapBuffers(window);//������ɫ����
        glfwPollEvents();//�����û�д���ʲô�¼������´���״̬�������ûص�����
    }

    glDeleteVertexArrays(2,VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();//�ͷŷ����������Դ
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