#pragma once

//#include <Windows.h>	// �v���R���p�C���ς݃w�b�_�[�ɒǉ������̂ŃR�����g�A�E�g
//#include <string>	// �v���R���p�C���ς݃w�b�_�[�ɒǉ������̂ŃR�����g�A�E�g

class Window {
public:
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);

	bool ProcessMessage();

private:
	HWND m_hWnd;
};