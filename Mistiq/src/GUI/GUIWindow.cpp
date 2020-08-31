#include "Mstqpch.h"
#include "GUIWindow.h"
#include "Mistiq/Application.h"

Mistiq::GUIWindow::GUIWindow() {
	m_Open = false;
}

Mistiq::GUIWindow::~GUIWindow() {

}

void Mistiq::GUIWindow::Init()
{
}

void Mistiq::GUIWindow::Update(float a_DeltaTime) {

}

void Mistiq::GUIConsoleWindow::Init()
{
	m_Open = true;
	m_ClearOnPlay = false;
	m_DisplayTimeStamp = false;
}

void Mistiq::GUIConsoleWindow::Update(float a_DeltaTime)
{
	ImGui::Begin("Console");

	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Clear on play", &m_ClearOnPlay);
		ImGui::Checkbox("Display timestamp", &m_DisplayTimeStamp);
		ImGui::EndPopup();
	}

	if (ImGui::SmallButton("Options"))
		ImGui::OpenPopup("Options");

	ImGui::SameLine();
	if(ImGui::SmallButton("Clear"))
	{
		Application::instance().m_Debugger->ClearConsoleLogs();
	}

    ImGui::Separator();

    for(int i = 0; i < Application::instance().m_Debugger->GetConsoleLogs().size(); ++i)
    {
		std::string log;

        //If timestamp is allowed to be displayed
        if(m_DisplayTimeStamp)
        {
			log.append(Application::instance().m_Debugger->GetConsoleLogs()[i].time);
			log.append(" ");
        }
        
		log.append(Application::instance().m_Debugger->GetConsoleLogs()[i].message);
		ImGui::Text(log.c_str());
    }

	ImGui::End();
}

void Mistiq::GUIHierarchyWindow::Init()
{
	m_Open = true;
}

void Mistiq::GUIHierarchyWindow::Update(float a_DeltaTime)
{
	ImGui::Begin("Hierarchy");

	std::map<Entity, std::shared_ptr<NameComponent>> components = Application::instance().m_ECSManager->GetComponents<NameComponent>();
	for (auto const& [key, val] : components)
	{
		if (val != nullptr)
		{
			if (ImGui::Selectable(val->name.c_str()))
			{
				Application::instance().m_GuiManager->m_OnInspectorEntitySelected(key);
			}
		}
	}
	ImGui::End();
}

void Mistiq::GUIInspectorWindow::Init()
{
	m_Open = true;
	m_CurrentSelectedEntity = -1;

	Application::instance().m_GuiManager->m_OnInspectorEntitySelected+= MemFunc(*this, &GUIInspectorWindow::OnInspectorEntitySelected);
}

void Mistiq::GUIInspectorWindow::Update(float a_DeltaTime)
{
	ImGui::Begin("Inspector");

    if(m_CurrentSelectedEntity > -1)
    {
		unsigned int i = m_CurrentSelectedEntity;
		ImGui::Text(Application::instance().m_ECSManager->GetComponent<NameComponent>(i)->name.c_str());
    }

	ImGui::End();
}

void Mistiq::GUIInspectorWindow::OnInspectorEntitySelected(unsigned a_Entity)
{
	m_CurrentSelectedEntity = a_Entity;
}

void Mistiq::GUISceneWindow::Init()
{
	m_Open = false;
}

void Mistiq::GUISceneWindow::Update(float a_DeltaTime)
{
	ImGui::Begin("Scene");
    
	ImGui::End();
}
