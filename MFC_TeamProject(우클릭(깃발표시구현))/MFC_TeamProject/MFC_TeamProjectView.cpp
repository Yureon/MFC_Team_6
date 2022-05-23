﻿
// MFC_TeamProjectView.cpp: CMFCTeamProjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_TeamProject.h"
#endif
#include <String>

#include "MFC_TeamProjectDoc.h"
#include "MFC_TeamProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTeamProjectView

IMPLEMENT_DYNCREATE(CMFCTeamProjectView, CView)

BEGIN_MESSAGE_MAP(CMFCTeamProjectView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DIFFICULTY_EASY, &CMFCTeamProjectView::OnDifficultyEasy)
	ON_COMMAND(ID_DIFFICULTY_MIDDLE, &CMFCTeamProjectView::OnDifficultyMiddle)
	ON_COMMAND(ID_DIFFICULTY_HARD, &CMFCTeamProjectView::OnDifficultyHard)
	ON_COMMAND(ID_DIFFICULTY_CHALLENGE, &CMFCTeamProjectView::OnDifficultyChallenge)
END_MESSAGE_MAP()

// CMFCTeamProjectView 생성/소멸

CMFCTeamProjectView::CMFCTeamProjectView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	bd.Difficulty(1);
	bd.Reset();
	bd.timer = 0;
	
}

CMFCTeamProjectView::~CMFCTeamProjectView()
{
}

BOOL CMFCTeamProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCTeamProjectView 그리기

void CMFCTeamProjectView::OnDraw(CDC* pDC)
{
	CMFCTeamProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	DrawReset_Button(pDC);
	DrawBox(pDC);
}


// CMFCTeamProjectView 인쇄

BOOL CMFCTeamProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCTeamProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCTeamProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCTeamProjectView 진단

#ifdef _DEBUG
void CMFCTeamProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTeamProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTeamProjectDoc* CMFCTeamProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTeamProjectDoc)));
	return (CMFCTeamProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTeamProjectView 메시지 처리기


void CMFCTeamProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	IsLbtnClicked = true;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCTeamProjectView::OnDifficultyEasy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(1);
	bd.Reset();
	Invalidate();
}


void CMFCTeamProjectView::OnDifficultyMiddle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(2);
	bd.Reset();
	Invalidate();
}


void CMFCTeamProjectView::OnDifficultyHard()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(3);
	bd.Reset();
	Invalidate();
}


void CMFCTeamProjectView::OnDifficultyChallenge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(4);
	bd.Reset();
	Invalidate();
}


void CMFCTeamProjectView::DrawReset_Button(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	CRect Textbox_Reset(230, 30, 280, 50);
	CRect Textbox_Timer(80, 60, 180, 80);
	CRect Textbox_Score(330, 60, 430, 80);
	CRect Windowbox(0, 0, 550, 600);
	CString Reset("초기화");
	CString Timer("시간: ");
	CString Score("점수:");

	pDC->Rectangle(Windowbox);
	pDC->Rectangle(Textbox_Reset);
	pDC->DrawText(Reset, Textbox_Reset, DT_CENTER && DT_VCENTER);
	
	pDC->DrawText(Timer, Textbox_Timer, DT_CENTER && DT_VCENTER);

	pDC->DrawText(Score, Textbox_Score, DT_CENTER && DT_VCENTER);

}


void CMFCTeamProjectView::DrawBox(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 1; i < bd.boxCount; i++) {
		for (int j = 1; j < bd.boxCount; j++) {
			bd.m_board[i][j] = CRect(i * bd.boxSize+42, j * bd.boxSize+102, (i + 1) * bd.boxSize+41, (j + 1) * bd.boxSize+101);
			pDC->Rectangle(bd.m_board[i][j]);
		}
	}
}




void CMFCTeamProjectView::Flag(int x, int y)
{
	//좌버튼이 눌려져있을 경우에 주변 열기 동작 실행
	if (IsLbtnClicked) {
		OpenSurround(x, y); //주변 열기 함수
	}
	else {
		//브럭이 아직 기본상태이며 깃발을 전부 쓰지 않았을 경우
		if (bd.check[x][y] == 0 && m_nMine != 0) {
			bd.check[x][y]=2;
			m_nMine--; //지뢰 개수의 변수가 m_nmine 깃발을 설치햇으므로 갯수--
			UpdateData(false);

			CClientDC dc(this);
			CPen BlackPen(PS_SOLID, 1, RGB(0, 0, 0));
			CPen *oldPen = dc.SelectObject(&BlackPen);
			CBrush BlueBrush(RGB(0, 0, 255));
			CBrush *oldBrush = dc.SelectObject(&BlueBrush);
			dc.Rectangle(10 + 20 * x, 10 + 20 * y, 30 + 20 * x, 30 + 20 * y);
			dc.SelectObject(oldPen);
			dc.SelectObject(oldBrush);
			//깃발 표시를 위한 그래픽 bitmap1.bmp로 만들어 두었습니다
		}	//이미 깃발이 표시 되어 있을 경우
		else if (bd.check[x][y]==2&&m_nMine != 10) {
			bd.check[x][y] = 0;
			m_nMine++;    //깃발이 제거가 되므로 지뢰 갯수++
			UpdateData(false);

			CClientDC dc(this);
			CPen BlackPen((PS_SOLID), 1, RGB(0, 0, 0));
			CPen *oldPen = dc.SelectObject(&BlackPen);
			CBrush BlueBrush(RGB(128, 207, 255));
			CBrush *oldBrush = dc.SelectObject(&BlueBrush);
			dc.Rectangle(10 + 20 * x, 10 + 20 * y, 30 + 20 * x, 30 + 20 * y);
			dc.SelectObject(oldPen);
			dc.SelectObject(oldBrush);
		}
	}
	Invalidate();
}

void CMFCTeamProjectView::OpenSurround(int x, int y)  //주변열기 함수
{
	// TODO: 여기에 구현 코드 추가.
}
