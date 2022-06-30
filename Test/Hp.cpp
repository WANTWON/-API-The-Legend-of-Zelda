#include "stdafx.h"
#include "Hp.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CHp::CHp() : m_DrawID(0), m_Option(0)
{
}


CHp::~CHp()
{
}

void CHp::Initialize(void)
{
	m_tInfo.fCX = 30;
	m_tInfo.fCY = 30;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/HUD/LinkHp.bmp", L"LinkHp");
}

int CHp::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CHp::Late_Update(void)
{
	

}

void CHp::Render(HDC hDC)
{
	HDC	hHpDC = CBmpMgr::Get_Instance()->Find_Image(L"LinkHp");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left ),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hHpDC,							// ��Ʈ���� ������ �ִ� DC
		(30) * m_DrawID,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		30,				// ������ ��Ʈ���� ����, ���� ����
		30,
		RGB(255, 0, 255));			// �����ϰ��� �ϴ� ����
}

void CHp::Release(void)
{
}
