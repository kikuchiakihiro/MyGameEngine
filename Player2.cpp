#include "Player2.h"

Player2::Player2(GameObject* parent) :GameObject(parent, "Player2"), pFbx(nullptr)
{
}

void Player2::Initialize()
{

	pFbx = new Fbx;
	pFbx->Load("Assets\\odden.fbx");
	this->transform_.position_.x = -5.0f;
	this->transform_.scale_.x = 0.2f;
	this->transform_.scale_.y = 0.2f;
	this->transform_.scale_.z = 0.2f;
}

void Player2::Update()
{
	transform_.rotate_.y++;
	if (transform_.rotate_.y > 300) {
		KillMe();
	}
}

void Player2::Draw()
{
	pFbx->Draw(transform_);
}

void Player2::Release()
{
	/*pFbx->Release();
	delete pFbx;*/
}