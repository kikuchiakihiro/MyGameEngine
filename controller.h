#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class controller : public GameObject
{
    int camType_;
public:
    //コンストラクタ
    controller(GameObject* parent);

    //デストラクタ
    ~controller();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
