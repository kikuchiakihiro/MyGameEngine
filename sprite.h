#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include <vector>
#include"Texture.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;} //�J������


using namespace DirectX;
using std::vector;
class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

	HRESULT hr;

protected:
	UINT64  vertexNum_; //���_��
	vector<VERTEX> vertices_; //���_���
	ID3D11Buffer* pVertexBuffer_; //���_�o�b�t�@

	UINT64 indexNum_; //�C���f�b�N�X��
	vector<int> index_; //�C���f�b�N�X���

	Texture* pTexture_; //�e�N�X�`��

	//���Ƃ͂Ȃ����
	ID3D11Buffer* pIndexBuffer_; //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

public:
	Sprite();
	~Sprite();

	//������(�|���S����\�����邽�ߊe���������)
	//�߂�l ����/���s
	HRESULT Initialize();

	//�`��
	//����:worldMatrix ���[���h�s��
	void Draw(XMMATRIX& worldMatrix);

	//�J��
	void Release();

private:

	//Initialize����Ă΂��֐�
	virtual void InitVertexData(); //���_��������
	HRESULT  CreateVertexBuffer(); //���_�o�b�t�@���쐬

	virtual void InitIndexData(); //�C���f�b�N�X��������
	HRESULT CreateIndexBuffer(); //�C���f�b�N�X�o�b�t�@���쐬

	HRESULT CreateConstantBuffer(); //�R���X�^���g�o�b�t�@���쐬

	HRESULT LoadTexture(); //�e�N�X�`�������[�h

	//Draw����Ă΂��֐�
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix); //�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline(); //�e�o�b�t�@���p�C�v���C���ɃZ�b�g

};

