#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};
class Dice
{
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;
public:
	Dice();
	~Dice();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
};