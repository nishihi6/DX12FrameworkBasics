#include "GraphicsDevice.h"

bool GraphicsDevice::Init() {
	if (!CreateFactory()) {
		assert(0 && "�t�@�N�g���[�쐬���s");
		return false;
	}

	if (!CreateDevice()) {
		assert(0 && "D3D12�f�o�C�X�쐬���s");
		return false;
	}

	if (!CreateCommandList()) {
		assert(0 && "�R�}���h���X�g�̍쐬���s");
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

bool GraphicsDevice::CreateCommandList() {
	auto hr = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pCmdAllocator));

	if (FAILED(hr)) {
		return false;
	}

	hr = m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pCmdAllocator.Get(), nullptr, IID_PPV_ARGS(&m_pCmdList));

	if (FAILED(hr)) {
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;				// �^�C���A�E�g�Ȃ�
	cmdQueueDesc.NodeMask = 0;										// �A�_�v�^�[��1�����g��Ȃ��Ƃ���0�ł���
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	// �v���C�I���e�B�͓��Ɏw��Ȃ�
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;				// �R�}���h���X�g�ƍ��킹��

	// �L���[����
	hr = m_pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_pCmdQueue));

	if (FAILED(hr)) {
		return false;
	}

	return true;
}