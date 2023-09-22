#pragma once

#include "Pipeline/Pipeline.h"
#include "RootSignature/RootSignature.h"

struct RenderingSetting {
	std::vector<InputLayout> InputLayouts;
	std::vector<DXGI_FORMAT> Formats;
	CullMode CullMode = CullMode::Back;
	BlendMode BlendMode = BlendMode::Alpha;
	PrimitiveTopologyType PrimitiveTopologyType = PrimitiveTopologyType::Triangle;
	bool IsDepth = true;
	bool IsDepthMask = true;
	int RTVCount = 1;
	bool IsWireFrame = false;
};

class Shader {
public:
	void Create(GraphicsDevice* pGraphicsDevice, const std::wstring& filePath, const RenderingSetting& renderingSetting, const std::vector<RangeType>& rangeTypes);

	void Begin(int w, int h);

	void DrawMesh(const Mesh& mesh);

private:
	void LoadShaderFile(const std::wstring& filePath);

	GraphicsDevice* m_pDevice = nullptr;

	std::unique_ptr<Pipeline>		m_upPipeline = nullptr;
	std::unique_ptr<RootSignature>	m_upRootSignature = nullptr;

	ID3DBlob* m_pVSBlob = nullptr;		// ���_�V�F�[�_�[
	ID3DBlob* m_pHSBlob = nullptr;		// �n���V�F�[�_�[
	ID3DBlob* m_pDSBlob = nullptr;		// �h���C���V�F�[�_�[
	ID3DBlob* m_pGSBlob = nullptr;		// �W�I���g���V�F�[�_�[
	ID3DBlob* m_pPSBlob = nullptr;		// �s�N�Z���V�F�[�_�[
};