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
	//MAHOR ���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//MINOR �˰汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Core-Profile ����ģʽ
	// ��glfwWindowHint������GLFW����һ������Ϊ����ѡ������ƣ�
	//�ڶ��β�������һ������
	
	// �鿴OpenGL�汾
	int Major, Minor, Rev;
	glfwGetVersion(&Major, &Minor, &Rev);
	printf("GLFW %d.%d.%d. initialized\n",Major, Minor, Rev);


	//����һ������
	GLFWwindow* window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFE window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))//���GLFW�Ƿ������˳�
	{
		
		//����
		//processInput(window);

		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//��Ⱦָ��


		// ��鲢�����¼���������
		glfwSwapBuffers(window);//������ɫ����
		glfwPollEvents();//�����û��ʲô�����¼������´���״̬�������ö�Ӧ�Ļص�����

	
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//�ӿ�

	glViewport(0, 0, width, height);
}