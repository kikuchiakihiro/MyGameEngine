#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//前方宣言
class Fbx;

class Player2 :
    public GameObject
{
    Fbx* pFbx;
    int hModel_;
public:
    //コンストラクタ
    //引数：parent  親オブジェクト（SceneManager）
    Player2(GameObject* parent);

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};

