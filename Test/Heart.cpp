#include "stdafx.h"
#include "Heart.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CHeart::CHeart() : m_bGet_Effect(false), m_dwTime(GetTickCount()), m_bCount(false)
{
}


CHeart::~CHeart()
{
}

void CHeart::Initialize(void)
{
	m_eItemType = ITEM_HEART;
	m_tInfo.fCX = 22;
	m_tInfo.fCY = 20;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Heart.bmp", L"Heart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/TextBar_GetHeart.bmp", L"TextBar_GetHeart");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameSpeed = 100;
	m_pFrameKey = L"Heart";
}

int CHeart::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Effect)
		Get_Effect();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CHeart::Late_Update(void)
{
	if (CCollisionMgr::Collsion_Rect(CObjMgr::Get_Instance()->Get_Player_List(), this))
		m_bGet_Effect = true;
}

void CHeart::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	m_eGroup = RENDER_PLAYERUPOBJECT;

	HDC hItemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hItemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		8,				// ������ ��Ʈ���� ����, ���� ����
		7,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����


	if (m_bCount)
	{
		HDC hTextDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBar_GetHeart");

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

void CHeart::Release(void)
{
}

void CHeart::Get_Effect(void)
{
	if (!m_bCount)
	{
		m_dwTime = GetTickCount();
		m_bCount = true;
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::EFFECT);
		m_tInfo.fY -= 15;
	}

	if (m_dwTime + 3000 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"Coin.wav", ITEM_EFFECT, g_fSound);
		m_bDead = true;
		
		CObjMgr::Get_Instance()->Get_Player()->Set_MaxHp();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(CPlayer::IDLE);
	}
}
