#include "stdafx.h"
#include "ShieldBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CShieldBullet::CShieldBullet() : m_bCount(false)
{
}


CShieldBullet::~CShieldBullet()
{
	Release();
}

void CShieldBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/ShieldBullet.bmp", L"ShieldBullet");
	m_pFrameKey = L"ShieldBullet";

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_eGroup = RENDER_EFFECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;

	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CShieldBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	
	if (!m_bCount)
	{
		CSoundMgr::Get_Instance()->StopSound(BUllET_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"ShieldSound.wav", BUllET_EFFECT, g_fSound + 0.5f);
		m_bCount = true;
	}
		



	Update_Rect();

	return OBJ_NOEVENT;
}

void CShieldBullet::Late_Update(void)
{
}

void CShieldBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX) ,	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY) ,
		int(m_tInfo.fCX) ,				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY) ,
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		126,				// ������ ��Ʈ���� ����, ���� ����
		126,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CShieldBullet::Release(void)
{
}
