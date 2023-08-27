#include "Application.h"
//#include <Windows.h>	// プリコンパイル済みヘッダーに追加したのでコメントアウト
//#include <cassert>	// プリコンパイル済みヘッダーに追加したのでコメントアウト

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::Instance().Execute();

	return 0;
}

void Application::Execute() {
	static const int width = 1280;
	static const int height = 720;

	if (!m_window.Create(width, height, L"DX12-framework", L"Window")) {
		assert(0 && "ウィンドウ作成失敗。");
		return;
	}

	while (true) {
		if (!m_window.ProcessMessage())
		{
			break;
		}
	}
}