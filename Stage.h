#pragma once
#include "Engine/GameObject.h"
#include "Windows.h"
namespace {
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT = 0,
        BRICK,
        GRASS,
        SAND,
        WATER
    };
    const char* blockName[] = { "デフォルト","レンガ", "草", "砂", "水" };
}



//◆◆◆を管理するクラス
class Stage : public GameObject
{
  
    int hModel_[MODEL_NUM];
    

    struct BLOCKHEIGHT{
        BLOCKTYPE blocks;
             int height;
             
    } table_[XSIZE][ZSIZE];
    int mode_ = 0;
    
    int select_ = 0;
public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
    void SaveBlockData();
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    //BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};