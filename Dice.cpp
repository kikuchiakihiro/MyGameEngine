//
//#include "Dice.h"
//#include "Camera.h"
//
//Dice::Dice() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
//{
//}
//
//Dice::~Dice()
//{
//	Release();
//}
//
//HRESULT Dice::Initialize()
//{
//	HRESULT hr;
//	// ���_���
//	VERTEX vertices[] =
//	{
//
//		//��1
//		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) },	// �l�p�`�̒��_�i����j,�e�N�X�`���̍��W(��e���C���[�W����΂��������A�����ɏt��[�݂����Ȋ���)0
//		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j,�e�N�X�`���̍��W 1
//		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) },	// �l�p�`�̒��_�i�E���j,�e�N�X�`���̍��W 2
//		{XMVectorSet(-1.0f,-1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) },	// �l�p�`�̒��_�i�����j,�e�N�X�`���̍��W 3
//
//		//��2
//		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j,�e�N�X�`���̍��W 4
//		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E���j,�e�N�X�`���̍��W 5
//		{XMVectorSet(1.0f ,1.0f ,2.0f ,0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i�E����j,�e�N�X�`���̍��W 6 z��+�ŉ�
//		{XMVectorSet(1.0f ,-1.0f ,2.0f ,0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i�E�����j,�e�N�X�`���̍��W 7 z��+�ŉ�
//
//		//��3
//		{XMVectorSet(1.0f ,1.0f ,2.0f ,0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},//�l�p�`�̒��_�i�E����j,�e�N�X�`���̍��W 8 z��+�ŉ�
//		{XMVectorSet(1.0f ,-1.0f ,2.0f ,0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},//�l�p�`�̒��_�i�E�����j,�e�N�X�`���̍��W 9 z��+�ŉ�
//		{XMVectorSet(-1.0f ,1.0f ,2.0f ,0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},//�l�p�`�̒��_�i������j,�e�N�X�`���̍��W 10 z��+�ŉ�
//		{XMVectorSet(-1.0f ,-1.0f ,2.0f ,0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)},//�l�p�`�̒��_�i�������j,�e�N�X�`���̍��W 11 z��+�ŉ�
//
//		//��4
//		{XMVectorSet(-1.0f ,1.0f ,2.0f ,0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i������)12
//		{XMVectorSet(-1.0f ,-1.0f ,2.0f ,0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i������)13
//		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f) },// �l�p�`�̒��_�i����)14
//		{XMVectorSet(-1.0f,-1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f) },// �l�p�`�̒��_�i����)15
//
//		//��5
//		{XMVectorSet(-1.0f ,1.0f ,2.0f ,0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i������)16
//		{XMVectorSet(1.0f ,1.0f ,2.0f ,0.0f),XMVectorSet(0.25f, 0.5f, 0.5f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i�E����j17
//		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j18
//		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i����)19
//
//		//��6
//		{XMVectorSet(-1.0f ,-1.0f ,2.0f ,0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i�������j20
//		{XMVectorSet(1.0f ,-1.0f ,2.0f ,0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)},//�l�p�`�̒��_�i�E�����j21
//		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E���j22
//		{XMVectorSet(-1.0f,-1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i����)23
//	};
//
//	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
//	D3D11_BUFFER_DESC bd_vertex;
//	bd_vertex.ByteWidth = sizeof(vertices);  //ByteWidth���o�b�t�@�[�̃T�C�Y
//	bd_vertex.Usage = D3D11_USAGE_DEFAULT;	 //�o�b�t�@�[�̓ǂݎ��Ə������ݕ��@�����
//	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//�o�b�t�@�[���p�C�v���C���Ɍ��т���
//	bd_vertex.CPUAccessFlags = 0;	//CPU�A�N�Z�X���K�v�Ȃ��ꍇ��0
//	bd_vertex.MiscFlags = 0;
//	bd_vertex.StructureByteStride = 0;
//	D3D11_SUBRESOURCE_DATA data_vertex;
//	data_vertex.pSysMem = vertices;
//
//	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
//	if (FAILED(hr))
//	{
//		//�G���[����
//		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
//		return hr;
//		//return E_FAIL;
//	}
//
//
//	//�C���f�b�N�X���
//
//	int index[] = {
//					0,2,3, 0,1,2,//�O��
//					4,7,5, 4,6,7,//�E��
//					8,11,9, 8,10,11,//���
//					12,15,13, 12,14,15,//����
//					16,18,19, 16,17,18,//���
//					20,23,22, 20,22,21,//����
//	};
//
//
//
//	// �C���f�b�N�X�o�b�t�@�𐶐�����
//	D3D11_BUFFER_DESC   bd;
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(index);
//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	bd.MiscFlags = 0;
//	D3D11_SUBRESOURCE_DATA InitData;
//	InitData.pSysMem = index;
//	InitData.SysMemPitch = 0;
//	InitData.SysMemSlicePitch = 0;
//
//	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
//
//	if (FAILED(hr))
//	{
//		//�G���[����
//		MessageBox(nullptr, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
//		return hr;
//
//	}
//
//	//�R���X�^���g�o�b�t�@�쐬
//	D3D11_BUFFER_DESC cb;
//	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
//	cb.Usage = D3D11_USAGE_DYNAMIC;
//	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cb.MiscFlags = 0;
//	cb.StructureByteStride = 0;
//
//	// �R���X�^���g�o�b�t�@�̍쐬
//	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
//	if (FAILED(hr))
//	{
//		//�G���[����
//		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
//		return hr;
//	}
//
//	pTexture_ = new Texture;
//	pTexture_->Load("Assets\\dice.png");
//
//	return S_OK;
//}
//
//void Dice::Draw(XMMATRIX& worldMatrix)
//{
//	//�R���X�^���g�o�b�t�@�ɓn�����
//	//XMVECTOR position = { 0, 3, -10, 0 };	//�J�����̈ʒu
//	//XMVECTOR target = { 0, 0, 0, 0 };	//�J�����̏œ_
//	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//�r���[�s�� //�J�������猩�Ă̊g�����邽�߂̂���  //XMVectorSet�̓J�����̏����
//	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//�ˉe�s�� //���ߊ������� //�������@��p�A����p�����W�A���ŕ\�����Ă���
//	//������ �A�X�y�N�g�� ��O�����@�j�A�N���b�v�ʁ@��l���� �t�@�[�N���b�v��
//	//�J�������Ɏ��߂�Ȃ�x���� -1����1 y����-1����1 z����-1����1
//	//����p����������ƃY�[�����邱�ƂɂȂ�@�����̂��̂Ƌ߂��̂��̂̍����ς��Ȃ��Ȃ�@���ߊ����Ȃ��Ȃ�
//	/*�J�����̕\�������͋߂����������������߂Ȃ��Ƃ����Ȃ�
//	�������ɐݒ肵�Ȃ��Ƃǂ��܂ł������Ă��܂�����
//	�߂����͂�����x�J�����Ƃ̋������Ȃ��Ƌ��������k���ĕ\���ł��Ȃ��Ȃ邩��*/
//	//�j�A�N���b�v�ʂƃt�@�[�N���b�v�ʂ̋����͂Ȃ�ׂ��Z������@�Ȃ��������̂��ꂪ������@���̂����܂����ᑫ�肵�Ă�����悤�ɂȂ�@<- z�t�@�C�e�B���O
//
//	CONSTANT_BUFFER cb;
//	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
//	//cb.matWVP = XMMatrixTranspose(view * proj);
//	cb.matW = XMMatrixTranspose(worldMatrix);
//
//	D3D11_MAPPED_SUBRESOURCE pdata;
//	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
//	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
//
//	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
//	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
//
//	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
//	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
//
//
//	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ
//
//	//���_�o�b�t�@
//	//UINT stride = sizeof(XMVECTOR); //�O�g���Ă����
//	UINT stride = sizeof(VERTEX);
//	UINT offset = 0;
//	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
//
//	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
//	stride = sizeof(int);
//	offset = 0;
//	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
//
//	//�R���X�^���g�o�b�t�@
//	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
//	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
//
//	//Direct3D::pContext_->DrawIndexed(9, 0, 0);
//	Direct3D::pContext_->DrawIndexed(36, 0, 0);
//}
//
//void Dice::Release()
//{
//	pTexture_->Release();
//	SAFE_DELETE(pTexture_);
//
//	SAFE_RELEASE(pConstantBuffer_);
//	SAFE_RELEASE(pIndexBuffer_);
//	SAFE_RELEASE(pVertexBuffer_);
//}