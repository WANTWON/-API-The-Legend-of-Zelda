#include "stdafx.h"
#include "FireBullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Player.h"

CFireBullet::CFireBullet()
	: dwTime(GetTickCount())
{
}


CFireBullet::~CFireBullet()
{
	Release();
}

void CFireBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/FireBullet.bmp", L"FireBullet");

	m_tInfo.fCX = 80.f;
	m_eGroup = RENDER_EFFECT;
	m_tInfo.fCY = 80.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.iMotion = 0;
	m_pFrameKey = L"FireBullet";
}

int CFireBullet::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CFireBullet::Late_Update(void)
{
	if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() != CPlayer::SKILL_FIRE)
		m_bDead = true;

	BulletFrame();

	switch (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Direction())
	{
	case DIR_DOWN:
		m_tFrame.iMotion = 1;
		break;
	case DIR_UP:
		m_tFrame.iMotion = 0;
		break;
	case DIR_LEFT:
		m_tFrame.iMotion = 2;
		break;
	case DIR_RIGHT:
		m_tFrame.iMotion = 3;
		break;
	default:
		break;
	}
}

void CFireBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX) - 25,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY) - 25,
			int(m_tInfo.fCX) + 50,				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY) + 50,
			hItemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iMotion*(150),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iFrameStart*(150),
			150,				// ������ ��Ʈ���� ����, ���� ����
			150,
			RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CFireBullet::Release(void)
{
}
