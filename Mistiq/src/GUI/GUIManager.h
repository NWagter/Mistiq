#pragma once
#include "Mstqpch.h"
#include "GUIWindow.h"
#include "../../ext/imgui/imgui.h"

namespace Mistiq {
	class GUIManager {
	public:
		GUIManager();
		~GUIManager();

		void Init();
		void Update(float a_DeltaTime);

        ///Draw none static GUI windows
		void DrawMenuBar();

	private:
		float m_Time = 0.0f;

		std::vector<std::unique_ptr<GUIWindow>> m_GuiWindows;
	};
}


