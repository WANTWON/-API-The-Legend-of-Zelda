#include "stdafx.h"
#include "Quest.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "MenuObjMgr.h"
#include "QuestTile.h"
#include "ChoosePoint.h"
#include "SceneMgr.h"


CQuest::CQuest()
{
}


CQuest::~CQuest()
{
	Release();
}

void CQuest::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Quest_Menu.bmp", L"Quest_Menu");

	if (!CSceneMgr::Get_Instance()->Get_bQuestCount())
	{
		for (int i = 0; i < 3; ++i)
		{
				CMenuObjMgr::Get_Instance()->Add_QuestTile(CAbstractFactory<CQuestTile>::Create_Menu(400, 200 + (i * 112)));	
		}
		CSceneMgr::Get_Instance()->Set_bQuestCount(true);

	}
	else
	{
		CMenuObjMgr::Get_Instance()->Load_Quest();
	}

}

int CQuest::Update(void)
{
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOpen.wav", SOUND_EFFECT, g_fSound);
		m_bCount = true;
	}
	CMenuObjMgr::Get_Instance()->Update();
	return 0;
}

void CQuest::Late_Update(void)
{
	CMenuObjMgr::Get_Instance()->Late_Update();
}

void CQuest::Render(HDC hDC)
{
	HDC	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Quest_Menu");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		0,	// 2,3 ���� :  ������� ��ġ X, Y
		0,
		WINCX,				// 4,5 ���� : ������� ����, ���� ����
		WINCY,
		hMenuDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		240,				// ������ ��Ʈ���� ����, ���� ����
		180,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����

	CMenuObjMgr::Get_Instance()->Render(hDC);
}

void CQuest::Release(void)
{
	CMenuObjMgr::Get_Instance()->Release();
}
