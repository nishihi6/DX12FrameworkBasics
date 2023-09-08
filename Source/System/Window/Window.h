#pragma once

//#include <Windows.h>	// プリコンパイル済みヘッダーに追加したのでコメントアウト
//#include <string>	// プリコンパイル済みヘッダーに追加したのでコメントアウト

class Window {
public:
	HWND GetWndHandle() const {
		return m_hWnd;
	}
	
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);

	bool ProcessMessage();

private:
	HWND m_hWnd;
};