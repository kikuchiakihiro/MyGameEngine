#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "resource.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
           /* table_[i][f];
            table_[i][f].height = 1;*/
            SetBlockHeight(x, z, x%3);
        }
    }
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
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
    //モデルデータのロード
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = Model::Load(fname_base + modelname[i]);
    assert(hModel_[i] >= 0);
    }
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlock(x, z, WATER);
        }
    }
}

//更新
void Stage::Update()
{
    static int a = 2;
    if (Input::IsKeyDown(DIK_U))
            {
        SetBlockHeight(7,7,a++);
        SetBlockHeight(8, 8, a++);
            }
}

//描画
void Stage::Draw()
{
    Transform BlockTrans;//Transform型の変数
    //Transform型 -> 位置,向き,大きさを扱う型



    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            

            for (int y = 0; y < table_[x][z].height+1; y++) {

                BlockTrans.position_.x = x;
                BlockTrans.position_.z = z;
                BlockTrans.position_ = { (float)x,(float)y,(float)z };
                Model::SetTransform(table_[x][z].blocks, BlockTrans);
                Model::Draw(table_[x][z].blocks);

            }
        }
    }
}
   

//開放
void Stage::Release()
{
   
}

void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].blocks = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}


BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lparam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
            //radio
        SendMessage(GetDlgItem(hDlg, IDC_RADIOUP), BM_SETCHECK, BST_CHECKED, BST_UNCHECKED);
        return TRUE;
        SendMessage(GetDlgItem(hDlg, IDC_RADIOUP), BM_SETCHECK, BST_CHECKED, BST_UNCHECKED);
    }
    return FALSE;
}