#include "Model.h"

int Model::Load(std::string fileName) 
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	for (auto& e : modelList) {
		if (e->filename_ == fileName) {
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}

	if (pData->pfbx_ == nullptr) {
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}
	
	modelList.push_back(pData);
	return (modelList.size() - 1);

}

void SetTransform(int hModel, Transform transform)
{
	Model::modelList[hModel]->transform_ = transform;
}

void Draw(int hModel) 
{
	Model::modelList[hModel]->pfbx_->Draw(Model::modelList[hModel]->transform_);
}