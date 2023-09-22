#include "Application.h"
//#include <Windows.h>	// プリコンパイル済みヘッダーに追加したのでコメントアウト
//#include <cassert>	// プリコンパイル済みヘッダーに追加したのでコメントアウト

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	
	Application::Instance().Execute();

	CoUninitialize();

	return 0;
}

void Application::Execute() {
	static const int width = 1280;
	static const int height = 720;

	if (!m_window.Create(width, height, L"DX12-framework", L"Window")) {
		assert(0 && "ウィンドウ作成失敗。");
		return;
	}

	if (!GraphicsDevice::Instance().Init(m_window.GetWndHandle(), width, height)) {
		assert(0 && "グラフィックスデバイス初期化失敗。");
		return;
	}

	Mesh mesh;
	mesh.Create(&GraphicsDevice::Instance());

	RenderingSetting renderingSetting = {};
	renderingSetting.InputLayouts = { InputLayout::POSITION };
	renderingSetting.Formats = { DXGI_FORMAT_R8G8B8A8_UNORM };
	renderingSetting.IsDepth = false;
	renderingSetting.IsDepthMask = false;

	Shader shader;
	shader.Create(&GraphicsDevice::Instance(), L"SimpleShader", renderingSetting, {});

	while (true) {
		if (!m_window.ProcessMessage()) {
			break;
		}

		GraphicsDevice::Instance().Prepare();

		shader.Begin(width, height);

		shader.DrawMesh(mesh);

		GraphicsDevice::Instance().ScreenFlip();
	}
}