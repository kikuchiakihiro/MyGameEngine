#include "PlayScene.h"
#include "Player.h"
#include "Player2.h"
#include "Enemy.h"
PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	GameObject * pPlayer = Instantiate<Player>(this);
	GameObject* pEnemy = Instantiate<Enemy>(this);
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