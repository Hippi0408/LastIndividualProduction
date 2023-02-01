//=============================================================================
//
// enemyu_smallfish.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy_smallfish.h"
#include "read.h"
#include "game.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "player.h"
#include "input.h"
#include "object_type_list.h"
#include "convenience_function.h"
#include "enemy_manager.h"

const D3DXVECTOR3 CEnemy_SmallFish::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy_SmallFish::MOVE_INERTIA = 5.0f;
const float CEnemy_SmallFish::JUMP_INERTIA = 0.1f; 
const float CEnemy_SmallFish::INIT_RADIUS = 100.0f;
const float CEnemy_SmallFish::SEARCH_RANGE = 1000.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy_SmallFish::CEnemy_SmallFish()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy_SmallFish::~CEnemy_SmallFish()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemy_SmallFish::Init()
{

	//�e�N���X�̏�����
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//���C�t�̐ݒ�
	SetLife(INIT_LIFE);

	//�����̈ʒu
	SetPos(INIT_POS);

	//�P�t���[���O�̈ʒu
	SetOldPos(INIT_POS);

	//�ړ��ʂ̏�����
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�����̏�����
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���[�V�������f���̐ݒ菈��
	SetMotionModel();

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemy_SmallFish::Uninit()
{
	//�e�N���X�̏I������
	CEnemy::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy_SmallFish::Update()
{
	//�e�N���X�̍X�V����
	CEnemy::Update();

	//���g�̈ʒu
	D3DXVECTOR3 pos = GetPos();

	//�}�l�[�W���[����v���C���[�̏��̎擾
	CManager* pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();
	CPlayer* pPlayer = pGame->GetPlayer();

	//�v���C���[�̈ʒu
	D3DXVECTOR3 PLpos = pPlayer->GetPos();

	//���G�͈͂ɂ��邩�ǂ���
	if (!CConvenience_Function::CircleCollision(pos, SEARCH_RANGE, PLpos, 0.0f))
	{
		return;
	}

	//�v���C���[�̕����ւ̃x�N�g��
	D3DXVECTOR3 vec = CConvenience_Function::PointOrientationVectorGeneration(PLpos, pos);


	//�v���C���[�ɋ߂Â�
	AddPos(vec * MOVE_INERTIA);


	//�G�l�~�[�}�l�[�W���[�̎擾
	CEnemy_Manager* pEnemy_Manager = pGame->GetEnemy_Manager();

	//�����蔻��(���̃G�l�~�[�Ƃ�)
	pEnemy_Manager->EnemyOnEnemyCollision(this);

	//�G�l�~�[��rot
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	rot.y = atan2f(vec.x, vec.z) + D3DX_PI;

	//rot�ݒ�
	SetRot(rot);


	//���[�V����
	CMotionParts::MoveMotionModel(GetMotionNum(), 0, &GetPos(), &GetRot());

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy_SmallFish::Draw()
{
	//�e�N���X�̕`�揈��
	CEnemy::Draw();
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemy_SmallFish::IsUnused()
{
	if (CMovable_Obj::CheckLife())
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// ���[�V�������f���̐ݒ菈��
//*****************************************************************************
void CEnemy_SmallFish::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionenemy.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}
