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
	//pPlayer = new Player(this);//�v���C���[�̐e�́A����
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);//�q�Ƃ��āA�o�^
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