#include "stdafx.h"
#include "QuestTile.h"
#include "BmpMgr.h"


CQuestTile::CQuestTile() : m_bExist(false), m_iDrawID(0), m_QuestType(QUEST_END)
{
}


CQuestTile::~CQuestTile()
{
	Release();
}

void CQuestTile::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Empty.bmp", L"Quest_Empty");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/FieldQuest.bmp", L"FieldQuest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/StoreQuest.bmp", L"StoreQuest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/MiniQuest.bmp", L"MiniQuest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/MiniQuest2.bmp", L"MiniQuest2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Quest/MiniQuest3.bmp", L"MiniQuest3");
	m_pFrameKey = L"Quest_Empty";

	m_tInfo.fCX = 540;
	m_tInfo.fCY = 80;
}

int CQuestTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CQuestTile::Late_Update(void)
{
	switch (m_QuestType)
	{
	case FIELD_QUEST:
		m_pFrameKey = L"FieldQuest";

		break;
	case STORE_QUEST:
		m_pFrameKey = L"StoreQuest";

		break;
	case MINIQUEST_FLOWER:
		m_pFrameKey = L"MiniQuest3";

		break;
	case MINIQUEST_WRITER:
		m_pFrameKey = L"MiniQuest2";
		break;

	case MINIQUEST_KEY:
		m_pFrameKey = L"MiniQuest";

		break;
	}
}

void CQuestTile::Render(HDC hDC)
{
	HDC hSwordMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		m_tRect.left,	// 2,3 ���� :  ������� ��ġ X, Y
		m_tRect.top,
		m_tInfo.fCX,				// 4,5 ���� : ������� ����, ���� ����
		m_tInfo.fCY,
		hSwordMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_iDrawID*80,
		530.f,				// ������ ��Ʈ���� ����, ���� ����
		80.f,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CQuestTile::Release(void)
{
}
