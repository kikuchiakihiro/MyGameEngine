#pragma once

#include <list>
#include <string>
#include "Transform.h"
#include "SphereCollider.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject
{
protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;
	SphereCollider*		pCollider_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
			void UpdateSub();
	virtual void Draw() = 0;
			void DrawSub();
	virtual void Release() = 0;
			void ReleaseSub();

			void SetScale(XMFLOAT3 scl_);
			void SetPosition(XMFLOAT3 pos_);
			//bool IsDead();
			bool IsDead;
			void KillMe();

			GameObject* FindChildObject(string _objName);
			GameObject* GetRootJob();
			GameObject* FindObject(string _objName);

			void AddCollider(SphereCollider* pCollider);
			void Collision(GameObject* pTarget);
			virtual void OnCollision(GameObject* pTarget) ;
			void RoundRobin(GameObject* pTarget);

			template <class T>
			GameObject* Instantiate(GameObject* parent)
			{
				T* pObject;
				pObject = new T(parent);
				pObject->Initialize();
				parent->childList_.push_back(pObject);
				return pObject;
			}



private:
	//�t���O
	//struct OBJECT_STATE
	//{
	//	unsigned initialized : 1;	//�������ς݂�
	//	//unsigned entered : 1;		//�X�V���邩
	//	//unsigned visible : 1;		//�`�悷�邩
	//	unsigned dead : 1;			//�폜���邩
	//};
	//OBJECT_STATE state_;


	

};