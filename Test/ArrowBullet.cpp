#include "stdafx.h"
#include "ArrowBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "BlockMgr.h"

CArrowBullet::CArrowBullet() : dwTime(GetTickCount())
{
}


CArrowBullet::~CArrowBullet()
{
	Release();
}

void CArrowBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ArrowBullet.bmp", L"ArrowBullet");
	m_eGroup = RENDER_EFFECT;

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_fSpeed = 10.f;
}

int CArrowBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CArrowBullet::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Block(CBlockMgr::Get_Instance()->Get_Blocks(), this))
		m_bDead = true;
	if (CCollisionMgr::Collsion_Tile(CTileMgr::Get_Instance()->Get_EditTiles(), this))
		m_bDead = true;

	BulletFrame();

	if (dwTime + 500 < GetTickCount())
	{
		m_bDead = true;
		dwTime = GetTickCount();
	}
}

void CArrowBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ArrowBullet");
	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX) - 25,	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY) - 25,
		int(m_tInfo.fCX) + 50,				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY) + 50,
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (100),								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		(100) * m_tFrame.iMotion,
		100,				// ������ ��Ʈ���� ����, ���� ����
		100,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CArrowBullet::Release(void)
{
}

void CArrowBullet::Move(void)
{
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		m_tFrame.iMotion = 1;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		m_tFrame.iMotion = 3;

		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		m_tFrame.iMotion = 2;

		break;
	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		m_tFrame.iMotion = 0;

		break;
	}
}
