#include "Mstqpch.h"
#include "GLFWWindow.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/Shaders/Shader.h"

Mistiq::GLFWWindow::GLFWWindow() {
	m_Localization.LoadLanguageData();
}

Mistiq::GLFWWindow::~GLFWWindow() {
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Mistiq::GLFWWindow::Create(WindowProperties a_WindowProperties) {
	Window::Create(a_WindowProperties);

	glfwInit();
	m_IsOpen = true;
	m_Window = glfwCreateWindow(m_Properties.m_Width, m_Properties.m_Height, m_Properties.m_Name, nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowUserPointer(m_Window, &m_Properties);
	glfwSwapInterval(true);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
}

void Mistiq::GLFWWindow::Update(float a_DeltaTime) {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
    
	processInput(m_Window);

    for(int i = 0; i < allModels.size(); i++)
    {
		allModels[i]->program->Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, allModels[i]->texture1->ID());

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_Properties.m_Width / (float)m_Properties.m_Height, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		allModels[i]->program->setMat4("projection", projection);
		allModels[i]->program->setMat4("view", view);

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(allModels[i]->m_Position.x, allModels[i]->m_Position.y, allModels[i]->m_Position.z));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(allModels[i]->m_Rotation.x, allModels[i]->m_Rotation.y, allModels[i]->m_Rotation.z));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(allModels[i]->m_Scale.x, allModels[i]->m_Scale.y, allModels[i]->m_Scale.z));
		allModels[i]->program->setMat4("model", modelMatrix);

		glBindVertexArray(allModels[i]->VAO);
		glDrawElements(GL_TRIANGLES, allModels[i]->model->primitives[0]->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); 
    }
	

	int x, y;
	glfwGetWindowSize(m_Window, &x, &y);
	m_Properties.m_Width = x;
	m_Properties.m_Height = y;

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Mistiq::GLFWWindow::Destroy() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Mistiq::GLFWWindow::IsOpen() {
	int state = glfwGetKey(m_Window, GLFW_KEY_ESCAPE);
	if (state == GLFW_PRESS)
	{
		m_IsOpen = false;
	}
	return m_IsOpen;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}