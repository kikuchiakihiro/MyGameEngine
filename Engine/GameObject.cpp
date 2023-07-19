#include "GameObject.h"
#include "Direct3D.h"
GameObject::GameObject():pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name): pParent_(parent),
objectName_(name),IsDead(false)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}


GameObject::~GameObject()
{
}

// 削除するかどうか
//bool GameObject::IsDead()
//{
//	return (state_.dead != 0);
//}

// 自分を削除する
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

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
	}
	Release();
}

void GameObject::SetScale(XMFLOAT3 scl_)
{
	transform_.scale_ = scl_;
}

void GameObject::SetPosition(XMFLOAT3 pos_)
{
	transform_.position_ = pos_;
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) {
		return(this);
	}
	else {
		//for (auto itr = childList_.begin(); itr != childList_.end(); itr++) 
		for(auto itr: childList_)
		{
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}
/// <summary>
///		再帰呼び出しでROOTJOB探して返すやーつ
/// </summary>
/// <returns></returns>RootJobのアドレス
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}







