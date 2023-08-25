#include "Stage.h"
#include "Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
   
        hModel_ = Model::Load("Assets/BoxDefault.fbx");
        assert(hModel_ >= 0);
    
    //モデルデータのロード
  
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Transform BlockTrans;//Transform型の変数を作る
    //Transform型は、位置向き大きさなどを扱う型

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

//開放
void Stage::Release()
{
}