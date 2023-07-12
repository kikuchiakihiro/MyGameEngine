#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//前方宣言
class Fbx;
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //開放処理
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;} //開放処理
class Player :
    public GameObject
{
    Fbx* pFbx;
public:
    //コンストラクタ
    //引数：parent  親オブジェクト（SceneManager）
    Player(GameObject* parent);

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};

