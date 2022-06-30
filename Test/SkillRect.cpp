#include "stdafx.h"
#include "SkillRect.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SceneMgr.h"



CSkillRect::CSkillRect() : m_DrawID(0)
{
}


CSkillRect::~CSkillRect()
{
}

void CSkillRect::Initialize(void)
{
	m_tInfo.fX = 100;
	m_tInfo.fY = 100;
	m_tInfo.fCX = 45;
	m_tInfo.fCY = 45;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Non.bmp", L"NonSkill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/ThunderSkill.bmp", L"ThunderSkill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/FireSkill2.bmp", L"KaguraSkill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/FireSkill.bmp", L"FireSkill");
}

int CSkillRect::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSkillRect::Late_Update(void)
{
	//if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_State() == CPlayer::UPGRADE)
	{
		if (m_DrawID == 0)
			m_pFrameKey = L"NonSkill";
		else if (m_DrawID == 1)
			m_pFrameKey = L"ThunderSkill";
		else if (m_DrawID == 2)
			m_pFrameKey = L"KaguraSkill";
		else if (m_DrawID == 3)
			m_pFrameKey = L"FireSkill";
	}
	


	//if (CSceneMgr::Get_Instance()->Get_SolvedQuestNumber() < 3)
		//m_pFrameKey = L"NonSkill";
}

void CSkillRect::Render(HDC hDC)
{
	HDC	hHpDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left) - 7,	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top) - 20,
		int(m_tInfo.fCX) + 10,				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY) + 10 ,
		hHpDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		57,				// ������ ��Ʈ���� ����, ���� ����
		57,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CSkillRect::Release(void)
{
}
