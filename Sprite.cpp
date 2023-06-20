#include "Sprite.h"

Sprite::Sprite() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr), hr(0), indexNum_(0), vertexNum_(0)
{
}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize()
{
	InitVertexData();

	hr = CreateVertexBuffer();
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
		//return E_FAIL;
	}

	InitIndexData();

	hr = CreateIndexBuffer();
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;

	}

	hr = CreateConstantBuffer();
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}


	LoadTexture();

}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	PassDataToCB(worldMatrix);

	SetBufferToPipeline();

	Direct3D::pContext_->DrawIndexed(6, 0, 0);
}

void Sprite::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}


void Sprite::InitVertexData()
{
	// ���_���
	vertices_ =
	{
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i����j,�e�N�X�`���̍��W(��e���C���[�W����΂��������A�����ɏt��[�݂����Ȋ���)
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E��j,�e�N�X�`���̍��W
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�E���j,�e�N�X�`���̍��W
		{XMVectorSet(-1.0f,-1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},	// �l�p�`�̒��_�i�����j,�e�N�X�`���̍��W

	};

	vertexNum_ = vertices_.size();
}

HRESULT Sprite::CreateVertexBuffer()
{
	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex{};
	bd_vertex.ByteWidth = vertexNum_ * sizeof(VERTEX);  //ByteWidth���o�b�t�@�[�̃T�C�Y
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;	 //�o�b�t�@�[�̓ǂݎ��Ə������ݕ��@�����
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//�o�b�t�@�[���p�C�v���C���Ɍ��т���
	bd_vertex.CPUAccessFlags = 0;	//CPU�A�N�Z�X���K�v�Ȃ��ꍇ��0
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = &vertices_.front();

	return Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

void Sprite::InitIndexData()
{
	indexNum_ = 6;
	//�C���f�b�N�X���
	index_ = { 0,2,3, 0,1,2 };
}

HRESULT Sprite::CreateIndexBuffer()
{
	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = indexNum_ * sizeof(index_);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData{};
	InitData.pSysMem = &index_.front();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	return Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
}

HRESULT Sprite::CreateConstantBuffer()
{
	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb{};
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	return Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

HRESULT Sprite::LoadTexture()
{
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\d.png");
	return S_OK;
}

void Sprite::PassDataToCB(DirectX::XMMATRIX& worldMatrix)
{

	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
}

void Sprite::SetBufferToPipeline()
{
	//���_�o�b�t�@
	//UINT stride = sizeof(XMVECTOR); //�O�g���Ă����
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

}