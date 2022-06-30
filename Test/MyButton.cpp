#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 130.f;
	m_tInfo.fCY = 60.f;
	m_eGroup = RENDER_GAMEOBJECT;
}

int CMyButton::Update(void)
{

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	
	POINT		Pt;
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&m_tRect, Pt))
	{
		

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Menu_Button.wav", SOUND_EFFECT, g_fSound - 0.3f);
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_FIELD);

			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT, SC_MINIWORLD);
			else if (!lstrcmp(L"Quit", m_pFrameKey))
				DestroyWindow(g_hWnd);
			else if (!lstrcmp(L"Back", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

			return;
		}

		m_iDrawID = 1;
	}
	else
	{
		
		m_iDrawID = 0;
	}
		




}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),			// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_iDrawID * (21 + 4),
		56,				// ������ ��Ʈ���� ����, ���� ����
		25,
		RGB(244, 0, 244));			// �����ϰ��� �ϴ� ����


}

void CMyButton::Release(void)
{

}
