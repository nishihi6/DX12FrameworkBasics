//#include <Windows.h>	// �v���R���p�C���ς݃w�b�_�[�ɒǉ������̂ŃR�����g�A�E�g
#include "Window.h"

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

bool Window::Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName) {
	HINSTANCE hInst = GetModuleHandle(0);

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;
	wc.lpszClassName = windowClassName.c_str();
	wc.hInstance = hInst;

	if (!RegisterClassEx(&wc)) {
		return false;
	}

	m_hWnd = CreateWindow(
		windowClassName.c_str(),							// �E�B���h�E�N���X��
		titleName.c_str(),									// �E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,				// �E�B���h�E�^�C�v�i�W���^�C�v�j
		0,													// �E�B���h�E�̈ʒu�i�w�j
		0,													// �E�B���h�E�̈ʒu�i�x�j						
		clientWidth,										// �E�B���h�E�̕�
		clientHeight,										// �E�B���h�E�̍���			
		nullptr,											// �e�E�B���h�E�̃n���h��
		nullptr,											// ���j���[�̃n���h��
		hInst,												// �C���X�^���X�n���h�� 
		this
	);

	if (m_hWnd == nullptr) {
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);

	UpdateWindow(m_hWnd);

	return true;
}

bool Window::ProcessMessage() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}