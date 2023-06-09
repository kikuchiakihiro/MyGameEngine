#pragma once

#include <d3d11.h>
#include <assert.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}


const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���
namespace Direct3D

{
	extern ID3D11Device* pDevice_;
	extern ID3D11DeviceContext* pContext_;
	//extern ID3D11DeviceContext* pContext__;
	//������

	void Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����

	void InitShader();

	//�`��J�n

	void BeginDraw();



	//�`��I��

	void EndDraw();



	//���

	void Release();

};

