//�C���N���[�h
#include <Windows.h>
#include "Direct3D.h"
#include "Camera.h"
//#include "Quad.h"
#include "Dice.h"
#include "Sprite.h"

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";  //�E�B���h�E�N���X��
const char* TITLE_NAME = "�T���v���Q�[��";  //�^�C�g����
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���


//Quad *q;
Dice* d;
Sprite* s;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

    //�E�B���h�E�N���X�i�݌v�}�j���쐬
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
    wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
    wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
    wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
    wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
    RegisterClassEx(&wc);  //�N���X��o�^

    //�E�B���h�E�T�C�Y�̌v�Z
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE); //�\���X�^�C���͓���
    int winW = winRect.right - winRect.left;     //�E�B���h�E��
    int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

    //�E�B���h�E���쐬
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //�E�B���h�E�N���X��
        TITLE_NAME,     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW,
        //WS_OVERLAPPEDWINDOW | WS_VISIBLE,//�X�^�C���i���ʂ̃E�B���h�E�j //|VISIBLE,��ǉ����邱�Ƃōŏ�����\���ł���B
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,                 //�E�B���h�E��
        winH,                 //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        hInstance,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );

    //�E�B���h�E��\��
    ShowWindow(hWnd, nCmdShow);

    HRESULT hr; //�������牺��hr�g�����
    //Direct3D������
    hr = Direct3D::Initialize(winW, winH, hWnd);
    if (FAILED(hr))
    {
        PostQuitMessage(0);  //�v���O�����I��
    }

    Camera::Initialize();

    /*Camera::SetPosition(XMFLOAT3(0, 0, 0));
    Camera::SetTarget(XMFLOAT3(0, 0, 0));*/


    // q = new Quad;
   // hr = q->Initialize();

   d = new Dice;
    hr = d->Initialize();

    s = new Sprite;
    hr = s->Initialize();
    if (FAILED(hr))
    {
        PostQuitMessage(0);  //�v���O�����I��
    }


    //���b�Z�[�W���[�v�i�����N����̂�҂j
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
            Camera::Update();



            //�Q�[���̏���
            Direct3D::BeginDraw();



            //�`�揈��
            static float n = 0;
            static float nn = 0;
            n += 0.5;
            nn += 1;
            static float angle = 0;
            angle += 0.05;
            //��]
            XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(angle));
            XMMATRIX matRx = XMMatrixRotationX(XMConvertToRadians(nn / 20));
            // q->Draw(mat);

            //���E
           // XMMATRIX matT = XMMatrixTranslation(0 ,0 ,0);
            XMMATRIX matI = XMMatrixIdentity();
            //q->Draw(mat);

            //�g��k��
            XMMATRIX matS = XMMatrixScaling(0.5, 0.5, 0.0f); //0���ƕ\������Ȃ�

            // XMMATRIX mat = matRx * matR;
            d->Draw(matRx);
           // q->Draw(matR);
            s->Draw(matS);

            //q->Draw(); //Quad��Draw
            Direct3D::EndDraw();

        }
    }

    Direct3D::Release();
    //SAFE_RELEASE(q);
   // SAFE_DELETE(q);
   SAFE_RELEASE(d);
   SAFE_DELETE(d);

    SAFE_RELEASE(s);
    SAFE_DELETE(s);

    return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {

    case WM_DESTROY:
        PostQuitMessage(0);  //�v���O�����I��
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}