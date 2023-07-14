#pragma once
#include <string>
#include <vector>
#include "Engine/Transform.h"
#include "Engine/Fbx.h"
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

	std::vector<ModelData*>modelList;

};

