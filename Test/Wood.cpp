#include "stdafx.h"
#include "Wood.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BlockMgr.h"
#include "Coin.h"
#include "AbstractFactory.h"
#include "Portion.h"

CWood::CWood()
{
}


CWood::~CWood()
{
	Release();
}

void CWood::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX*1.5f;
	m_tInfo.fCY = BLOCKCY*1.5f;

	m_eBlockType = BLOCK_WOOD;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 70;
	m_iOption = 5;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MIni/Wood.bmp", L"Wood");

	m_pFrameKey = L"Wood";
}

int CWood::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CWood::Late_Update(void)
{
	if (m_bEditorMode)
		return;
}

void CWood::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX) ,	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY) ,
		int(m_tInfo.fCX) ,				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY) ,
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		38,				// ������ ��Ʈ���� ����, ���� ����
		32,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CWood::Release(void)
{
}
