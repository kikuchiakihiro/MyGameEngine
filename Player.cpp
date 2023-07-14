#include "Player.h"
#include "Player2.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"),pFbx(nullptr)
{
}

void Player::Initialize()
{
	

	pFbx = new Fbx;
	pFbx->Load("Assets\\odden.fbx");
	//this->transform_.position_.x = -2.0f;
	this->transform_.scale_.x = 0.8f;
	this->transform_.scale_.y = 0.8f;
	this->transform_.scale_.z = 0.8f;

	/*Instantiate<Player2>(this);
	GameObject* pCO2 = Instantiate<Player2>(this);
	pCO2->SetPosition(XMFLOAT3(5, 0, 0));*/
}

void Player::Update()
{
	transform_.rotate_.y++;
	/*if (transform_.rotate_.y > 600) {
		KillMe();
	}*/
	if (Input::IsKey(DIK_LEFT)) {
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.position_.x += 0.1f;
	}
	
	if (Input::IsKeyDown(DIK_SPACE)) {
		GameObject* pBullet = Instantiate<Player2>(pParent_);
			pBullet->SetPosition(transform_.position_);
	}
}

void Player::Draw()
{
	pFbx->Draw(transform_);

}

void Player::Release()
{
	//pFbx->Release();
	//SAFE_RELEASE(pFbx);
	////delete pFbx;
}