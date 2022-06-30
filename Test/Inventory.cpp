#include "stdafx.h"
#include "Inventory.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "MenuObjMgr.h"
#include "ItemTile.h"
#include "ChoosePoint.h"
#include "SceneMgr.h"

CInventory::CInventory() 
{

}


CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/EmptyInven2.bmp", L"Item_Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item_Rect.bmp", L"Item_Rect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item_Bar.bmp", L"Item_Bar");

	

	if (!CSceneMgr::Get_Instance()->Get_bCount())
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				CMenuObjMgr::Get_Instance()->Add_ItemTile((CAbstractFactory<CItemTile>::Create_Menu(220 + (j * 120), 180 + (i * 80))));
			}

		}
		CMenuObjMgr::Get_Instance()->Add_Weapon(SWORD, true);
		CSceneMgr::Get_Instance()->Set_bCount(true);
		CMenuObjMgr::Get_Instance()->Add_Object(MENU_CHOOSE, CAbstractFactory<CChoosePoint>::Create_Menu(CMenuObjMgr::Get_Instance()->Get_Inven()[0]->Get_Info().fX, CMenuObjMgr::Get_Instance()->Get_Inven()[0]->Get_Info().fY));
		static_cast<CChoosePoint*>(CMenuObjMgr::Get_Instance()->Get_ChoosePos())->Set_UsedIndex(0);
		
	}
	else
	{
		CMenuObjMgr::Get_Instance()->Load_Weapon();
		CMenuObjMgr::Get_Instance()->Add_Object(MENU_CHOOSE, CAbstractFactory<CChoosePoint>::Create_Menu(CMenuObjMgr::Get_Instance()->Get_Inven()[0]->Get_Info().fX, CMenuObjMgr::Get_Instance()->Get_Inven()[0]->Get_Info().fY));
		CMenuObjMgr::Get_Instance()->Load_ChoosePoint();
	}
	
	
	//CMenuObjMgr::Get_Instance()->Initialize();
	
	
	
}

int CInventory::Update(void)
{
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"InvenOpen.wav", SOUND_EFFECT, g_fSound);
		m_bCount = true;
	}
	CMenuObjMgr::Get_Instance()->Update();
	return 0;
}

void CInventory::Late_Update(void)
{
	CMenuObjMgr::Get_Instance()->Late_Update();
}

void CInventory::Render(HDC hDC)
{
	HDC	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"Item_Menu");

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

void CInventory::Release(void)
{
	CMenuObjMgr::Get_Instance()->Release();
	
}
