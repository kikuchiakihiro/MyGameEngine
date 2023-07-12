#include "Player.h"
#include "Player2.h"
#include "Engine/Input.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"),pFbx(nullptr)
{
}

void Player::Initialize()
{
	Instantiate<Player2>(this);

	pFbx = new Fbx;
	pFbx->Load("Assets\\odden.fbx");
	this->transform_.scale_.x = 0.8f;
	this->transform_.scale_.y = 0.8f;
	this->transform_.scale_.z = 0.8f;
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