#include "GameObject.h"
#include "Direct3D.h"
GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name): pParent_(nullptr)
{
}

GameObject::~GameObject()
{
}

// �폜���邩�ǂ���
//bool GameObject::IsDead()
//{
//	return (state_.dead != 0);
//}

// �������폜����
void GameObject::KillMe()
{
	IsDead = true;
}


void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end();itr++ )
	{
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead == true)
		{
			ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->ReleaseSub();
}


