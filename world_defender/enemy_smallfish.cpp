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
#include "ballast_manager.h"

const D3DXVECTOR3 CEnemy_SmallFish::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy_SmallFish::MOVE_INERTIA = 5.0f;
const float CEnemy_SmallFish::JUMP_INERTIA = 0.1f; 
const float CEnemy_SmallFish::INIT_RADIUS = 100.0f;
const float CEnemy_SmallFish::SEARCH_RANGE = 1000.0f;
const D3DXVECTOR3 CEnemy_SmallFish::ENEMY_SIZE_MAX = D3DXVECTOR3(INIT_RADIUS, INIT_RADIUS, INIT_RADIUS);
const D3DXVECTOR3 CEnemy_SmallFish::ENEMY_SIZE_MIN = D3DXVECTOR3(-INIT_RADIUS, 0.0f, -INIT_RADIUS);
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy_SmallFish::CEnemy_SmallFish()
{
	m_nRandomMoveCnt = 0;
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
	//���[�V����
	//CMotionParts::UnUpdateDraw();
	CMotionParts::DestructionMotionModel(GetMotionNum());

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
	if (CConvenience_Function::CircleCollision(pos, SEARCH_RANGE, PLpos, 0.0f))
	{
		//�v���C���[�̕����ւ̃x�N�g��
		D3DXVECTOR3 vec = CConvenience_Function::PointOrientationVectorGeneration(PLpos, pos);

		//Y�������Ȃ���
		vec.y = 0.0f;

		//�v���C���[�ɋ߂Â�
		SetMove(vec * MOVE_INERTIA);
	}
	else
	{
		//�����_���s��
		RandomMove();
	}
	


	//�G�l�~�[�}�l�[�W���[�̎擾
	CEnemy_Manager* pEnemy_Manager = pGame->GetEnemy_Manager();

	//�����蔻��(���̃G�l�~�[�Ƃ�)
	pEnemy_Manager->EnemyOnEnemyCollision(this);

	

	

	//-------------------------------------------------------
	// ���I�Ƃ̓����蔻��
	//-------------------------------------------------------

	//���I�}�l�[�W���[�̎擾
	CBallast_Manager* pBallast_Manager = pGame->GetBallast_Manager();

	//�}�b�v��̂ǂ��ɋ��邩
	int nMapGrid = pGame->GetMeshfield()->CheckPosLocation(pos);

	//�}�b�v�̉��s�Ƀ��b�V����
	int nDepthGrid = pGame->GetMeshfield()->GetMeshZ();

	//�����蔻����`�F�b�N���郁�b�V��
	int aMapGrid[CHECK_RANGE];

	//�v���C���[�̂��郁�b�V��
	int nEnemyMapGrid = nMapGrid - nDepthGrid;

	//�v���C���[�̂��郁�b�V���������W�ӏ��̊���o��
	for (int nCnt = 0; nCnt < CHECK_RANGE_X; nCnt++)
	{
		aMapGrid[nCnt * CHECK_RANGE_X] = nEnemyMapGrid + nDepthGrid * nCnt - 1;
		aMapGrid[nCnt * CHECK_RANGE_X + 1] = nEnemyMapGrid + nDepthGrid * nCnt;
		aMapGrid[nCnt * CHECK_RANGE_X + 2] = nEnemyMapGrid + nDepthGrid * nCnt + 1;
	}

	//���I�Ƃ̓����蔻��
	D3DXVECTOR3 Add = GetPos();

	//�w��͈͂̊��I�̓����蔻��
	for (int nCnt = 0; nCnt < CHECK_RANGE; nCnt++)
	{
		//���I�̓����蔻��
		Add = pBallast_Manager->CollisionBallast(aMapGrid[nCnt], GetPos(), GetOldPos(), ENEMY_SIZE_MAX, ENEMY_SIZE_MIN);

		if (Add != GetPos())
		{
			break;
		}

	}

	//���I�Ƃ̓����蔻��
	SetPos(Add);


	//�G�l�~�[��rot
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 MoveVec = GetMoveVec();
	rot.y = atan2f(MoveVec.x, MoveVec.z) - D3DX_PI;

	//rot�ݒ�
	SetRot(rot);


	//���[�V����
	CMotionParts::MoveMotionModel(GetMotionNum(), 1, &GetPos(), &GetRot());

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

	//SetMotionNum(cRead.ReadMotion("data/MOTION/motionenemy.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}

//*****************************************************************************
// �����_���s��
//*****************************************************************************
void CEnemy_SmallFish::RandomMove()
{
	if (m_nRandomMoveCnt > 0)
	{
		m_nRandomMoveCnt--;

		D3DXVECTOR3 moveVec =  GetMoveVec();

		SetMove(MOVE_INERTIA * moveVec);

		return;
	}

	m_nRandomMoveCnt = rand() % RANDOM_MOVE_CNT_MAX;

	float fAngle = D3DXToRadian(rand() % 360);

	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	vec.x = cosf(fAngle);
	vec.z = sinf(fAngle);
	vec.y = 0.0f;

	D3DXVec3Normalize(&vec,&vec);


	SetMove(MOVE_INERTIA * vec);
}
