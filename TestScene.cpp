#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Stage.h"
#include "controller.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<controller>(this);

}

void TestScene::Update()
{

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}