#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("assets/BoxDefault.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Stage::Update()
{
   
}

//�`��
void Stage::Draw()
{
    Transform BlockTrans;//Transfrom�^�̕ϐ�
    //Transform�^ -> �ʒu,����,�傫���������^



    for (int w = 0; w < 15; w++)
    {
        for (int z = 0; z < 15; z++)
        {
            BlockTrans.position_.x = w;
            BlockTrans.position_.z = z;



            Model::SetTransform(hModel_, BlockTrans);
            Model::Draw(hModel_);



        }
    }
}
   

//�J��
void Stage::Release()
{
   
}