#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "WalkTile.h"
#include "AbstractFactory.h"

CTile::CTile() : m_bCount(false)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_eTiletype = TILE_EDIT;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iOption = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile2.bmp", L"Tile");
	m_pFrameKey = L"Tile";
}

int CTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
	if (m_iOption == 2 && !m_bCount && CTileMgr::Get_Instance()->Get_SolvedTiles() != 0)
	{
		CTileMgr::Get_Instance()->Add_Tiles(TILE_WALK, CAbstractFactory<CWalkTile>::Create(m_tInfo.fX, m_tInfo.fY));
		m_bCount = true;
	}
}

void CTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		30 * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		30,				// ������ ��Ʈ���� ����, ���� ����
		30,
		RGB(0, 255, 0));			// �����ϰ��� �ϴ� ����
}

void CTile::Release(void)
{
}
