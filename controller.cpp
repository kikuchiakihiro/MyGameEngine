 //#include "controller.h"
//#include "Engine/Input.h"
//#include "Engine/Camera.h"
//
//
////コンストラクタ
//controller::controller(GameObject* parent)
//    :GameObject(parent, "controller")
//{
//}
//
////デストラクタ
//controller::~controller()
//{
//}
//
////初期化
//void controller::Initialize()
//{
//}
//
////更新
//void controller::Update()
//{
//    //Aが押されていたら
//    if (Input::IsKey(DIK_UP))
//    {
//        transform_.rotate_.x += 1.0f;
//    }
//    //Dが押されていたら
//    if (Input::IsKey(DIK_DOWN))
//    {
//        transform_.rotate_.x -= 1.0f;
//    }
//    //Aが押されていたら
//    if (Input::IsKey(DIK_LEFT))
//    {
//        transform_.rotate_.y -= 1.0f;
//    }
//    //Dが押されていたら
//    if (Input::IsKey(DIK_RIGHT))
//    {
//        transform_.rotate_.y += 1.0f;
//    }
//
//    
//
//
//
//    //戦車の現在位置をベクトル型に変換する
//    XMVECTOR vTankPos = XMLoadFloat3(&transform_.position_);
//    //1フレームごとの移動ベクトル 4つあるのは四次元まで対応しているからでも基本は使わない x y zの順になってる
//    XMVECTOR vTankMove = { 0.0f ,0.0f ,0.05f , 0.0f };//z軸が0.1なので奥方向に進んでいく
//    //XMMATRIXは行列を扱う型
//    XMMATRIX mRotY;
//    XMMATRIX mRotX;
//    //ここでtransform_.rotate_y度回転させる行列を作成
//    mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
//    mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
//
//
//    //移動ベクトルを変形(戦車と同じ向きに回転)させる  ベクトルを行列に変換　行列に変換することで移動させることができるようになる
//    vTankMove = XMVector3TransformCoord(vTankMove, mRotY);//ベクトルｖを行列ｍで変形
//
//
//    //Wが押されていたら
//    if (Input::IsKey(DIK_W))
//    {
//        vTankPos += vTankMove;
//
//    }
//
//
//
//    //Wが押されていたら
//    if (Input::IsKey(DIK_S))
//    {
//        vTankPos -= vTankMove;
//
//    }
//
//
//
//    //現在地をベクトルからいつものtransform_.position_に戻す
//    XMStoreFloat3(&transform_.position_, vTankPos);
//
//    //カメラのポジション tankに追従するようになってる
//    Camera::SetTarget(transform_.position_);
//
//    XMVECTOR vCam = { 0, 6, -10, 0 };
//    vCam = XMVector3TransformCoord(vCam, mRotY);
//    XMFLOAT3 camPos;
//    XMStoreFloat3(&camPos, vTankPos + vCam);
//    Camera::SetPosition(camPos);
//
//    XMVECTOR vCamX = { 0, 6, -10, 0 };
//    vCamX = XMVector3TransformCoord(vCamX, mRotX);
//    XMFLOAT3 camPosX;
//    XMStoreFloat3(&camPosX, vTankPos + vCamX);
//    Camera::SetPosition(camPosX);
//}
//
////描画
//void controller::Draw()
//{
//}
//
////開放
//void controller::Release()
//{
//}

#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

#define SPEED = 1;

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
}

//更新
void Controller::Update()
{
    //左回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //右回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }


    if (Input::IsKey(DIK_UP)&& transform_.rotate_.x <= 45)
    {

    transform_.rotate_.x += 1;
            
    }
    if (Input::IsKey(DIK_DOWN)&& transform_.rotate_.x >= -45)
    {

        transform_.rotate_.x -= 1;
    }
    
    //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    /*if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1.0f;
    }

    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1.0f;
    }*/
   
    //現在位置をベクトルにしておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //前後移動ベクトル
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //奥向きのXMFLOAT3構造体を用意し
    XMVECTOR vMove = XMLoadFloat3(&frontMove);               //それをベクトルにする
    vMove = XMVector3TransformCoord(vMove, mRotate);    //戦車の向きに合わせて回転


    if (Input::IsKey(DIK_W))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_S))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //左右移動ベクトル
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //右向きのXMFLOAT3構造体を用意し
    vMove = XMLoadFloat3(&rightMove);               //それをベクトルにする
    vMove = XMVector3TransformCoord(vMove, mRotate);    //戦車の向きに合わせて回転


    if (Input::IsKey(DIK_D))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::IsKey(DIK_A))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }


    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 13, -13, 0);
    vCam = XMVector3TransformCoord(vCam, mRotX*mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));        //カメラの焦点はプレイヤーの位置
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}