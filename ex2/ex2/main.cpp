#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//三角形的顶点数据
const float triangle[] = {
	// 位置
	-0.5f, -0.5f, 0.0f, //左下
	0.5f, -0.5f, 0.0f,//右下
	0.0f, 0.5f, 0.0f//正上
};
//顶点着色器源码
const char *vetex_shader_source =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos, 1.0);\n"
	"}\n\0";
//片段着色器源码
const char *fragment_shader_source =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";



int main()
{
	//初始化
	// 初始化GLFW
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
	//初始化GLAD ， 加载OpenGL函数指针地址函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//指定当前视口尺寸
	glViewport(0, 0, screen_width, screen_height);




	//数据处理
		//VAO VBO我们有了顶点数据，接下来就是要将这些顶点数据发送到GPU中去处理，
		//这里我们生成了一个顶点缓冲对象VBO，
		//并且将其绑定到顶点缓冲对象上，
		//使用这个顶点缓冲对象的好处是我们不用将顶点数据一个一个的发送到显卡，
		//而是可以借助VBO一次性的发送一大批数据过去，
		//然后使用 glBufferData将顶点 数据绑定到当前默认的缓冲上，
		//这里的GL_STATIC_DRAW表示我们的三角形 位置数据不会被改变。
	//生成并绑定VBO
	GLuint vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	//将顶点数据绑定至当前默认的缓冲中
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	
		//这里我们还生成了一个顶点数组对象VAO，
		//使用VAO的原因是首先我们 使用的核心模式要求我们需要使用VAO，
		//其次使用VAO的好处在于我们在渲 染的时候只需要调用一次 VAO 就可以了，
		//之前的数据都对应存储在了 VAO 中， 不用再调用VBO。
		//那么VAO的生成过程也跟VBO一样，需要先生成再绑定，
		//等到这些操作都进行完，我们可以解绑我们的VAO，VBO
	//生成并绑定VAO
	GLuint vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	
	

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*) 0);
	glEnableVertexAttribArray(0);

	//生成顶点着色器
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vetex_shader_source, NULL);
	glCompileShader(vertex_shader);
	int success;
	char info_log[512];
	//检查着色器是否成功编译
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	//生成片段着色器
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source,NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	//连接顶点和片段着色器至一个着色器程序
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

	//渲染
	//使用着色器程序

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