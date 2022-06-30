#include "stdafx.h"
#include "EndingLogo.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CEndingLogo::CEndingLogo() : m_dwDrawTime(GetTickCount()), m_DrawEffectID(0), m_DrawUIID(0), m_dwButtonTime(GetTickCount())
, m_DrawPhotoID(0), m_dwPhotoTime(GetTickCount())
{
}


CEndingLogo::~CEndingLogo()
{
	Release();
}

void CEndingLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/BackGround.bmp", L"Ending_Background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending/Ending.bmp", L"Ending_Photo");

}

int CEndingLogo::Update(void)
{
	if (m_dwDrawTime + 100 < GetTickCount())
	{
		++m_DrawEffectID;
		if (m_DrawEffectID == 4)
			m_DrawEffectID = 0;

		m_dwDrawTime = GetTickCount();
	}

	if (m_dwButtonTime + 500 < GetTickCount())
	{
		++m_DrawUIID;
		if (m_DrawUIID == 2)
			m_DrawUIID = 0;

		m_dwButtonTime = GetTickCount();
	}

	return 0;
}

void CEndingLogo::Late_Update(void)
{

	if (m_dwPhotoTime + 1000 < GetTickCount())
	{
		++m_DrawPhotoID;

		if (m_DrawPhotoID > 7)
			m_DrawPhotoID = 0;

		m_dwPhotoTime = GetTickCount();
	}
}

void CEndingLogo::Render(HDC hDC)
{
	HDC hBackGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending_Background");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackGroundMemDC, 0, 0, SRCCOPY);

	HDC hSwordMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Sword");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		50,	// 2,3 ���� :  ������� ��ġ X, Y
		180,
		175,				// 4,5 ���� : ������� ����, ���� ����
		100,
		hSwordMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		(98 + 3) * m_DrawUIID,
		191,				// ������ ��Ʈ���� ����, ���� ����
		98,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����

	HDC hTitleMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Title");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		150,	// 2,3 ���� :  ������� ��ġ X, Y
		200,
		250,				// 4,5 ���� : ������� ����, ���� ����
		150,
		hTitleMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		167,				// ������ ��Ʈ���� ����, ���� ����
		88,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����

	HDC hLogoMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOGO_Nintendo");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		250,	// 2,3 ���� :  ������� ��ġ X, Y
		550,
		300,				// 4,5 ���� : ������� ����, ���� ����
		30,
		hLogoMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		133,				// ������ ��Ʈ���� ����, ���� ����
		16,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����

	HDC hPhotoDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending_Photo");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		450,	// 2,3 ���� :  ������� ��ġ X, Y
		100,
		240,				// 4,5 ���� : ������� ����, ���� ����
		320,
		hPhotoDC,							// ��Ʈ���� ������ �ִ� DC
		120 * m_DrawPhotoID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		120,				// ������ ��Ʈ���� ����, ���� ����
		160,
		RGB(112, 216, 248));			// �����ϰ��� �ϴ� ����
}

void CEndingLogo::Release(void)
{
}
