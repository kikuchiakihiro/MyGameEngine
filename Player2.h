#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//�O���錾
class Fbx;

class Player2 :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;
public:
    //�R���X�g���N�^
    //�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
    Player2(GameObject* parent);

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};

