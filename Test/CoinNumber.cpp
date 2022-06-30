#include "stdafx.h"
#include "CoinNumber.h"
#include "BmpMgr.h"


CCoinNumber::CCoinNumber()
{
}


CCoinNumber::~CCoinNumber()
{
	Release();
}

void CCoinNumber::Initialize(void)
{
	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HUD/Number.bmp", L"Number");
}

int CCoinNumber::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoinNumber::Late_Update(void)
{
	if (m_DrawID > 4)
	{
		m_Option = 1;
		m_DrawID -= 5;
	}
	else
	{
		m_Option = 0;
	}
}

void CCoinNumber::Render(HDC hDC)
{
	HDC	hHpDC = CBmpMgr::Get_Instance()->Find_Image(L"Number");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hHpDC,							// ��Ʈ���� ������ �ִ� DC
		(8) * m_DrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		(8) * m_Option,
		7,				// ������ ��Ʈ���� ����, ���� ����
		7,
		RGB(244, 0, 244));			// �����ϰ��� �ϴ� ����
}

void CCoinNumber::Release(void)
{
}
