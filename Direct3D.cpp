#include <d3dcompiler.h>
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"



//変数

namespace Direct3D

{
	ID3D11Device* pDevice_ = nullptr;		//デバイス
	ID3D11DeviceContext* pContext_ = nullptr;		//デバイスコンテキスト
	IDXGISwapChain* pSwapChain_ = nullptr;		//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView_ = nullptr;	//レンダーターゲットビュー

	ID3D11VertexShader* pVertexShader_ = nullptr;	//頂点シェーダー
	ID3D11PixelShader* pPixelShader_ = nullptr;		//ピクセルシェーダー
	ID3D11InputLayout* pVertexLayout_ = nullptr;	//頂点インプットレイアウト
	ID3D11RasterizerState* pRasterizerState_ = nullptr;	//ラスタライザー
}



//初期化

void Direct3D::Initialize(int winW, int winH, HWND hWnd)

{
	DXGI_SWAP_CHAIN_DESC scDesc;

	ZeroMemory(&scDesc, sizeof(scDesc));

	//描画先のフォーマット
	scDesc.BufferDesc.Width = WINDOW_WIDTH;		//画面幅
	scDesc.BufferDesc.Height = WINDOW_HEIGHT;	//画面高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

	//FPS（1/60秒に1回）
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//その他
	scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
	scDesc.OutputWindow = hWnd;		//ウィンドウハンドル
	scDesc.BufferCount = 1;			//バックバッファの枚数
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
	scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
	scDesc.SampleDesc.Quality = 0;		//　〃

	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,				// どのビデオアダプタを使用するか？既定ならばnullptrで
		D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
		nullptr,				// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
		0,					// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
		nullptr,				// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
		0,					// 上の引数でレベルを何個指定したか
		D3D11_SDK_VERSION,			// SDKのバージョン。必ずこの値
		&scDesc,				// 上でいろいろ設定した構造体
		&pSwapChain_,				// 無事完成したSwapChainのアドレスが返ってくる
		&pDevice_,				// 無事完成したDeviceアドレスが返ってくる
		&level,					// 無事完成したDevice、Contextのレベルが返ってくる
		&pContext_);

	//スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）
	ID3D11Texture2D* pBackBuffer;
	pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//レンダーターゲットビューを作成
	
	pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);
	 


	//一時的にバックバッファを取得しただけなので解放
	pBackBuffer->Release();

	//レンダリング結果を表示する範囲
	D3D11_VIEWPORT vp;
	vp.Width = (float)WINDOW_WIDTH;	//幅
	vp.Height = (float)WINDOW_HEIGHT;//高さ
	vp.MinDepth = 0.0f;	//手前
	vp.MaxDepth = 1.0f;	//奥
	vp.TopLeftX = 0;	//左
	vp.TopLeftY = 0;	//上

	//データを画面に描画するための一通りの設定（パイプライン）
	pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);            // 描画先を設定
	pContext_->RSSetViewports(1, &vp);


	//シェーダー準備

	InitShader();
}


void Direct3D::InitShader()

{
	// 頂点シェーダの作成（コンパイル）

	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);
	pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader_);
	pCompileVS->Release();
	
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::XMVECTOR) , D3D11_INPUT_PER_VERTEX_DATA, 0 },//UV座標//位置
		{ "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2 ,	D3D11_INPUT_PER_VERTEX_DATA, 0 },//法線
	};
	
	 pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout_);
	

	ID3DBlob* pCompilePS = nullptr;
	
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader_);
	pCompilePS->Release();

	

	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	pDevice_->CreateRasterizerState(&rdc, &pRasterizerState_);

	//それぞれをデバイスコンテキストにセット
	pContext_->VSSetShader(pVertexShader_, NULL, 0);	//頂点シェーダー
	pContext_->PSSetShader(pPixelShader_, NULL, 0);	//ピクセルシェーダー
	pContext_->IASetInputLayout(pVertexLayout_);	//頂点インプットレイアウト
	pContext_->RSSetState(pRasterizerState_);		//ラスタライザー

}
//描画開始

void Direct3D::BeginDraw()

{
	float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

	//画面をクリア
	pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);
}



//描画終了

void Direct3D::EndDraw()

{
	pSwapChain_->Present(0, 0);
}



//解放処理

void Direct3D::Release()

{
	/*pRasterizerState_->Release();
	pVertexLayout_->Release();
	pPixelShader_->Release();
	pVertexShader_->Release();*/


	SAFE_RELEASE(pRasterizerState_);
	SAFE_RELEASE(pVertexLayout_);
	SAFE_RELEASE(pPixelShader_);
	SAFE_RELEASE(pVertexShader_);

	/*pRenderTargetView_->Release();
	pSwapChain_->Release();
	pContext_->Release();
	pDevice_->Release();*/

	SAFE_RELEASE(pRenderTargetView_);
	SAFE_RELEASE(pSwapChain_);
	SAFE_RELEASE(pContext_);
	SAFE_RELEASE(pDevice_);



}