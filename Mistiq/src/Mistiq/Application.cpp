#include "Mstqpch.h"
#include "Application.h"
#include "../ECS/Component.h"
#include "../ECS/System.h"
#include "../ECS/ECSManager.h"
#include <imgui.h>
#include "include/glad/glad.h"

struct Position : public Mistiq::Component {
	static const unsigned int m_Type;

	float x;
	float y;

	Position(float a_X, float a_Y) : x(a_X), y(a_Y) {
	}
};

const unsigned int Position::m_Type = 1;

class Translate : public Mistiq::System {
public:
	Translate() {
		std::set<unsigned int> requiredComponents;
		requiredComponents.insert(Position::m_Type);
		SetRequiredComponents(std::move(requiredComponents));
	}

    void UpdateEntities(float a_DeltaTime) override {
        for(auto entity : m_MatchingEntities) {
			std::shared_ptr<Position> position = m_Manager->GetComponentStorage<Position>()->Get(entity);

			position->x += 20;
			position->y += 20;
        }
	}
};

Mistiq::Application::Application()
{
	Mistiq::ECSManager manager;
    manager.CreateComponentStorage<Position>();
	manager.AddSystem<Translate>();

	for (size_t i = 0; i < 2; ++i) {
		Mistiq::Entity ball = manager.CreateEntity();
		manager.AddComponent<Position>(ball, Position(0.0f, 0.0f));
		manager.RegisterEntity(ball);
	}

	for (size_t i = 0; i < 20; ++i) {
		manager.UpdateEntities(0.0f);
	}

    ///Setting up upper hierarchy engine classes
	m_Window = std::make_unique<GLFWWindow>();
	m_GuiManager = std::make_unique<GUIManager>();
}

Mistiq::Application::~Application()
{
    
}

void Mistiq::Application::Setup() {
	///Setting up window
	WindowProperties windowProps;
	windowProps.m_Name = "Mistiq";
	windowProps.m_Width = 1920;
	windowProps.m_Height = 1080;
	m_Window->Create(windowProps);
}

void Mistiq::Application::Update() {
    OPTICK_FRAME("ApplicationUpdate")
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GuiManager->Update(0.2f);
	m_Window->Update(0.2f);
	
}

void Mistiq::Application::Clean() {
	m_Window->Destroy();
}

bool Mistiq::Application::IsOpen() {
	return m_Window->IsOpen();
}
