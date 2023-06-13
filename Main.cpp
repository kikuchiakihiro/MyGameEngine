#include <Windows.h>
#include <iostream>
#include "Direct3D.h"
#include "Quad.h"
#include "Camera.h"
#include "Texture.h"
#include "Dice.h"
//#include <d3d11.h>
//#pragma comment(lib, "d3d11.lib")

const char* WIN_CLASS_NAME = "SampleGame";
const char* TITLE_NAME = "サンプルゲーム";
//const int WINDOW_WIDTH = 800;  //ウィンドウの幅
//const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//ID3D11Device* pDevice_;		//デバイス
//ID3D11DeviceContext* pContext_;		//デバイスコンテキスト
//IDXGISwapChain* pSwapChain_;		//スワップチェイン
//ID3D11RenderTargetView* pRenderTargetView_;	//レンダーターゲットビュー

Dice* q;


//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）


	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

  //ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME ,         //ウィンドウクラス名
		TITLE_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);
	
	
	q = new Dice;
	

  //ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(q->Initialize()))
	{
		return 0;
	}
	Camera::Initialize();
	

	
  //メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//ゲームの処理
			//背景の色


			Camera::Update();
			//描画処理
			Direct3D::BeginDraw();
			static int a=0;
		    a += 1;

			XMMATRIX matS = XMMatrixRotationZ(XMConvertToRadians(a / 15));
			XMMATRIX matT = XMMatrixRotationY(XMConvertToRadians(a /15));
			XMMATRIX matR = XMMatrixRotationX(XMConvertToRadians(a/20));
			XMMATRIX matSRT = matS * matR * matT;//拡大　回転　移動
			q->Draw(matSRT);
			//スワップ（バックバッファを表に表示する）
			
			Direct3D::EndDraw();
		}
	}
	SAFE_RELEASE(q);
	SAFE_DELETE(q);
	Direct3D::Release();
	//q->Release();
	//delete q;

	q = nullptr;
	return 0;
}
//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	

	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}