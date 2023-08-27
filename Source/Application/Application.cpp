#include "Application.h"
//#include <Windows.h>	// �v���R���p�C���ς݃w�b�_�[�ɒǉ������̂ŃR�����g�A�E�g
//#include <cassert>	// �v���R���p�C���ς݃w�b�_�[�ɒǉ������̂ŃR�����g�A�E�g

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::Instance().Execute();

	return 0;
}

void Application::Execute() {
	static const int width = 1280;
	static const int height = 720;

	if (!m_window.Create(width, height, L"DX12-framework", L"Window")) {
		assert(0 && "�E�B���h�E�쐬���s�B");
		return;
	}

	while (true) {
		if (!m_window.ProcessMessage())
		{
			break;
		}
	}
}