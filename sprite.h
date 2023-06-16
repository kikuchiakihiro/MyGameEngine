#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}


class Sprite
{

	struct CONSTANT_BUFFER
		{
			XMMATRIX	matW;
		};
		struct VERTEX
		{
			XMVECTOR position;
			XMVECTOR uv;
		};
protected:
		ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
		ID3D11Buffer* pIndexBuffer_;
		ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

		Texture* pTexture_;
public:
	Sprite();
	~Sprite();

		HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();

private:

	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);
	void SetBufferToPipeline();

};

