#pragma once
#include <string>
#include <vector>
#include "Transform.h"
#include "Fbx.h"
namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;

	};

	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);

	void Release();
	void RayCast(int hModel, RayCastData& rayData);
};

