//=============================================================================
//
// read.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "read.h"
#include <stdio.h>
#include "game.h"
#include "result.h"
#include "manager.h"
#include <assert.h>
#include "motion_parts.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CRead::CRead()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CRead::~CRead()
{
}

//*****************************************************************************
// ���f���̓ǂݍ���
//*****************************************************************************
void CRead::ReadModel(ModelTxt ModelTxt)
{
	//FILE *pFile = nullptr;			//�t�@�C���|�C���^�[�錾
	//char cBff[LINE_MAX_READING_LENGTH];		//��s���ǂݎ�邽�߂̕ϐ�
	//char cBffHead[LINE_MAX_READING_LENGTH];	//���̕�����ǂݎ�邽�߂̕ϐ�

	////�t�@�C�����J��
	//switch (ModelTxt)
	//{
	//case TitleModel:
	//	pFile = fopen("data/TXT/SetModelDataTitle.txt", "r");
	//	break;
	//case StageSelectModel:
	//	pFile = fopen("data/TXT/SetModelDataStageSelect.txt", "r");
	//	break;
	//case GameStage01:
	//	pFile = fopen("data/TXT/SetModelDataGameStage01.txt", "r");
	//	break;
	//case GameStage02:
	//	pFile = fopen("data/TXT/SetModelDataGameStage02.txt", "r");
	//	break;
	//case GameStage03:
	//	pFile = fopen("data/TXT/SetModelDataGameStage03.txt", "r");
	//	break;
	//case GameStage04:
	//	pFile = fopen("data/TXT/SetModelDataGameStage04.txt", "r");
	//	break;
	//case GameStage05:
	//	pFile = fopen("data/TXT/SetModelDataGameStage05.txt", "r");
	//	break;
	//case GameStage06:
	//	pFile = fopen("data/TXT/SetModelDataGameStage06.txt", "r");
	//	break;
	//case ResultModel:
	//case ModelTxtMax:
	//default:
	//	assert(false);
	//	break;
	//}

	//if (pFile == nullptr)
	//{//�J���Ȃ��������p
	//	assert(false);
	//}

	////������̓ǂݎ�胋�[�v����
	//while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
	//{
	//	//������̕���
	//	sscanf(cBff, "%s", &cBffHead);

	//	if (strcmp(&cBffHead[0], "MODEL") == 0)
	//	{//x�t�@�C���̃p�X
	//		char XFilePath[LINE_MAX_READING_LENGTH];

	//		//������̕���
	//		sscanf(cBff, "%s = %s", &cBffHead, &XFilePath);

	//		ReadXFile(XFilePath);
	//	}
	//	else if (strcmp(&cBffHead[0], "END") == 0)
	//	{//�ǂݐ؂�����
	//		break;
	//	}

	//	//�ۑ����̕�����̏�����
	//	ZeroMemory(&cBff, sizeof(cBff));
	//	ZeroMemory(&cBffHead, sizeof(cBffHead));
	//}

	////�t�@�C�������
	//fclose(pFile);
}

//*****************************************************************************
// ���[�V�����t�@�C���̓ǂݍ���
//*****************************************************************************
int CRead::ReadMotion(char * sXFilePath)
{
	FILE *pFile = NULL;			//�t�@�C���|�C���^�[�錾

	char cBff[LINE_MAX_READING_LENGTH];		//��s���ǂݎ�邽�߂̕ϐ�
	char cBffHead[LINE_MAX_READING_LENGTH];	//���̕�����ǂݎ�邽�߂̕ϐ�
	//���f���\���̂̕ۑ��p�ϐ��錾
	MotionData* pMotiondata = nullptr;
	//�e���f���̃C���f�b�N�X
	int* pMotionIndex = nullptr;

	int nMotionMax = 0;//���f���̐�

	int nSettingCompletionParts = 0;//�ݒ�̊��������p�[�c��

	int nSettingCompletionModel = 0;//�ݒ�̊����������f����

	//�Z�b�g���[�V�����I�u�W�F�N�g
	int nMotionNum = 0;

	//�t�@�C�����J��
	pFile = fopen(sXFilePath, "r");

	if (pFile == nullptr)
	{//�J���Ȃ��������p
		assert(false);
	}

	//������̓ǂݎ�胋�[�v����
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
	{
		//������̕���
		sscanf(cBff, "%s", &cBffHead);

		if (strcmp(&cBffHead[0], "NUM_MODEL") == 0)
		{//���f����
			if (pMotionIndex != nullptr)
			{
				assert(false);
			}
			sscanf(cBff, "%s = %d", &cBffHead, &nMotionMax);
			pMotionIndex = new int[nMotionMax];
		}
		else if (strcmp(&cBffHead[0], "MODEL_FILENAME") == 0)
		{//X�t�@�C���̑��΃p�X�p

			char sPath[LINE_MAX_READING_LENGTH];		//���΃p�X�ۑ��p

			//��s�̕����񂩂瑊�΃p�X�̓ǂݎ��
			sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);

			//X�t�@�C���̓ǂݍ���
			pMotionIndex[nSettingCompletionModel] = ReadXFile(sPath);
			nSettingCompletionModel++;
		}
		else if (strcmp(&cBffHead[0], "CHARACTERSET") == 0)
		{//�������̔z�u�p

		 //���f���Z�b�g�ɕK�v�ȏ��ǂݎ�胋�[�v����
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//������̕���
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "NUM_PARTS") == 0)
				{//�p�[�c��
				 //������̕���
					if (pMotiondata != nullptr)
					{
						assert(false);
					}
					int nPartsMax = 0;//�p�[�c�̐�
					sscanf(cBff, "%s = %d", &cBffHead, &nPartsMax);

					pMotiondata = new MotionData[nPartsMax];
				}
				else if (strcmp(&cBffHead[0], "MOVE") == 0)
				{//�ړ���
				 //������̕���
					//sscanf(cBff, "%s = %f", &cBffHead, &);
				}
				else if (strcmp(&cBffHead[0], "JUMP") == 0)
				{//�W�����v��
				 //������̕���
					//sscanf(cBff, "%s = %f", &cBffHead, &);
				}
				else if (strcmp(&cBffHead[0], "PARTSSET") == 0)
				{//���f���ЂƂ̃Z�b�g�p�̃f�[�^�ǂݎ��
				 //�C���f�b�N�X�ۑ��p
				
					//���f���Z�b�g�ɕK�v�ȏ��ǂݎ�胋�[�v����
					while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
					{
						//������̕���
						sscanf(cBff, "%s", &cBffHead);

						if (strcmp(&cBffHead[0], "INDEX") == 0)
						{//�g�p���郂�f���̔ԍ�
						 //������̕���
							int nNum = 0;
							sscanf(cBff, "%s = %d", &cBffHead, &nNum);
							pMotiondata[nSettingCompletionParts].nModelPattern = pMotionIndex[nNum];
						}
						else if (strcmp(&cBffHead[0], "PARENT") == 0)
						{//�e�̔ԍ�
						 //������̕���
							sscanf(cBff, "%s = %d", &cBffHead, &pMotiondata[nSettingCompletionParts].nParentNum);
						}
						else if (strcmp(&cBffHead[0], "POS") == 0)
						{//���f���̈ʒu
						 //������̕���
							D3DXVECTOR3 pos;
							sscanf(cBff, "%s = %f%f%f", &cBffHead, &pos.x, &pos.y, &pos.z);
							pMotiondata[nSettingCompletionParts].pos = pos;
						}
						else if (strcmp(&cBffHead[0], "ROT") == 0)
						{//���f���̌���
						 //������̕���
							D3DXVECTOR3 rot;
							sscanf(cBff, "%s = %f%f%f", &cBffHead, &rot.x, &rot.y, &rot.z);
							pMotiondata[nSettingCompletionParts].rot = rot;
						}
						else if (strcmp(&cBffHead[0], "END_PARTSSET") == 0)
						{//���f���P�p�[�c�̃Z�b�g�I��
							nSettingCompletionParts++;
							break;
						}

						//�ۑ����̕�����̏�����
						ZeroMemory(&cBff, sizeof(cBff));
						ZeroMemory(&cBffHead, sizeof(cBffHead));

					}
				}
				else if (strcmp(&cBffHead[0], "END_CHARACTERSET") == 0)
				{//���f���̃f�[�^�ǂݎ��I��
					//�Z�b�g���[�V�����I�u�W�F�N�g
					nMotionNum = CMotionParts::CreateMotionObj(pMotiondata, nSettingCompletionParts);

					if (pMotiondata != nullptr)
					{
						delete[] pMotiondata;
						pMotiondata = nullptr;
					}

					break;
				}

				//�ۑ����̕�����̏�����
				ZeroMemory(&cBff, sizeof(cBff));
				ZeroMemory(&cBffHead, sizeof(cBffHead));

			}
		}
		else if (strcmp(&cBffHead[0], "MOTIONSET") == 0)
		{//���[�V�����p�̃f�[�^�ǂݎ��
			MotionMoveData MotionMoveData;
			MotionMoveData.pMotionKeyData = nullptr;
			MotionMoveData.bLoop = false;
			MotionMoveData.nKeyMax = 0;
			MotionMoveData.nNextMotionNum = 0;

			int nMotionKeyMax = 0;
			int nMotionKey = 0;//�g�����L�[�̐��̃J�E���g
			//���f���Z�b�g�ɕK�v�ȏ��ǂݎ�胋�[�v����
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
			{
				//������̕���
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "LOOP") == 0)
				{//���̃��[�V�����̓��[�v�Đ����邩�ǂ���
				 //������̕���
					int nLoop;
					sscanf(cBff, "%s = %d", &cBffHead, &nLoop);
					MotionMoveData.bLoop = false;
					if (nLoop != 0)
					{
						MotionMoveData.bLoop = true;
					}
				}
				else if (strcmp(&cBffHead[0], "NUM_KEY") == 0)
				{//���[�V�����̃L�[��
				 //������̕���
					sscanf(cBff, "%s = %d", &cBffHead, &nMotionKeyMax);

					if (MotionMoveData.pMotionKeyData != nullptr)
					{
						assert(false);
					}
					MotionMoveData.nKeyMax = nMotionKeyMax;//�L�[���̕ۑ�
					MotionMoveData.pMotionKeyData = new MotionKeyData[nMotionKeyMax];//�L�[���ƂɕK�v�ȃf�[�^�̊m��

					for (int nKey = 0; nKey < nMotionKeyMax; nKey++)
					{
						//������
						MotionMoveData.pMotionKeyData[nKey].pMotionPartsData = nullptr;
					}
				}
				else if (strcmp(&cBffHead[0], "NEXT_MOTION") == 0)
				{
					int nNext = 0;
					sscanf(cBff, "%s = %d", &cBffHead, &nNext);

					MotionMoveData.nNextMotionNum = nNext;
				}
				else if (strcmp(&cBffHead[0], "KEYSET") == 0)
				{//���f���p�[�c�̃��[�V�����ݒ�


					//�p�[�c���ƂɕK�v�ȏ����m��
					if (MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData != nullptr)
					{
						assert(false);
					}
					MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData = new MotionPartsData[nSettingCompletionParts];

					

					int nModelPasCnt = 0;		//���f���p�[�c�̃Z�b�g�ԍ�

					//���f���Z�b�g�ɕK�v�ȏ��ǂݎ�胋�[�v����
					while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
					{
						//������̕���
						sscanf(cBff, "%s", &cBffHead);

						if (strcmp(&cBffHead[0], "FRAME") == 0)
						{//���̃��[�V�����͉��t���[�����ōĐ����邩�`�F�b�N
						 //������̕���
							int nFrame = 0;
							sscanf(cBff, "%s = %d", &cBffHead, &nFrame);
							if (nFrame == 0)
							{//�Đ��t���[������0�̏ꍇ1�ɂ���
								nFrame = 1;
							}
							MotionMoveData.pMotionKeyData[nMotionKey].nFrame = nFrame;
						}
						else if (strcmp(&cBffHead[0], "KEY") == 0)
						{//���[�V�����̂P�p�[�c�̃Z�b�g
						 //���f���Z�b�g�ɕK�v�ȏ��ǂݎ�胋�[�v����
							while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != NULL)
							{
								//������̕���
								sscanf(cBff, "%s", &cBffHead);

								if (strcmp(&cBffHead[0], "POS") == 0)
								{//���[�V�������̂P�p�[�c�̈ʒu
								 //������̕���
									D3DXVECTOR3 pos;
									sscanf(cBff, "%s = %f%f%f", &cBffHead,&pos.x,&pos.y,&pos.z);

									MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData[nModelPasCnt].pos = pos;
								}
								else if (strcmp(&cBffHead[0], "ROT") == 0)
								{//���[�V�������̂P�p�[�c�̌���
								 //������̕���
									D3DXVECTOR3 rot;
									sscanf(cBff, "%s = %f%f%f", &cBffHead, &rot.x, &rot.y, &rot.z);

									MotionMoveData.pMotionKeyData[nMotionKey].pMotionPartsData[nModelPasCnt].rot = rot;
								}
								else if (strcmp(&cBffHead[0], "END_KEY") == 0)
								{//���[�V�������̂P�p�[�c�̃Z�b�g�I��
									nModelPasCnt++;//�P�p�[�c�̃Z�b�g�I��
									break;
								}

								//�ۑ����̕�����̏�����
								ZeroMemory(&cBff, sizeof(cBff));
								ZeroMemory(&cBffHead, sizeof(cBffHead));

							}
						}
						else if (strcmp(&cBffHead[0], "END_KEYSET") == 0)
						{
							nMotionKey++;//�ݒ肵���L�[���̃J�E���g
							break;
						}

						//�ۑ����̕�����̏�����
						ZeroMemory(&cBff, sizeof(cBff));
						ZeroMemory(&cBffHead, sizeof(cBffHead));

					}
				}
				else if (strcmp(&cBffHead[0], "END_MOTIONSET") == 0)
				{//���f���p�[�c�̃��[�V�����ݒ�I��
					//���[�V�����̓o�^
					CMotionParts::SetMotionFileData(MotionMoveData, nMotionNum);

					for (int nCnt = 0; nCnt < nMotionKey; nCnt++)
					{
						if (MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData != nullptr)
						{
							delete[] MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData;
							MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData = nullptr;
						}
					}

					if (MotionMoveData.pMotionKeyData != nullptr)
					{
						delete[] MotionMoveData.pMotionKeyData;
						MotionMoveData.pMotionKeyData = nullptr;
					}

					break;
				}

				//�ۑ����̕�����̏�����
				ZeroMemory(&cBff, sizeof(cBff));
				ZeroMemory(&cBffHead, sizeof(cBffHead));

			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{//�e�L�X�g�t�@�C����ǂݐ؂�����
			break;
		}

		//�ۑ����̕�����̏�����
		ZeroMemory(&cBff, sizeof(cBff));
		ZeroMemory(&cBffHead, sizeof(cBffHead));

	}

	//�t�@�C�������
	fclose(pFile);

	

	if (pMotionIndex != nullptr)
	{
		delete[] pMotionIndex;
		pMotionIndex = nullptr;
	}

	return nMotionNum;
}

//*****************************************************************************
// X�t�@�C���̓ǂݍ���
//*****************************************************************************
int CRead::ReadXFile(char * sXFilePath)
{
	C3DObject::ModelPattern Model;

	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(sXFilePath,
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		nullptr,
		&Model.pBuffMatModel,
		nullptr,
		&Model.nNumMatModel,
		&Model.pMeshModel);

	Model.bUse = true;

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)Model.pBuffMatModel->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (int i = 0; i < (int)Model.nNumMatModel; i++)
	{
		Model.pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename != nullptr)
		{// �}�e���A���Őݒ肳��Ă���e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFileA(pD3DDevice,
				pMat[i].pTextureFilename,
				&Model.pTexture[i]);
		}
		else
		{
			Model.pTexture[i] = nullptr;
		}
	}

	//���f���̓o�^
	return C3DObject::SetModel(&Model);
}