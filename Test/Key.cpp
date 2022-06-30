#include "stdafx.h"
#include "Key.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "MenuObjMgr.h"
#include "SceneMgr.h"

CKey::CKey() : m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CKey::~CKey()
{
}

void CKey::Initialize(void)
{
	m_eItemType = ITEM_KEY;
	m_tInfo.fCX = 25;
	m_tInfo.fCY = 30;
	m_eGroup = RENDER_PLAYERUPOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Key.bmp", L"Key");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/TextBar_Key.bmp", L"TextBar_Key");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_pFrameKey = L"Key";
}

int CKey::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CKey::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;
}

void CKey::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hItemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		14,				// ������ ��Ʈ���� ����, ���� ����
		16,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����

	if (m_bCount)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBar_Key");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			150,	// 2,3 ���� :  ������� ��ġ X, Y
			500,
			500,				// 4,5 ���� : ������� ����, ���� ����
			50,
			hTextDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			600,				// ������ ��Ʈ���� ����, ���� ����
			61,
			RGB(192, 192, 255));			// �����ϰ��� �ϴ� ����
	}
}

void CKey::Release(void)
{
}

void CKey::Get_Effect(void)
{
	if (!m_bCount)
	{
		m_dwTime = GetTickCount();
		m_bCount = true;
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::EFFECT);
		m_tInfo.fY -= 15;
	}

	if (m_dwTime + 3000 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_bDead = true;
		CSceneMgr::Get_Instance()->Set_SolvedQuestNumber();

		CMenuObjMgr::Get_Instance()->Load_Quest();
		CMenuObjMgr::Get_Instance()->Set_QuestComplete(MINIQUEST_KEY);
		CMenuObjMgr::Get_Instance()->Update();

		CMenuObjMgr::Get_Instance()->Late_Update();
		CMenuObjMgr::Get_Instance()->Save_Quest();
		CObjMgr::Get_Instance()->Get_Player()->Set_Key();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
	}
}

