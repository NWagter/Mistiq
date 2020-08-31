#pragma once
#include "GUIWindow.h"
#include "EventSystem/Event.h"

namespace Mistiq {
	class GUIManager {
	public:
		GUIManager();
		~GUIManager();

		void Init();
		void Update(float a_DeltaTime, int a_FPS);

        ///Draw none static GUI windows
		void DrawMenuBar();
		void DrawDebugRenderer(float a_DeltaTime, int a_FPS);

	public:
		Event<void(unsigned int)> m_OnInspectorEntitySelected;

	private:
		float m_Time = 0.0f;

		std::vector<std::unique_ptr<GUIWindow>> m_GuiWindows;
	};
}


