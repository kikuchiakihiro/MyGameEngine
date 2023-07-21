#include "Enemy.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent):GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Assets\\odden.fbx");
	this->transform_.position_.z = 5.0f;
	this->transform_.scale_.x = 0.5f;
	this->transform_.scale_.y = 0.5f;
	this->transform_.scale_.z = 0.5f;
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
