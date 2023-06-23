#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Direct3D.h"
#include "Texture.h"

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数


	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	Texture* pTexture_;

public:

	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);
	HRESULT InitConstant(fbxsdk::FbxMesh* mesh);
	void    Draw(Transform& transform);
	void    Release();

	HRESULT LoadTexture();

private:
	//void PassDataToCB(Transform transform);	//コンスタントバッファに各種情報を渡す
	//void SetBufferToPipeline();
};