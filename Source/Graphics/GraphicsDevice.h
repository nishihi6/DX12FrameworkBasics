#pragma once

//#include "RTVHeap/RTVHeap.h"

class GraphicsDevice {
public:
	bool Init(HWND hWnd, int w, int h);

	void ScreenFlip();

	void WaitForCommandQueue();

	ID3D12Device8* GetDevice()const {
		return m_pDevice.Get();
	}

	ID3D12GraphicsCommandList6* GetCmdList()const {
		return m_pCmdList.Get();
	}

	static GraphicsDevice& Instance() {
		static GraphicsDevice instance;
		return instance;
	}
private:
	bool CreateFactory();

	bool CreateDevice();

	bool CreateCommandList();

	bool CreateSwapchain(HWND hWnd, int width, int height);

	bool CreateSwapchainRTV();

	bool CreateFence();

	void SetResourceBarrier(ID3D12Resource* pResource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);

	void EnableDebugLayer();

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

	std::array<ComPtr<ID3D12Resource>, 2>	m_pSwapchainBuffers;
	std::unique_ptr<RTVHeap>	m_pRTVHeap = nullptr;

	ComPtr<ID3D12Fence>		m_pFence = nullptr;
	UINT64		m_fenceVal = 0;

	GraphicsDevice() {}
	~GraphicsDevice() {}
};