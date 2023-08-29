#pragma once
#include "Engine/GameObject.h"

enum
{
    TYPE_FLOOR,
    TYPE_WL,
    TYPE_MAX
};
//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[TYPE_MAX];
    int** table_;
    int width_, height_;
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};