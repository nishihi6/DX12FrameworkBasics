#pragma once
#include "../System/Window/Window.h"

class Application {
public:
	void Execute();

	static Application& Instance()
	{
		static Application instance;
		return instance;
	}
private:
	Window m_window;

	Application() {}
};