﻿#pragma once

class Mesh {
public:
	void Create(GraphicsDevice* pGraphicsDevice);

	void DrawInstanced()const;

private:
	GraphicsDevice* m_pDevice = nullptr;
	ComPtr<ID3D12Resource>		m_pVBuffer = nullptr;
	ComPtr<ID3D12Resource>		m_pIBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW	m_vbView;
	D3D12_INDEX_BUFFER_VIEW		m_ibView;

	std::array<Math::Vector3, 3> m_vertices;
};