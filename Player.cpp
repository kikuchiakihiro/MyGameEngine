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

	Instantiate<Player2>(this);
	GameObject* pCO2 = Instantiate<Player2>(this);
	pCO2->SetPosition(XMFLOAT3(5, 0, 0));
}

void Player::Update()
{
	transform_.rotate_.y++;

	if (Input::IsKeyDown(DIK_ESCAPE)) {
		KillMe();
	}
}

void Player::Draw()
{
	pFbx->Draw(transform_);

}

void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}