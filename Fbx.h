//#pragma once
//
//#include <d3d11.h>
//#include <fbxsdk.h>
//#include <string>
//#include "Transform.h"
//#include "Direct3D.h"
//
//#pragma comment(lib, "LibFbxSDK-Md.lib")
//#pragma comment(lib, "LibXml2-Md.lib")
//#pragma comment(lib, "zlib-Md.lib")
//
//class Fbx
//{
//	struct CONSTANT_BUFFER
//	{
//		XMMATRIX	matWVP;
//		XMMATRIX	matNormal;
//	};
//
//	struct VERTEX
//	{
//		XMFLOAT3 position;
//	};
//
//	int vertexCount_;	//í∏ì_êî
//	int polygonCount_;	//É|ÉäÉSÉìêî
//
//
//	ID3D11Buffer* pVertexBuffer_;
//	ID3D11Buffer* pIndexBuffer_;
//	ID3D11Buffer* pConstantBuffer_;
//
//public:
//
//	Fbx();
//	~Fbx();
//	HRESULT Load(std::string fileName);
//	void InitVertex(fbxsdk::FbxMesh* mesh);
//	void    Draw(Transform& transform);
//	void    Release();
//};