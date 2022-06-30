#include "stdafx.h"
#include "Seed.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "BlockMgr.h"

CSeed::CSeed() : m_dwTime(GetTickCount()), m_bCount(false)
{
}


CSeed::~CSeed()
{
}

void CSeed::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX;
	m_tInfo.fCY = BLOCKCY;

	m_eBlockType = BLOCK_SEED;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_iOption = 0;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Seed.bmp", L"Seed");
	m_iOption = rand() % 3;
	m_pFrameKey = L"Seed";
}

int CSeed::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSeed::Late_Update(void)
{
	if (m_bEditorMode)
		return;

	if ((CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this)) && m_dwTime + 50 < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart >= m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			if (!m_bCount)
			{
				CBlockMgr::Get_Instance()->Set_SeedSolved();
				m_bCount = true;
			}
		}
			
		m_dwTime = GetTickCount();
	}
}

void CSeed::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hTileDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hTileDC,							// ��Ʈ���� ������ �ִ� DC
		(16) * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_iOption * 16,
		16,				// ������ ��Ʈ���� ����, ���� ����
		16,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CSeed::Release(void)
{
}
