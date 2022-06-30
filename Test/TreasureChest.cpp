#include "stdafx.h"
#include "TreasureChest.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BlockMgr.h"
#include "Coin.h"
#include "AbstractFactory.h"
#include "Portion.h"
#include "Heart.h"
#include "Key.h"
#include "WhatThe.h"
#include "None.h"

CTreasureChest::CTreasureChest() :  m_fTime(0), m_bThrow(false), m_bBreak(false), m_bCount(false)
{
}


CTreasureChest::~CTreasureChest()
{
}

void CTreasureChest::Initialize(void)
{
	m_tInfo.fCX = BLOCKCX + 5;
	m_tInfo.fCY = BLOCKCY + 5;
	m_eBlockType = BLOCK_CHEST;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_iOption = 0;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Block/Treasure_Chest.bmp", L"Treasure_Chest");
	m_eITemType = ITEM_HEART;
	m_pFrameKey = L"Treasure_Chest";
}

int CTreasureChest::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTreasureChest::Late_Update(void)
{
	CCollisionMgr::Collsion_Bullets(CObjMgr::Get_Instance()->Get_Bullets(), this);

	if (m_tFrame.iFrameStart == 1 && !m_bCount)
	{

		CSoundMgr::Get_Instance()->PlaySound(L"chest open.wav", ITEM_EFFECT, g_fSound);
		switch (m_eITemType)
		{
		case ITEM_PORTION:
		{
			CObj* pObj = CAbstractFactory<CPortion>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			break;
		}
		case ITEM_HEART:
		{
			CObj* pObj = CAbstractFactory<CHeart>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			break;
		}
		case ITEM_KEY:
		{
			CObj* pObj = CAbstractFactory<CKey>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			break;
		}
		case ITEM_STRANGEMAN:
		{
			CObj* pObj = CAbstractFactory<CWhatThe>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			break;
		}		
		case ITEM_NOTHING:
		{
			CObj* pObj = CAbstractFactory<CNone>::Create(m_tInfo.fX, m_tInfo.fY);
			CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, pObj);
			break;
		}
		default:
			break;
		}
		
		m_bCount = true;
	}
}

void CTreasureChest::Render(HDC hDC)
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
		(16 + 8) * m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		16,				// ������ ��Ʈ���� ����, ���� ����
		16,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����
}

void CTreasureChest::Release(void)
{
}
