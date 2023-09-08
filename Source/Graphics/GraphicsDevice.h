#pragma once

class GraphicsDevice {
public:
	bool Init(HWND hWnd, int w, int h);

	static GraphicsDevice& Instance() {
		static GraphicsDevice instance;
		return instance;
	}
private:
	bool CreateFactory();

	bool CreateDevice();

	bool CreateCommandList();

	bool CreateSwapchain(HWND hWnd, int width, int height);

	enum class GPUTier {
		NVIDIA,
		Amd,
		Intel,
		Arm,
		Qualcomm,
		Kind,
	};

	ComPtr<ID3D12Device8>		m_pDevice = nullptr;
	ComPtr<IDXGIFactory6>		m_pDxgiFactory = nullptr;
	
	ComPtr<ID3D12CommandAllocator>			m_pCmdAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList6>		m_pCmdList = nullptr;
	ComPtr<ID3D12CommandQueue>				m_pCmdQueue = nullptr;
	
	ComPtr<IDXGISwapChain4>		m_pSwapChain = nullptr;

	GraphicsDevice() {}
	~GraphicsDevice() {}
};