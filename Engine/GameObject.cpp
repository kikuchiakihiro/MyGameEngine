#include "GameObject.h"
#include "Direct3D.h"
GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name): pParent_(nullptr),
objectName_(name),IsDead(false)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

// íœ‚·‚é‚©‚Ç‚¤‚©
//bool GameObject::IsDead()
//{
//	return (state_.dead != 0);
//}

// Ž©•ª‚ðíœ‚·‚é
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

void GameObject::SetScale(XMFLOAT3 scl_)
{
	transform_.scale_ = scl_;
}

void GameObject::SetPosition(XMFLOAT3 pos_)
{
	transform_.position_ = pos_;
}







