#include<iostream>
#include<string>
#include<Windows.h>
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"
#include "Engine/Direct3D.h"

HANDLE hFile;

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z < ZSIZE; z++) {
           /* table_[i][f];
            table_[i][f].height = 1;*/
            SetBlockHeight(x, z, 0);
        }
    }
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string  fname_base = "Assets/";
    //���f���f�[�^�̃��[�h
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = Model::Load(fname_base + modelname[i]);
    assert(hModel_[i] >= 0);
    }
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlock(x, z, DEFAULT);
        }
    }
}

//�X�V
void Stage::Update()
{
    
    if (!Input::IsMouseButtonDown(0)) {
        return;
   }
    float w = (float)(Direct3D::scrWidth / 2.0f);
    float h = (float)(Direct3D::scrHeight / 2.0f);

    XMMATRIX vp =
    {
        w, 0, 0, 0,
        0,-h, 0, 0,
        0, 0, 1, 0,
        w, h, 0, 1
    };
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
        XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
        XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
        XMFLOAT3 mousePosFront = Input::GetMousePosition();
        mousePosFront.z = 0.0f;
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);

    vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);

    XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);

    vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);


        for (int x = 0; x < XSIZE; x++) {
            for (int z = 0; z < ZSIZE; z++) {
                for (int y = 0; y < table_[x][z].height + 1; y++) {
                    RayCastData data{};
                    XMStoreFloat4(&data.start, vMouseFront);
                    XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
                    Transform trans;
                   trans.position_.x = x;
                   trans.position_.y = y;
                   trans.position_.z = z;
                    Model::SetTransform(hModel_[0], trans);

                    Model::RayCast(hModel_[0], data);

                    if (data.hit) {

                        switch (mode_)
                        {
                        case 0:
                            table_[x][z].height++;
                            break;
                        case 1:
                            if (table_[x][z].height > 0)
                                table_[x][z].height--;
                            break;
                        case 2:  
                                table_[x][z].blocks = (BLOCKTYPE)hModel_[select_];
                 
                            break;
                        case 3:
                            for (int x = 0; x < XSIZE; x++) {
                                for (int z = 0; z < ZSIZE; z++) {
                                    table_[x][z].blocks = (BLOCKTYPE)hModel_[select_];
                                }
                             }
                        }
                        return;
                        }

                        
                    }
                    
                }
            }
        }
  


//�`��
void Stage::Draw()
{
    Transform BlockTrans;//Transform�^�̕ϐ�
    //Transform�^ -> �ʒu,����,�傫���������^



    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            

            for (int y = 0; y < table_[x][z].height+1; y++) {

                BlockTrans.position_.x = x;
                BlockTrans.position_.z = z;
                BlockTrans.position_ = { (float)x,(float)y,(float)z };
                Model::SetTransform(table_[x][z].blocks, BlockTrans);
                Model::Draw(table_[x][z].blocks);

            }
        }
    }
}
   

//�J��
void Stage::Release()
{
   
}

void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].blocks = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}




void Stage::SaveBlockData()
{
    char fileName[MAX_PATH] = "SaveData.map";  //�t�@�C����������ϐ�

    //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
    ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
    ofn.lpstrFile = fileName;               	//�t�@�C����
    ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
    ofn.lpstrDefExt = "map";                  	//�f�t�H���g�g���q

    //�u�t�@�C����ۑ��v�_�C�A���O
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    if (selFile == FALSE) return;


            //�t�@�C���̃n���h��
    hFile = CreateFile(
        "SaveData.txt",//�t�@�C����
        GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
        0,                      //���L�i�Ȃ��j
        NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
        CREATE_ALWAYS,           //�쐬���@
        FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
        NULL);                  //�g�������i�Ȃ��j
   
    std::string heightdata;
    std::string typedata;
    std::string stagedata;

    for (int x = 0; x < XSIZE; x++)
    {
        for (int z = 0; z < ZSIZE; z++)
        {
            
            stagedata += std::to_string(table_[x][z].height) + "," + std::to_string(table_[x][z].blocks)+"\n";
            
        }
    }
   

    //stagedata = heightdata + "\n" + typedata;

    DWORD dwBytes = 0;  //�������݈ʒu
    BOOL res = WriteFile(
        hFile,                   //�t�@�C���n���h��
        stagedata.c_str(),                  //�ۑ�����f�[�^�i������j
        (DWORD)strlen(stagedata.c_str()),   //�������ޕ�����
        &dwBytes,                //�������񂾃T�C�Y������ϐ�
        NULL);
   
    CloseHandle(hFile);

}

void Stage::LoadBlockData()
{
    char fileName[MAX_PATH] = "SaveData.map";  //�t�@�C����������ϐ�

    //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
    ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
    ofn.lpstrFile = fileName;               	//�t�@�C����
    ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
    ofn.Flags = OFN_FILEMUSTEXIST;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
    ofn.lpstrDefExt = "map";                  	//�f�t�H���g�g���q
     
    //�u�t�@�C����ۑ��v�_�C�A���O
    BOOL selFile;
    selFile = GetOpenFileName(&ofn);

    if (selFile == FALSE) return;

         //�t�@�C���̃n���h��
    hFile = CreateFile(
        "SaveData.txt",                 //�t�@�C����
        GENERIC_READ,           //�A�N�Z�X���[�h�i�������ݗp�j
        0,                      //���L�i�Ȃ��j
        NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
        OPEN_EXISTING,          //�쐬���@
        FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
        NULL);                  //�g�������i�Ȃ��j
    //�t�@�C���̃T�C�Y���擾
    DWORD fileSize = GetFileSize(hFile, NULL);

    //�t�@�C���̃T�C�Y�����������m��
    char* data;
    data = new char[fileSize];

    DWORD dwBytes = 0; //�ǂݍ��݈ʒu

    ReadFile(
        hFile,     //�t�@�C���n���h��
        data,      //�f�[�^������ϐ�
        fileSize,  //�ǂݍ��ރT�C�Y
        &dwBytes,  //�ǂݍ��񂾃T�C�Y
        NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

    CloseHandle(hFile);
}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_INITDIALOG:
            //radio
        SendMessage(GetDlgItem(hDlg, IDC_RADIOUP), BM_SETCHECK, BST_CHECKED,0);
        
        for (int i = 0; i < MODEL_NUM; i++) {
            SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)blockName[i]);

        }
        
      
        
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
        return TRUE;

    case WM_COMMAND:

        
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);
        select_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0);
       

        if (IsDlgButtonChecked(hDlg, IDC_RADIOUP)) {
            mode_ = 0;
        }
        if (IsDlgButtonChecked(hDlg, IDC_RADIODOWN)) {
            mode_ = 1;
        }
        if (IsDlgButtonChecked(hDlg, IDC_RADIOCange)) {
            mode_ = 2;
        }
        if (IsDlgButtonChecked(hDlg, IDC_RADIOALLchange)) {
            mode_ = 3;
        }
        return TRUE;
        
    }
    return FALSE;

   
}

