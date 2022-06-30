#include "stdafx.h"
#include "EditMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"


CEditMenu::CEditMenu() : m_dwDrawTime(GetTickCount()), m_iDrawID(0)
{
}


CEditMenu::~CEditMenu()
{
	Release();
}

void CEditMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/EditMenu.bmp", L"EditMenu");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Quit.bmp", L"Quit");


	CObj*	pObj = CAbstractFactory<CMyButton>::Create(100.f, 100.f);
	pObj->Set_FrameKey(L"Back");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(100.f, 200.f);
	pObj->Set_FrameKey(L"Quit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);
}

int CEditMenu::Update(void)
{
	
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CEditMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (m_dwDrawTime + 200 < GetTickCount())
	{
		m_iDrawID += Temp;
		if (m_iDrawID == 4 || m_iDrawID == 0)
			Temp *= -1;

		m_dwDrawTime = GetTickCount();
	}
}

void CEditMenu::Render(HDC hDC)
{
	HDC	hMenuDC = CBmpMgr::Get_Instance()->Find_Image(L"EditMenu");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		0,	// 2,3 ���� :  ������� ��ġ X, Y
		0,
		WINCX,				// 4,5 ���� : ������� ����, ���� ����
		WINCY,
		hMenuDC,							// ��Ʈ���� ������ �ִ� DC
		(500) * m_iDrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		500,				// ������ ��Ʈ���� ����, ���� ����
		333,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����

	CObjMgr::Get_Instance()->Render(hDC);
}
 
void CEditMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
