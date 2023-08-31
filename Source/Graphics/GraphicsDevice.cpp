#include "GraphicsDevice.h"

bool GraphicsDevice::Init() {
	if (!CreateFactory()) {
		assert(0 && "ファクトリー作成失敗");
		return false;
	}

	if (!CreateDevice()) {
		assert(0 && "D3D12デバイス作成失敗");
		return false;
	}

	return true;
}

bool GraphicsDevice::CreateFactory() {
	UINT flagsDXGI = 0;
	flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
	auto result = CreateDXGIFactory2(flagsDXGI, IID_PPV_ARGS(m_pDxgiFactory.GetAddressOf()));

	if (result) {
		return false;
	}

	return true;
}

bool GraphicsDevice::CreateDevice() {
	ComPtr<IDXGIAdapter> pSelectAdapter = nullptr;
	std::vector<ComPtr<IDXGIAdapter>> pAdapters;
	std::vector<DXGI_ADAPTER_DESC> descs;

	for (UINT index = 0; 1; ++index) {
		pAdapters.push_back(nullptr);
		HRESULT ret = m_pDxgiFactory->EnumAdapters(index, &pAdapters[index]);

		if (ret == DXGI_ERROR_NOT_FOUND) { break; }

		descs.push_back({});
		pAdapters[index]->GetDesc(&descs[index]);
	}

	GPUTier gpuTier = GPUTier::Kind;

	for (int i = 0; i < descs.size(); ++i) {
		if (std::wstring(descs[i].Description).find(L"NVIDIA") != std::wstring::npos) {
			pSelectAdapter = pAdapters[i];
			break;
		} else if (std::wstring(descs[i].Description).find(L"Amd") != std::wstring::npos) {
			if (gpuTier > GPUTier::Amd) {
				pSelectAdapter = pAdapters[i];
				gpuTier = GPUTier::Amd;
			}
		} else if (std::wstring(descs[i].Description).find(L"Intel") != std::wstring::npos) {
			if (gpuTier > GPUTier::Intel) {
				pSelectAdapter = pAdapters[i];
				gpuTier = GPUTier::Intel;
			}
		} else if (std::wstring(descs[i].Description).find(L"Arm") != std::wstring::npos) {
			if (gpuTier > GPUTier::Arm) {
				pSelectAdapter = pAdapters[i];
				gpuTier = GPUTier::Arm;
			}
		} else if (std::wstring(descs[i].Description).find(L"Qualcomm") != std::wstring::npos) {
			if (gpuTier > GPUTier::Qualcomm) {
				pSelectAdapter = pAdapters[i];
				gpuTier = GPUTier::Qualcomm;
			}
		}
	}

	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;
	for (auto lv : levels) {
		if (D3D12CreateDevice(pSelectAdapter.Get(), lv, IID_PPV_ARGS(&m_pDevice)) == S_OK) {
			featureLevel = lv;
			break;
		}
	}

	return true;
}