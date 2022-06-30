#include "stdafx.h"
#include "Door.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "BlockMgr.h"
#include "TileMgr.h"

CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX + 5;
	m_tInfo.fCY = BLOCKCY + 5;
	m_eBlockType = BLOCK_CHEST;
	m_eGroup = RENDER_GAMEOBJECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_iOption = 0;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Door.bmp", L"Door");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Door_Text.bmp", L"Door_Text");

	m_pFrameKey = L"Door";
}

int CDoor::Update(void)
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"secret.wav", PUZZLE_EFFECT, g_fSound);
		return OBJ_DEAD;
	}
		

	Update_Rect();

	return OBJ_NOEVENT;
}

void CDoor::Late_Update(void)
{
	if (m_eDoortype == DOOR_3)
	{
		m_tInfo.fCX = BLOCKCX*2 + 5;
		m_tInfo.fCY = BLOCKCY*2 + 5;
	}
	if (CTileMgr::Get_Instance()->Get_SolvedTiles() != 0 && m_eDoortype == DOOR_1)
		m_bDead = true;
	else if (CTileMgr::Get_Instance()->Get_SolvedTiles() >= 7 && m_eDoortype == DOOR_2)
		m_bDead = true;
	else if (CBlockMgr::Get_Instance()->Get_iSolvedBlock() >= 14 && m_eDoortype == DOOR_3)
		m_bDead = true;



}

void CDoor::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX) + 20,				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		24,				// ������ ��Ʈ���� ����, ���� ����
		15,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CDoor::Release(void)
{
}
