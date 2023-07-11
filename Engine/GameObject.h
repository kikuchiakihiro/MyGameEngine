#pragma once

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;
class GameObject
{
protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;

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

			bool IsDisappear();
	template <class T>
	void Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
	}
private:
	//�t���O
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//�������ς݂�
		unsigned entered : 1;		//�X�V���邩
		unsigned visible : 1;		//�`�悷�邩
		unsigned dead : 1;			//�폜���邩
	};
	OBJECT_STATE state_;

	


};