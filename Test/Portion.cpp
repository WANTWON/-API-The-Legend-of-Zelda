#include "stdafx.h"
#include "Portion.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"



CPortion::CPortion() : m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CPortion::~CPortion()
{
}

void CPortion::Initialize(void)
{
	m_eItemType = ITEM_PORTION;
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 35;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Portion.bmp", L"Portion");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_pFrameKey = L"Portion";
}

int CPortion::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPortion::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;
}

void CPortion::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hItemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			14,				// ������ ��Ʈ���� ����, ���� ����
			16,
			RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����

}

void CPortion::Release(void)
{
}

void CPortion::Get_Effect(void)
{
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_dwTime = GetTickCount();
		m_bCount = true;
	}

	float m_fJumpPower = 12.f;
	m_tInfo.fY -= m_fJumpPower * m_fTime - (9.8f * m_fTime * m_fTime * 0.5f);
	m_fTime += 0.1f;


	if (m_dwTime + 500 < GetTickCount())
	{
		m_bDead = true;
		int Coin = 1;
		if (m_iOption == 1)
		{
			switch (m_iDrawID)
			{
			case 0:
				Coin = 50;
				break;
			case 1:
				Coin = 100;
				break;
			case 2:
				Coin = 300;
				break;
			default:
				break;
			}
		}
		CObjMgr::Get_Instance()->Get_Player()->Set_Hp();
	}
}
