#pragma once
#include "Mstqpch.h"

class GUIManager;

namespace Mistiq{
	class GUIWindow {
	public:
		GUIWindow();
		virtual ~GUIWindow();

		virtual void Init(std::shared_ptr<GUIManager> a_GuiManager);
		virtual void Update(float a_DeltaTime);
	};
}
