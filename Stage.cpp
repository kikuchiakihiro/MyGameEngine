#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"
#include "Engine/Direct3D.h"
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
            SetBlockHeight(x, z, 0);
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
            SetBlock(x, z, DEFAULT);
        }
    }
}

//更新
void Stage::Update()
{
    
    if (!Input::IsMouseButtonDown(0)) {
        return;
   }
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);

    XMMATRIX vp =
    {
        w, 0, 0, 0,
        0,-h, 0, 0,
        0, 0, 1, 0,
        w, h, 0, 1
    };
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
        XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
        XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
        XMFLOAT3 mousePosFront = Input::GetMousePosition();
        mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);

    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);

    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);

    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);


        for (int x = 0; x < 15; x++) {
            for (int z = 0; z < 15; z++) {
                for (int y = 0; y < table_[x][z].height + 1; y++) {
                    RayCastData data{};
                    XMStoreFloat4(&data.start, vMouseFront);
                    XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
                    Transform trans;
                   trans.position_.x = x;
                   trans.position_.y = y;
                   trans.position_.z = z;
                    Model::SetTransform(hModel_[0], trans);

                    Model::RayCast(hModel_[0], data);

                    if (data.hit) {

                        switch (mode_)
                        {
                        case 0:
                            table_[x][z].height++;
                            break;
                        case 1:
                            if (table_[x][z].height > 0)
                                table_[x][z].height--;
                            break;
                        case 2:  
                                table_[x][z].blocks = (BLOCKTYPE)hModel_[select_];
                 
                            break;
                        }
                        return;
                        }

                        
                    }
                    
                }
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




void Stage::SaveBlockData()
{
    char fileName[MAX_PATH] = "SaveData.map";  //ファイル名を入れる変数

    //「ファイルを保存」ダイアログの設定
    OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
    ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
    ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
    ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
        TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
    ofn.lpstrFile = fileName;               	//ファイル名
    ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
    ofn.lpstrDefExt = "map";                  	//デフォルト拡張子

    //「ファイルを保存」ダイアログ
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    if (selFile == FALSE) return;

    HANDLE hFile;        //ファイルのハンドル
    hFile = CreateFile(
        "mapdata.txt",                 //ファイル名
        GENERIC_WRITE,           //アクセスモード（書き込み用）
        0,                      //共有（なし）
        NULL,                   //セキュリティ属性（継承しない）
        CREATE_ALWAYS,           //作成方法
        FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
        NULL);  //拡張属性（なし）
        
    string 
}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
            //radio
        SendMessage(GetDlgItem(hDlg, IDC_RADIOUP), BM_SETCHECK, BST_CHECKED,0);
        
        for (int i = 0; i < MODEL_NUM; i++) {
            SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)blockName[i]);

        }
        
      
        
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
        return TRUE;

    case WM_COMMAND:

        
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);
        select_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);
       

        if (IsDlgButtonChecked(hDlg, IDC_RADIOUP)) {
            mode_ = 0;
        }
        if (IsDlgButtonChecked(hDlg, IDC_RADIODOWN)) {
            mode_ = 1;
        }
        if (IsDlgButtonChecked(hDlg, IDC_RADIOCange)) {
            mode_ = 2;
        }
        return TRUE;
        
    }
    return FALSE;

   
}

