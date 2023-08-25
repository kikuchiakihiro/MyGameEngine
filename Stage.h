#pragma once
#include "Engine/GameObject.h"

enum
{
    TYPE_FLOOR,
    TYPE_WL,
    TYPE_MAX
};





//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_;
    int** table_;
    int x, z;

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

    bool IsWall(int x, int z);
};