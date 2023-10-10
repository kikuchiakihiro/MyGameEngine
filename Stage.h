#pragma once
#include "Engine/GameObject.h"
#include "Windows.h"
namespace {
    const int MODEL_NUM{ 5 };
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };
    enum BLOCKTYPE
    {
        DEFAULT = 0,
        BRICK,
        GRASS,
        SAND,
        WATER
    };
    const char* blockName[] = { "�f�t�H���g","�����K", "��", "��", "��" };
}



//���������Ǘ�����N���X
class Stage : public GameObject
{
  
    int hModel_[MODEL_NUM];
    

    struct BLOCKHEIGHT{
        BLOCKTYPE blocks;
             int height;
             
    } table_[XSIZE][ZSIZE];
    int mode_ = 0;
    
    int select_ = 0;
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
    void SaveBlockData();
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
    //BOOL MenuProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};