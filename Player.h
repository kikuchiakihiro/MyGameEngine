#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//�O���錾
class Fbx;
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //�J������
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;} //�J������
class Player :
    public GameObject
{
    Fbx* pFbx;
public:
    //�R���X�g���N�^
    //�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
    Player(GameObject* parent);

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};

