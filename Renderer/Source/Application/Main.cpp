#include "stdafx.h"
#include "Application/Application.h"
#include "Application/Window/Window.h"
#include "Application/Layer/UiLayer.h"
#include "Application/Layer/RenderLayer.h"

void calculateFps(GLFWwindow* window);

enum class ShadingOption : uint8_t
{
	DefaultShading = 0,
	Wireframe = 1
};

enum class ObjectProperty : uint8_t
{
	CULL_FACE = 0,
	CULL_BACK_FACE = 1
};

enum class RendererOption : uint16_t
{
	CLOCK_WISE = 0
};

ShadingOption mode = ShadingOption::DefaultShading;

ObjectProperty property = ObjectProperty::CULL_BACK_FACE;



unsigned int viewportWidth = 0;
unsigned int viewportHeight = 0;


void onWindowSizeChange(GLFWwindow* window, int width, int height)
{
	viewportWidth = width;
	viewportHeight = height;
}


int main()
{

	Log::init();

	Application* app = Application::getPtr();

	app->registerWindow(new Window);
	app->addGuiLayer(new UiLayer);
	app->addLayer(new RenderLayer);

	app->run();

	return 0;
}

#if 0


int main()
{
#if 0
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vMode = glfwGetVideoMode(primaryMonitor);

	GLFWwindow* window = glfwCreateWindow(vMode->width, vMode->height, "This is a renderer", primaryMonitor, nullptr);
	if (window == nullptr)
	{
		return 1;
	}
#endif
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	if (primaryMonitor == nullptr)
	{
		// error
		return 1;
	}


	int videoModeCount = 0;
	const GLFWvidmode* videoModes = glfwGetVideoModes(primaryMonitor, &videoModeCount);
	if (videoModeCount == 0 || videoModes == nullptr)
	{
		// Error
		return 1;
	}

	for (int i = 0; i < videoModeCount; i++)
	{
		GLFWvidmode videoMode = videoModes[i];

		printf("-------- Video Modes: --------\n\n");
		printf("* Width: %d Height: %d RefreshRate: %d\n",
			videoMode.width, videoMode.height,
			videoMode.refreshRate
			);
		printf("--------              --------\n\n");
	}

	GLFWvidmode currentVideoMode = videoModes[0];
	viewportWidth = currentVideoMode.width;
	viewportHeight = currentVideoMode.height;

	GLFWwindow* window = glfwCreateWindow(currentVideoMode.width, currentVideoMode.height, "This is a renderer", nullptr, nullptr);
	if (window == nullptr)
	{
		return 1;
	}
	glfwMakeContextCurrent(window);


	// Callbacks
	glfwSetWindowSizeCallback(window, onWindowSizeChange);
	

	// Prepare for OpenGL API
	ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (ret != 0)
	{
		// Error;
		// Done;
	}

	// Shader
	int successed;
	char buf[256] = { 0 };

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successed);
	if (!successed)
	{
		glGetShaderInfoLog(vertexShader, 256, nullptr, buf);
		return 1;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successed);
	if (!successed)
	{
		glGetShaderInfoLog(fragmentShader, 256, nullptr, buf);
		return 1;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successed);
	if (!successed)
	{
		glGetShaderInfoLog(fragmentShader, 256, nullptr, buf);
		return 1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Buffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Render Settings
	// VSync
	glfwSwapInterval(0);

	// Framewire mode
	if (mode == ShadingOption::Wireframe)
	{
	    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (mode == ShadingOption::DefaultShading)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Cull face
	if (property == ObjectProperty::CULL_BACK_FACE)
	{
		glCullFace(GL_BACK);
	}
	else if (property == ObjectProperty::CULL_FACE)
	{
		glEnable(GL_CULL_FACE);
	}

	glFrontFace(GL_CW);

	while (!glfwWindowShouldClose(window))
	{
		calculateFps(window);
		// Input

		
		// Render 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, viewportWidth, viewportHeight);

		// Draw
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		

		// Render end
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Release
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}
#endif
