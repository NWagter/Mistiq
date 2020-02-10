#include "SandboxApp.h"

SandboxApp::SandboxApp()
{
}

SandboxApp::~SandboxApp()
{
}

void main()
{
	SandboxApp* app = new SandboxApp();
	app->Setup();

    while(app->IsOpen()) {
		app->Update();
    }

	app->Clean();
	delete app;
}