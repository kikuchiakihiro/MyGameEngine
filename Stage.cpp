#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),hModel_{-1,-1,-1,-1,-1}
{
    
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string  fname_base = "Assets/";
    //���f���f�[�^�̃��[�h
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = Model::Load(fname_base + modelname[i]);
    assert(hModel_[i] >= 0);
    }
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < ZSIZE; x++) {
            table_[x][z] = x % 5;
        }
    }
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



    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            BlockTrans.position_.x = x;
            BlockTrans.position_.z = z;

            int type = table_[x][z];

            Model::SetTransform(hModel_[type], BlockTrans);
            Model::Draw(hModel_[type]);


        }
    }
}
   

//�J��
void Stage::Release()
{
   
}