#pragma once

#include <Windows.h>
#include <string>

class Window {
public:
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);

	bool ProcessMessage();

private:
	HWND m_hWnd;
};