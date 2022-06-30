#include "stdafx.h"
#include "RockPaperScissor.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CRockPaperScissor::CRockPaperScissor() : m_iOption(0), m_iDrawID(0)
{
}


CRockPaperScissor::~CRockPaperScissor()
{
	Release();
}

void CRockPaperScissor::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Rock.bmp", L"Rock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Paper.bmp", L"Paper");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/Scissor.bmp", L"Scissor");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/PCRock.bmp", L"PCRock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/PCPaper.bmp", L"PCPaper");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mini/PCScissor.bmp", L"PCScissor");

	m_tInfo.fCX = 200;
	m_tInfo.fCY = 200;

	m_iOption = rand() % 3;
}

int CRockPaperScissor::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CRockPaperScissor::Late_Update(void)
{

	if (m_bPC)
	{
		if (m_iOption == 0)
			m_pFrameKey = L"PCRock";
		else if (m_iOption == 2)
			m_pFrameKey = L"PCScissor";
		else if (m_iOption == 1)
			m_pFrameKey = L"PCPaper";
	}
	else
	{

		if (m_iOption == 0)
			m_pFrameKey = L"Rock";
		else if (m_iOption == 2)
			m_pFrameKey = L"Scissor";
		else if (m_iOption == 1)
			m_pFrameKey = L"Paper";
	}
}

void CRockPaperScissor::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart ,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		100,				// ������ ��Ʈ���� ����, ���� ����
		100,
		RGB(128, 128, 128));			// �����ϰ��� �ϴ� ����
}

void CRockPaperScissor::Release(void)
{
}
