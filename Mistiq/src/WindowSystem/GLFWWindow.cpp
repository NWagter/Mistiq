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

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(805.0f, 1100.0f, -9.43f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos(805.0f, 500.0f, -9.43f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

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

	lighting = std::make_shared<Mistiq::ShaderProgram>();
	std::shared_ptr<Mistiq::Shader> vertShader = std::make_shared<Mistiq::Shader>("assets/shaders/basic_lighting.vert", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_VERTEX);
	std::shared_ptr<Mistiq::Shader> fragShader = std::make_shared<Mistiq::Shader>("assets/shaders/basic_lighting.frag", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_FRAGMENT);

	lighting->AddShader(vertShader);
	lighting->AddShader(fragShader);
	lighting->Link();

	lamp = std::make_shared<Mistiq::ShaderProgram>();
	std::shared_ptr<Mistiq::Shader> vertShader2 = std::make_shared<Mistiq::Shader>("assets/shaders/lamp.vert", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_VERTEX);
	std::shared_ptr<Mistiq::Shader> fragShader2 = std::make_shared<Mistiq::Shader>("assets/shaders/lamp.frag", Mistiq::Shader::ESHADER_TYPE::SHADER_TYPE_FRAGMENT);

	lamp->AddShader(vertShader2);
	lamp->AddShader(fragShader2);
	lamp->Link();

    //Cube
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
    //

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Mistiq::GLFWWindow::Update(float a_DeltaTime) {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
    
	processInput(m_Window);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	lighting->Use();
	lighting->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	lighting->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	lighting->setVec3("lightPos", lightPos);
	lighting->setVec3("viewPos", cameraPos);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_Properties.m_Width / (float)m_Properties.m_Height, 0.1f, 2000.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	lighting->setMat4("projection", projection);
	lighting->setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	lighting->setMat4("model", model);

	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	lamp->Use();
	lamp->setMat4("projection", projection);
	lamp->setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(200.0f)); // a smaller cube
	lamp->setMat4("model", model);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

    std::cout << "Camera Pos: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;

    for(int i = 0; i < allModels.size(); i++)
    {
        if(allModels[i]->enabled)
        {
			allModels[i]->program->Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, allModels[i]->texture1->ID());

			allModels[i]->program->setMat4("projection", projection);
			allModels[i]->program->setMat4("view", view);

			glm::mat4 modelMatrix = glm::mat4(1.0f);

			/*allModels[i]->MakeTranslationMatrix();
			allModels[i]->MakeRotationMatrix();
			allModels[i]->MakeScaleMatrix();
			allModels[i]->MakeModelMatrix();*/

			modelMatrix = glm::translate(modelMatrix, glm::vec3(allModels[i]->m_Position.x, allModels[i]->m_Position.y, allModels[i]->m_Position.z));

			modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			modelMatrix = glm::scale(modelMatrix, glm::vec3(allModels[i]->m_Scale.x, allModels[i]->m_Scale.y, allModels[i]->m_Scale.z));

			allModels[i]->program->setMat4("model", modelMatrix);

			glBindVertexArray(allModels[i]->VAO);
			glDrawElements(GL_TRIANGLES, allModels[i]->model->primitives[0]->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
        }
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

	float cameraSpeed = 200.5 * 0.02f;
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