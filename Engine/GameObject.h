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
	//フラグ
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//初期化済みか
		unsigned entered : 1;		//更新するか
		unsigned visible : 1;		//描画するか
		unsigned dead : 1;			//削除するか
	};
	OBJECT_STATE state_;

	


};