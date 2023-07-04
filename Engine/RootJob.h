#pragma once
#include "GameObject.h"
class RootJob :
	public GameObject
{
	RootJob() {};
	~RootJob() {};
		void	Initialize() override;
		void	Update()	 override;
		void	Draw()		 override;
		void	Release()	 override;
};
