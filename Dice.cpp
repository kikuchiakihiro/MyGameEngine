
#include "Dice.h"
#include "Camera.h"
#include "Texture.h"

Dice::Dice() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr)
{
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	VERTEX vertices[] =
	{
		//面１
	   {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 前面（左上）0
	   {XMVectorSet( 1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 前面（右上）1
	   {XMVectorSet( 1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 前面（右下）2
	   {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 前面（左下）3

	   //面２
	   {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) }, // 上面（左上）4
	   {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) , XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 上面（右上）5
	   {XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },    // 上面（右下）6
	   {XMVectorSet(-1.0f, -1.0f,  1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 上面（左下）7
	  
	   //面３
	   {XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f, 0.0f)},    // 測面右（左上）8
	   {XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 測面右（右上）9
	   {XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 測面右（右下）10
	   {XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 測面右（左下）11

	   //面４
	  {XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 測面左（左上）12
	  {XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 測面左（右上）13
	  {XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f, 0.0f)},  // 測面左（右下）14
	  {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },  // 測面左（左下）15

	  //面５
	   {XMVectorSet(-1.0f, 1.0f,  1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },    // 上面（左上）16
	   {XMVectorSet(1.0f,  1.0f,  1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 上面（右上）17
	   {XMVectorSet(1.0f, 1.0f,  -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 上面（右下）18
	   {XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f, 0.0f)},   // 上面（左下）19

	   //面６
	   {XMVectorSet(1.0f, 1.0f,   1.0f, 0.0f),XMVectorSet( 0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },    // 背面（左上）20
	   {XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f)  ,XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 背面（右上）21
	   {XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f)  ,XMVectorSet(0.0f,0.0f,-1.0f, 0.0f) },   // 背面（右下）22
	   {XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f),XMVectorSet( 0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f, 0.0f)},   // 背面（左下）23

	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	if (FAILED(Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_)))
	{
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}
	//インデックス情報
	int index[] = { 0, 2, 3,  0, 1, 2,     
					4, 6, 7,  4, 5, 6,     
					8,10,11,  8, 9,10,     
					12,14,15, 12,13,14,    
					16,18,19, 16,17,18,    
					20,22,23, 20,21,22,        
	};

	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	if (FAILED(Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_)))
	{
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	if (FAILED(Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_)))
	{
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\MicrosoftTeams-image.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列 画角　XM_PIDIV4は45度, アスペクト比,　ニアクリッピング面,　ファークリッピング面

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matW = XMMatrixTranspose(worldMatrix);
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);



	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();

	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);


	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext_->DrawIndexed(36, 0, 0);
}

void Dice::Release()
{
	/*pConstantBuffer_->Release();
	pIndexBuffer_->Release();
	pVertexBuffer_->Release();*/

	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}