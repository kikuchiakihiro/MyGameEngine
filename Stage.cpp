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
   
        hModel_ = Model::Load("Assets/BoxDefault.fbx");
        assert(hModel_ >= 0);
    
    //���f���f�[�^�̃��[�h
  
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Transform BlockTrans;//Transform�^�̕ϐ������
    //Transform�^�́A�ʒu�����傫���Ȃǂ������^

    Transform blockTrans;

    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            blockTrans.position_.x = x;
            blockTrans.position_.z = z;

            int type = table_[x][z];

            Model::SetTransform(hModel_, blockTrans);
            Model::Draw(hModel_);
        }
    }

}

//�J��
void Stage::Release()
{
}