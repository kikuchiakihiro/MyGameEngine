#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class controller : public GameObject
{
    int camType_;
public:
    //�R���X�g���N�^
    controller(GameObject* parent);

    //�f�X�g���N�^
    ~controller();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
