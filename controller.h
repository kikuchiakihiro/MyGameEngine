#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Controller : public GameObject
{
    int speedx;
    int speedy;
public:
    //コンストラクタ
    Controller(GameObject* parent);

    //デストラクタ
    ~Controller();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};