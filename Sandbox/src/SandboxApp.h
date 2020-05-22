#pragma once
#include <Mistiq/Application.h>

class SandboxApp : public Mistiq::Application {
public:
	SandboxApp();
	~SandboxApp();

    void Setup() override;
    void Update() override;
    void Clean() override;

private:
	std::vector<std::shared_ptr<Mistiq::GameObject>> m_Player;
};