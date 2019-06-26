#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	//MAHOR 主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//MINOR 此版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Core-Profile 核心模式
	// 用glfwWindowHint来配置GLFW，第一个参数为代表选项的名称，
	//第二次参数接受一个整形
	
	// 查看OpenGL版本
	int Major, Minor, Rev;
	glfwGetVersion(&Major, &Minor, &Rev);
	printf("GLFW %d.%d.%d. initialized\n",Major, Minor, Rev);


	//创建一个窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFE window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// 渲染循环
	while (!glfwWindowShouldClose(window))//检测GLFW是否请求退出
	{
		
		//输入
		//processInput(window);

		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//渲染指令


		// 检查并调用事件交换缓冲
		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//检查有没有什么触发事件、更新窗口状态，并调用对应的回调函数

	
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//视口

	glViewport(0, 0, width, height);
}