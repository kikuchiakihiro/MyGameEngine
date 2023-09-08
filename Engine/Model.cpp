#include "Model.h"
#include "Direct3D.h"



namespace Model {
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;

	};
	std::vector<ModelData*>modelList;

}

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

void Model::SetTransform(int hModel, Transform transform)
{
	Model::modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel)
{
	Model::modelList[hModel]->pfbx_->Draw(Model::modelList[hModel]->transform_);
}

void Model::Release()
{
	bool IsReferred = false;
	for (int i = 0; i < modelList.size();i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_) {
				IsReferred = true;
				break;
			}
		}
		if (IsReferred == false) {
			SAFE_DELETE(modelList[i]->pfbx_)
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}

void Model::RayCast(int hModel, RayCastData& rayData)
{
	//モデルのトランスフォームをカリキュレーション
	modelList[hModel]->transform_.Calculation();
	//逆行列
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[hModel]->transform_.GetWorldMatrix());
	//通過点
	XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
					rayData.start.y + rayData.dir.y,
					rayData.start.z + rayData.dir.z,
					rayData.start.w + rayData.dir.w };
	//モデル空間に変換
	XMVECTOR vstart = XMLoadFloat4(&rayData.start);
	vstart = XMVector3TransformCoord(vstart, wInv);
	//通過点に1をかける
	vpass = XMVector3TransformCoord(vpass, wInv);
	//３，４に向かうベクトルにする
	vpass = vpass-vstart;
	XMStoreFloat4(&rayData.dir, vpass);



	modelList[hModel]->pfbx_->RayCast(rayData);
}


