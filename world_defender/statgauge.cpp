//=============================================================================
//
// statgauge.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "statgauge.h"
#include "gauge.h"
#include <assert.h>

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CStatGauge::CStatGauge()
{
	m_pStatGauge = nullptr;
	m_nCntRecovery = 0;
	m_nValue = 0;
	m_GaugeState = NormalGauge;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CStatGauge::~CStatGauge()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CStatGauge::Init()
{
	m_pStatGauge = CGauge::Create();

	if (FAILED(m_pStatGauge->Init()))
	{
		return -1;
	}

	m_pStatGauge->SetFadeSpeed(0.1f);
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CStatGauge::Uninit()
{
	if (m_pStatGauge != nullptr)
	{
		m_pStatGauge = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CStatGauge::Update()
{
	if (m_GaugeState == GaugeBreak)
	{
		return;
	}

	if (m_nValue <= 0)
	{
		m_GaugeState = BreakTime;
	}

	m_nCntRecovery++;

	if (m_nCntRecovery >= m_nCntRecoveryMax)
	{
		m_nCntRecovery = 0;
		SetStatGauge(m_nRecovery);
	}

	m_pStatGauge->Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CStatGauge::Draw()
{
}

//*****************************************************************************
// ���C�t�o�[�̍쐬
//*****************************************************************************
void CStatGauge::CreateStatBar(SStatGauge SStatGauge)
{
	if (m_pStatGauge != nullptr)
	{
		m_nRecovery = SStatGauge.nRecovery;
		m_nValue = SStatGauge.nValueMax;
		m_nValueMax = SStatGauge.nValueMax;
		m_nCntRecoveryMax = SStatGauge.nRecoveryCntMaqx;
		m_pStatGauge->SetUp(SStatGauge.pos, SStatGauge.rot);
		m_pStatGauge->SetDiagonalLine(SStatGauge.fXSize, 0.0f);
		m_pStatGauge->SetNumerics(SStatGauge.nValueMax, SStatGauge.nValueMax);
		m_pStatGauge->SetHeightElasticity(SStatGauge.fYSize);
		m_pStatGauge->SetHeightMax(SStatGauge.fYSize);
		m_pStatGauge->SetColor(SStatGauge.color);
		m_pStatGauge->SetTextIndex(0);
		m_pStatGauge->SetPolygon();
	}
}

//*****************************************************************************
// �_���[�W����
//*****************************************************************************
void CStatGauge::SetStatGauge(int nStatGauge)
{
	
	if (m_nValue + nStatGauge > m_nValueMax)
	{
		if (m_GaugeState == BreakTime)
		{
			m_GaugeState = NormalGauge;
		}
		m_nValue = m_nValueMax;
	}
	else if(m_nValue + nStatGauge < 0)
	{
		if (m_GaugeState == BreakTime)
		{
			m_GaugeState = GaugeBreak;
		}
		m_nValue = 0;
	}
	else
	{
		if (m_GaugeState == BreakTime)
		{
			m_pStatGauge->SetFlashing(10);
			if (nStatGauge < 0)
			{
				m_GaugeState = GaugeBreak;
				m_pStatGauge->ChangeNumerics(0);
			}
		}
		m_nValue += nStatGauge;
	}

	if (m_pStatGauge != nullptr)
	{
		m_pStatGauge->ChangeNumerics(m_nValue);
	}

	m_pStatGauge->Update();
}

//*****************************************************************************
// �Q�[�W�̏�Ԏ擾
//*****************************************************************************
bool CStatGauge::GetGaugeState(GaugeState GaugeState)
{
	if (m_GaugeState == GaugeState)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// �_���[�W����
//*****************************************************************************
bool CStatGauge::ValueCheck()
{
	if (m_nValue <= 0)
	{
		return true;
	}
	return false;
}

bool CStatGauge::ValueCheck(int nCheck)
{
	if (m_nValue >= nCheck)
	{
		return true;
	}
	return false;
}
