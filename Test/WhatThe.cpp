#include "stdafx.h"
#include "WhatThe.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CWhatThe::CWhatThe(): m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CWhatThe::~CWhatThe()
{
	Release();
}

void CWhatThe::Initialize(void)
{
	m_eItemType = ITEM_STRANGEMAN;
	m_tInfo.fCX = 25;
	m_tInfo.fCY = 50;
	m_fSpeed = 0.2f;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/WhatMan.bmp", L"WhatMan");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/TextBar_WhatThe.bmp", L"TextBar_WhatThe");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.dwFrameSpeed = 100;
	m_pFrameKey = L"WhatMan";
}

int CWhatThe::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CWhatThe::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;

	Move_Frame();
}

void CWhatThe::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hItemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart *(16),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		16,				// ������ ��Ʈ���� ����, ���� ����
		32,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����


	if (m_bCount)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBar_WhatThe");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			150,	// 2,3 ���� :  ������� ��ġ X, Y
			500,
			500,				// 4,5 ���� : ������� ����, ���� ����
			50,
			hTextDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			600,				// ������ ��Ʈ���� ����, ���� ����
			61,
			RGB(192, 192, 255));			// �����ϰ��� �ϴ� ����
	}
}

void CWhatThe::Release(void)
{
}

void CWhatThe::Get_Effect(void)
{
	if (!m_bCount)
	{
		m_dwTime = GetTickCount();
		m_bCount = true;
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::EFFECT);
		m_tInfo.fY -= 15;
	}

	if (m_dwTime + 3000 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_bDead = true;

		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
	}

}
