#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
Enemy::Enemy(GameObject* parent):GameObject(parent,"Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Assets\\odden.fbx");
	this->transform_.position_.z = 5.0f;
	this->transform_.scale_.x = 0.5f;
	this->transform_.scale_.y = 0.5f;
	this->transform_.scale_.z = 0.5f;

	SphereCollider* col = new SphereCollider(1.0);
	AddCollider(col);
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

void Enemy::OnCollision(GameObject* pTarget)
{
	
}


