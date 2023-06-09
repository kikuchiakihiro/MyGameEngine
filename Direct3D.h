#pragma once

#include <d3d11.h>
#include <assert.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}


const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ
namespace Direct3D

{
	extern ID3D11Device* pDevice_;
	extern ID3D11DeviceContext* pContext_;
	//extern ID3D11DeviceContext* pContext__;
	//初期化

	void Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備

	void InitShader();

	//描画開始

	void BeginDraw();



	//描画終了

	void EndDraw();



	//解放

	void Release();

};

