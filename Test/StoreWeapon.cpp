#include "stdafx.h"
#include "StoreWeapon.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "MenuObjMgr.h"
#include "AbstractFactory.h"
#include "ItemTile.h"


CStoreWeapon::CStoreWeapon() : m_dwTime(GetTickCount()), m_bCount(false), m_bTextout(false), m_bSuccessBuy(false), m_bShortage_Money(false)
{
}


CStoreWeapon::~CStoreWeapon()
{
}

void CStoreWeapon::Initialize(void)
{
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 100;
	m_eGroup = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Mage.bmp", L"Item_Mage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Boomerang.bmp", L"Item_Boomerang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Bow.bmp", L"Item_Bow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Shield.bmp", L"Item_Shield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Inventory/Item/Fire.bmp", L"Item_Fire");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Wand.bmp", L"Text_Wand");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Shield.bmp", L"Text_Shield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Lanton.bmp", L"Text_Lanton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Bow.bmp", L"Text_Bow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Boomerang.bmp", L"Text_Boomerang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Hp.bmp", L"Text_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Text_Portion.bmp", L"Text_Portion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Purchase_success.bmp", L"Purchase_success");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store/TextBar/Money_is_scarce.bmp", L"Money_is_scarce");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Portion.bmp", L"Item_Portion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Heart.bmp", L"Item_Heart");


	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 0;
	//m_tFrame.dwFrameSpeed = 100;
}

int CStoreWeapon::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CStoreWeapon::Late_Update(void)
{

	switch (m_eType)
	{
	case CStoreWeapon::WEAPON:
		Set_WeaponType();
		break;
	case CStoreWeapon::HP:
		m_pFrameKey = L"Item_Heart";
		TextFrameKey = L"Text_Hp";
		iCoin = 50;
		break;
	case CStoreWeapon::PORTION:
		m_pFrameKey = L"Item_Portion";
		TextFrameKey = L"Text_Portion";
		iCoin = 10;
		break;
	default:
		break;
	}
	RECT rc = {};

	if (IntersectRect(&rc, &(CObjMgr::Get_Instance()->Get_Player()->Get_Rect()), &m_tRect))
	{
		if (m_bSuccessBuy)
			m_bTextout = false;
		else
			m_bTextout = true;
		

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			if (iCoin > CObjMgr::Get_Instance()->Get_Player()->Get_Coin())
			{
				m_bShortage_Money = true;
				return;
			}


			if (m_eType == WEAPON)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Buy.wav", SOUND_EFFECT, g_fSound - 0.4f);
				m_bSuccessBuy = true;
				CMenuObjMgr::Get_Instance()->Load_Weapon();
				CMenuObjMgr::Get_Instance()->Add_Weapon(m_eWeapontype);
				CMenuObjMgr::Get_Instance()->Update();
				CMenuObjMgr::Get_Instance()->Late_Update();
				CMenuObjMgr::Get_Instance()->Save_Weapon();
				CObjMgr::Get_Instance()->Get_Player()->Set_Coin(-iCoin);
				
			}
			else if (m_eType == HP)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"HpUp.wav", SOUND_EFFECT, g_fSound + 0.5f);
				CObjMgr::Get_Instance()->Get_Player()->Set_MaxHp();
				CObjMgr::Get_Instance()->Get_Player()->Set_Coin(-iCoin);
			}
			else if (m_eType == PORTION)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"HpPortion.wav", SOUND_EFFECT, g_fSound + 0.5f);
				CObjMgr::Get_Instance()->Get_Player()->Set_Coin(-iCoin);
				CObjMgr::Get_Instance()->Get_Player()->Set_Hp();
			}
				
			m_dwTime = GetTickCount();
			m_bTextout = false;
			m_bShortage_Money = false;
		}		
		
	}
	else
	{
		m_bTextout = false;
	}
	
	if ((m_bSuccessBuy||m_bShortage_Money) && m_dwTime + 1000 < GetTickCount() )
	{
		m_bSuccessBuy = false;
		m_bShortage_Money = false;
		m_dwTime = GetTickCount();
	}
}

void CStoreWeapon::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	if (m_eType == HP)
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY) + 25,
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY) - 70,
			hItemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			8,				// ������ ��Ʈ���� ����, ���� ����
			7,
			RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
	}
	else if (m_eType == PORTION)
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY) + 20,
			int(m_tInfo.fCX) + 5,				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY) - 60,
			hItemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			14,				// ������ ��Ʈ���� ����, ���� ����
			16,
			RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
	}
	else
	{
		HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX) - 10,	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + iScrollY) + 20,
			int(m_tInfo.fCX) + 20,				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY) - 60,
			hItemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			78,				// ������ ��Ʈ���� ����, ���� ����
			57,
			RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
	}
	

	if (m_bShortage_Money)
	{
		HDC hTextOutDC = CBmpMgr::Get_Instance()->Find_Image(L"Money_is_scarce");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			150,	// 2,3 ���� :  ������� ��ġ X, Y
			500,
			500,				// 4,5 ���� : ������� ����, ���� ����
			50,
			hTextOutDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			600,				// ������ ��Ʈ���� ����, ���� ����
			61,
			RGB(192, 192, 255));			// �����ϰ��� �ϴ� ����
	}
	else if (m_bSuccessBuy)
	{

		HDC hTextOutDC = CBmpMgr::Get_Instance()->Find_Image(L"Purchase_success");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			150,	// 2,3 ���� :  ������� ��ġ X, Y
			500,
			500,				// 4,5 ���� : ������� ����, ���� ����
			50,
			hTextOutDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			600,				// ������ ��Ʈ���� ����, ���� ����
			61,
			RGB(192, 192, 255));			// �����ϰ��� �ϴ� ����
	}
	else if (!m_bSuccessBuy && m_bTextout)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(TextFrameKey);

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

void CStoreWeapon::Release(void)
{
}

void CStoreWeapon::Set_WeaponType(void)
{
	
	switch (m_eWeapontype)
	{
	case WAND:
		m_pFrameKey = L"Item_Mage";
		TextFrameKey = L"Text_Wand";
		iCoin = 300;
		break;
	case ARROW:
		m_pFrameKey = L"Item_Bow";
		TextFrameKey = L"Text_Bow";
		iCoin = 70;
		break;
	case SHIELD:
		m_pFrameKey = L"Item_Shield";
		TextFrameKey = L"Text_Shield";
		iCoin = 100;
		break;
	case LANTON:
		m_pFrameKey = L"Item_Fire";
		TextFrameKey = L"Text_Lanton";
		iCoin = 100;
		break;
	case BOOMERANG:
		m_pFrameKey = L"Item_Boomerang";
		TextFrameKey = L"Text_Boomerang";
		iCoin = 100;
		break;
	}
}
