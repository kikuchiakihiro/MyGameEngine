#pragma once

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���
namespace Direct3D

{
	
	//������

	void Initialize(int winW, int winH, HWND hWnd);



	//�`��J�n

	void BeginDraw();



	//�`��I��

	void EndDraw();



	//���

	void Release();

};

