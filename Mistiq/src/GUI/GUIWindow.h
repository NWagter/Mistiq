#pragma once

class GUIManager;

namespace Mistiq{
	class GUIWindow {
	public:
		GUIWindow();
		virtual ~GUIWindow();

		virtual void Init();
		virtual void Update(float a_DeltaTime);

	public:
		bool m_Open;
	};

    class GUIConsoleWindow final : public GUIWindow
    {
    public:
		GUIConsoleWindow() {}
		~GUIConsoleWindow() {}

        void Init() override;
        void Update(float a_DeltaTime) override;

    private:
		bool m_ClearOnPlay;
		bool m_DisplayTimeStamp;
    };

    class GUIHierarchyWindow final : public GUIWindow
    {
    public:
		GUIHierarchyWindow() {}
		~GUIHierarchyWindow() {}

		void Init() override;
		void Update(float a_DeltaTime) override;
    };

	class GUIInspectorWindow final : public GUIWindow
	{
	public:
		GUIInspectorWindow() {}
		~GUIInspectorWindow() {}

		void Init() override;
		void Update(float a_DeltaTime) override;

		void OnInspectorEntitySelected(unsigned int a_Entity);

	private:
		int m_CurrentSelectedEntity;
	};

    class GUISceneWindow final : public GUIWindow
    {
    public:
		GUISceneWindow() {}
		~GUISceneWindow() {}

		void Init() override;
		void Update(float a_DeltaTime) override;
    };
}
