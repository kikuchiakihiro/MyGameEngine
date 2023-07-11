#include "Player.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"),pFbx(nullptr)
{
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets\\odden.fbx");
	this->transform_.scale_.x = 0.8f;
	this->transform_.scale_.y = 0.8f;
	this->transform_.scale_.z = 0.8f;
}

void Player::Update()
{
	this->transform_.rotate_.y++;
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