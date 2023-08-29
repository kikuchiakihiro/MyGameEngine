 //#include "controller.h"
//#include "Engine/Input.h"
//#include "Engine/Camera.h"
//
//
////�R���X�g���N�^
//controller::controller(GameObject* parent)
//    :GameObject(parent, "controller")
//{
//}
//
////�f�X�g���N�^
//controller::~controller()
//{
//}
//
////������
//void controller::Initialize()
//{
//}
//
////�X�V
//void controller::Update()
//{
//    //A��������Ă�����
//    if (Input::IsKey(DIK_UP))
//    {
//        transform_.rotate_.x += 1.0f;
//    }
//    //D��������Ă�����
//    if (Input::IsKey(DIK_DOWN))
//    {
//        transform_.rotate_.x -= 1.0f;
//    }
//    //A��������Ă�����
//    if (Input::IsKey(DIK_LEFT))
//    {
//        transform_.rotate_.y -= 1.0f;
//    }
//    //D��������Ă�����
//    if (Input::IsKey(DIK_RIGHT))
//    {
//        transform_.rotate_.y += 1.0f;
//    }
//
//    
//
//
//
//    //��Ԃ̌��݈ʒu���x�N�g���^�ɕϊ�����
//    XMVECTOR vTankPos = XMLoadFloat3(&transform_.position_);
//    //1�t���[�����Ƃ̈ړ��x�N�g�� 4����͎̂l�����܂őΉ����Ă��邩��ł���{�͎g��Ȃ� x y z�̏��ɂȂ��Ă�
//    XMVECTOR vTankMove = { 0.0f ,0.0f ,0.05f , 0.0f };//z����0.1�Ȃ̂ŉ������ɐi��ł���
//    //XMMATRIX�͍s��������^
//    XMMATRIX mRotY;
//    XMMATRIX mRotX;
//    //������transform_.rotate_y�x��]������s����쐬
//    mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
//    mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
//
//
//    //�ړ��x�N�g����ό`(��ԂƓ��������ɉ�])������  �x�N�g�����s��ɕϊ��@�s��ɕϊ����邱�Ƃňړ������邱�Ƃ��ł���悤�ɂȂ�
//    vTankMove = XMVector3TransformCoord(vTankMove, mRotY);//�x�N�g�������s�񂍂ŕό`
//
//
//    //W��������Ă�����
//    if (Input::IsKey(DIK_W))
//    {
//        vTankPos += vTankMove;
//
//    }
//
//
//
//    //W��������Ă�����
//    if (Input::IsKey(DIK_S))
//    {
//        vTankPos -= vTankMove;
//
//    }
//
//
//
//    //���ݒn���x�N�g�����炢����transform_.position_�ɖ߂�
//    XMStoreFloat3(&transform_.position_, vTankPos);
//
//    //�J�����̃|�W�V���� tank�ɒǏ]����悤�ɂȂ��Ă�
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
////�`��
//void controller::Draw()
//{
//}
//
////�J��
//void controller::Release()
//{
//}

#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

#define SPEED = 1;

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
}

//�X�V
void Controller::Update()
{
    //����]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    //�E��]
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
    
    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
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
   
    //���݈ʒu���x�N�g���ɂ��Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�O��ړ��x�N�g��
    XMFLOAT3 frontMove = { 0, 0, 0.1f };                //��������XMFLOAT3�\���̂�p�ӂ�
    XMVECTOR vMove = XMLoadFloat3(&frontMove);               //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotate);    //��Ԃ̌����ɍ��킹�ĉ�]


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

    //���E�ړ��x�N�g��
    XMFLOAT3 rightMove = { 0.1f, 0, 0 };                //�E������XMFLOAT3�\���̂�p�ӂ�
    vMove = XMLoadFloat3(&rightMove);               //������x�N�g���ɂ���
    vMove = XMVector3TransformCoord(vMove, mRotate);    //��Ԃ̌����ɍ��킹�ĉ�]


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


    //�J����
    XMVECTOR vCam = XMVectorSet(0, 13, -13, 0);
    vCam = XMVector3TransformCoord(vCam, mRotX*mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(XMLoadFloat3(&camPos));
    Camera::SetTarget(XMLoadFloat3(&transform_.position_));        //�J�����̏œ_�̓v���C���[�̈ʒu
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}