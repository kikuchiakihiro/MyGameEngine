//#include "Fbx.h"
//
//Fbx::Fbx():
//	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr),pConstantBuffer_(nullptr)
//	, vertexCount_(0), polygonCount_(0)
//{
//}
//
//Fbx::~Fbx()
//{
//	Release();
//}
//
//HRESULT Fbx::Load(std::string fileName)
//{
//	//�}�l�[�W���𐶐�
//	FbxManager* pFbxManager = FbxManager::Create();
//
//	//�C���|�[�^�[�𐶐�
//	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
//	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());
//
//	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
//	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
//	fbxImporter->Import(pFbxScene);
//	fbxImporter->Destroy();
//
//	//���b�V�������擾
//	FbxNode* rootNode = pFbxScene->GetRootNode();
//	FbxNode* pNode = rootNode->GetChild(0);
//	FbxMesh* mesh = pNode->GetMesh();
//
//	//�e���̌����擾
//
//	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
//
//	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
//
//	InitVertex(mesh);		//���_�o�b�t�@����
//
//	//�}�l�[�W�����
//	pFbxManager->Destroy();
//	return S_OK;
//}
//
//void Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
//{
//	
//}
//
//void Fbx::Draw(Transform& transform)
//{
//}
//
//void Fbx::Release()
//{
//	SAFE_RELEASE(pConstantBuffer_);
//	SAFE_RELEASE(pIndexBuffer_);
//	SAFE_RELEASE(pVertexBuffer_);
//}
