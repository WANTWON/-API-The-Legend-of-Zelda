#include "stdafx.h"
#include "Mushroom.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BlockMgr.h"
#include "Coin.h"
#include "AbstractFactory.h"

CMushroom::CMushroom() : m_bBePull(false), m_bPullend(false), m_ePreDIR(DIR_END), m_bCount(false)
{
}


CMushroom::~CMushroom()
{
}

void CMushroom::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX;
	m_tInfo.fCY = BLOCKCY;
	m_eGroup = RENDER_GAMEOBJECT;

	m_eBlockType = BLOCK_MUSHROOM;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.iMotion = 0;
	m_tFrame.dwFrameTime = GetTickCount();
	m_iOption = 0;
	m_eDir = DIR_RIGHT;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/MushRoom2.bmp", L"MushRoom");

	m_pFrameKey = L"MushRoom";
}

int CMushroom::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMushroom::Late_Update(void)
{
	if (m_bEditorMode)
		return;

	if (!m_bBePull)
	{
		Direction_Change();
		Motion_Change();
		//Move_Frame();
	}

	Be_Pull_Motion();
}

void CMushroom::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX) - 100,	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY) - 100,
		int(m_tInfo.fCX) + 200,				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY) + 225,
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		(100) * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		(200) * m_tFrame.iMotion + (m_iOption*100),
		100,				// ������ ��Ʈ���� ����, ���� ����
		100,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CMushroom::Release(void)
{
}

void CMushroom::Direction_Change(void)
{
	if (m_bEditorMode)
		return;

	DIRECTION Dir =  CObjMgr::Get_Instance()->Get_Player()->Get_Direction();

	switch (Dir)
	{
	case DIR_LEFT:
		m_eDir = DIR_RIGHT;
		break;
	case DIR_UP:
		m_eDir = DIR_DOWN;
		break;
	case DIR_RIGHT:
		m_eDir = DIR_LEFT;
		break;
	case DIR_DOWN:
		m_eDir = DIR_UP;
		break;
	}

}

void CMushroom::Motion_Change(void)
{

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 2;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case DIR_UP:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case DIR_RIGHT:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 1;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	case DIR_DOWN:
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 3;

		m_tFrame.dwFrameSpeed = 100;
		m_tFrame.dwFrameTime = GetTickCount();
		break;
	}

}

void CMushroom::Be_Pull_Motion(void)
{
	if (m_bBePull)
	{
		if (!m_bCount)
		{
			m_bCount = true;
			CSoundMgr::Get_Instance()->StopSound(ITEM_EFFECT);
			CSoundMgr::Get_Instance()->PlaySoundW(L"Pull.wav", ITEM_EFFECT, g_fSound + 0.3f);
		}
		

		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			++m_tFrame.iFrameStart;

			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			}

			m_tFrame.dwFrameTime = GetTickCount();
		}
	}
	else if (m_bPullend)
	{
		if(m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			--m_tFrame.iFrameStart;

			if (m_tFrame.iFrameStart <= 0)
			{
				m_tFrame.iFrameStart = 0;
			}

			m_tFrame.dwFrameTime = GetTickCount();
		}
	}

	
}
