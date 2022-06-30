#include "stdafx.h"
#include "WalkTile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CWalkTile::CWalkTile()
{
}


CWalkTile::~CWalkTile()
{
	Release();
}

void CWalkTile::Initialize(void)
{
	m_eTiletype = TILE_WALK;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_eGroup = RENDER_GAMEOBJECT;

	m_iOption = 0;
	m_iDrawID = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/WalkTile.bmp", L"WalkTile");
}

int CWalkTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CWalkTile::Late_Update(void)
{
}

void CWalkTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(L"WalkTile");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		16 * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		16,				// ������ ��Ʈ���� ����, ���� ����
		16,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CWalkTile::Release(void)
{
}
