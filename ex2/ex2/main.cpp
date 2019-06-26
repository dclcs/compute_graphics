#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//�����εĶ�������
const float triangle[] = {
	// λ��
	-0.5f, -0.5f, 0.0f, //����
	0.5f, -0.5f, 0.0f,//����
	0.0f, 0.5f, 0.0f//����
};
//������ɫ��Դ��
const char *vetex_shader_source =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos, 1.0);\n"
	"}\n\0";
//Ƭ����ɫ��Դ��
const char *fragment_shader_source =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";



int main()
{
	//��ʼ��
	// ��ʼ��GLFW
	int screen_width = 600;
	int screen_height = 800;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	auto window = glfwCreateWindow(screen_width, screen_height, "Triangle",
		nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to Create OpenGL Context" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//��ʼ��GLAD �� ����OpenGL����ָ���ַ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//ָ����ǰ�ӿڳߴ�
	glViewport(0, 0, screen_width, screen_height);




	//���ݴ���
		//VAO VBO�������˶������ݣ�����������Ҫ����Щ�������ݷ��͵�GPU��ȥ����
		//��������������һ�����㻺�����VBO��
		//���ҽ���󶨵����㻺������ϣ�
		//ʹ��������㻺�����ĺô������ǲ��ý���������һ��һ���ķ��͵��Կ���
		//���ǿ��Խ���VBOһ���Եķ���һ�������ݹ�ȥ��
		//Ȼ��ʹ�� glBufferData������ ���ݰ󶨵���ǰĬ�ϵĻ����ϣ�
		//�����GL_STATIC_DRAW��ʾ���ǵ������� λ�����ݲ��ᱻ�ı䡣
	//���ɲ���VBO
	GLuint vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	//���������ݰ�����ǰĬ�ϵĻ�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	
		//�������ǻ�������һ�������������VAO��
		//ʹ��VAO��ԭ������������ ʹ�õĺ���ģʽҪ��������Ҫʹ��VAO��
		//���ʹ��VAO�ĺô������������� Ⱦ��ʱ��ֻ��Ҫ����һ�� VAO �Ϳ����ˣ�
		//֮ǰ�����ݶ���Ӧ�洢���� VAO �У� �����ٵ���VBO��
		//��ôVAO�����ɹ���Ҳ��VBOһ������Ҫ�������ٰ󶨣�
		//�ȵ���Щ�����������꣬���ǿ��Խ�����ǵ�VAO��VBO
	//���ɲ���VAO
	GLuint vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	
	

	//���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*) 0);
	glEnableVertexAttribArray(0);

	//���ɶ�����ɫ��
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vetex_shader_source, NULL);
	glCompileShader(vertex_shader);
	int success;
	char info_log[512];
	//�����ɫ���Ƿ�ɹ�����
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	//����Ƭ����ɫ��
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source,NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	//���Ӷ����Ƭ����ɫ����һ����ɫ������
	int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	//��Ⱦ
	//ʹ����ɫ������

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f,  1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);

		glBindVertexArray(vertex_array_object);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);

	glfwTerminate();
	return 0;
}