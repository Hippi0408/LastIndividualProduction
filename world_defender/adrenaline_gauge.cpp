//=============================================================================
//
// �A�h���i�����Q�[�W���� [adrenaline_gauge.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "adrenaline_gauge.h" 
#include "texture.h"
#include "2d6polygon.h"

const D3DXVECTOR3 CAdrenaline_Gauge::INIT_POS = D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
const float CAdrenaline_Gauge::INIT_HEIGHT = 600.0f;
const float CAdrenaline_Gauge::INIT_WIDTH = 200.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CAdrenaline_Gauge::CAdrenaline_Gauge()
{
	m_Pos = INIT_POS;
	m_nGauge = 0;
	m_nGaugeDest = 0;
	m_pGauge = nullptr;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CAdrenaline_Gauge::~CAdrenaline_Gauge()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CAdrenaline_Gauge::Init()
{
	//���̊m��
	m_pGauge = new C2D6Polygon;

	//������
	if (FAILED(m_pGauge->Init()))
	{
		return -1;
	}

	int nIndex = CTexture::LoadTexture("data/TEXTURE/�A�h���i�����Q�[�W.png");
	m_pGauge->SetTextIndex(nIndex);
	m_pGauge->SetPos(INIT_POS);
	m_pGauge->SetDiagonalLine(INIT_WIDTH, INIT_HEIGHT);
	m_pGauge->SetPolygon();


	return S_OK;
}

//*****************************************************************************
// ������(Pos����)
//*****************************************************************************
HRESULT CAdrenaline_Gauge::Init(D3DXVECTOR3 Pos)
{
	//�ʒu�̕ۊ�
	m_Pos = Pos;

	//������
	if (FAILED(Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CAdrenaline_Gauge::Uninit()
{
	//���̉��
	if (m_pGauge != nullptr)
	{
		//�I������
		m_pGauge->Uninit();
		delete m_pGauge;
		m_pGauge = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CAdrenaline_Gauge::Update()
{

	m_nCounter++;
	if (m_nCounter > COUNTER_MAX)
	{
		m_nCounter = 0;
		if (m_nGaugeDest > 0)
		{
			m_nGaugeDest -= AUTOMATIC_DECREASE;
		}
	}
	


	if (m_nGaugeDest > m_nGauge)
	{
		m_nGauge++;
	}
	else if (m_nGaugeDest < m_nGauge)
	{
		m_nGauge--;
	}

	float fRatio = (float)m_nGauge / MAX_GAUGE;

	m_pGauge->SetRatio(fRatio);

	m_pGauge->Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CAdrenaline_Gauge::Draw()
{
	//�`�揈��
	m_pGauge->Draw();
}

void CAdrenaline_Gauge::AddGauge(int nAdd)
{
	m_nGaugeDest += nAdd;
}

