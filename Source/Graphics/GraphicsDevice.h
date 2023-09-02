#pragma once

class GraphicsDevice {
public:
	bool Init();

	static GraphicsDevice& Instance() {
		static GraphicsDevice instance;
		return instance;
	}
private:
	bool CreateFactory();

	bool CreateDevice();

	bool CreateCommandList();

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