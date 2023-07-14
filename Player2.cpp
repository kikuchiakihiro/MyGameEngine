#include "Player2.h"
#include "Engine/Model.h"


Player2::Player2(GameObject* parent) :GameObject(parent, "Player2"), pFbx(nullptr),hModel_(-1)
{
}

void Player2::Initialize()
{

	//pFbx = new Fbx;
	hModel_ = Model::Load("Assets\\odden.fbx");
	this->transform_.position_.x = -5.0f;
	this->transform_.scale_.x = 0.2f;
	this->transform_.scale_.y = 0.2f;
	this->transform_.scale_.z = 0.2f;
}

void Player2::Update()
{
	transform_.rotate_.x = 90.0f;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 20) {
		KillMe();
	}
	//transform_.rotate_.x++;
	/*if (transform_.rotate_.y > 300) {
		KillMe();
	}*/
}

void Player2::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player2::Release()
{
	/*pFbx->Release();
	delete pFbx;*/
}