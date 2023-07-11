#include "PlayScene.h"
#include "Player.h"
#include "Player2.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	
	//Player* pPlayer;
	//pPlayer = new Player(this);//プレイヤーの親は、自分
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);//子として、登録
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}