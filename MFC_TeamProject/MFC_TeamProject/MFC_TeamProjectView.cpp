
// MFC_TeamProjectView.cpp: CMFCTeamProjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_TeamProject.h"
#endif

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
	Windowbox = CRect(0, 0, 550, 600);
	
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
	
	DrawButton(pDC);
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

	if (Windowbox.PtInRect(point)) {
		for (int i = 0; i < bd.boxCount; i++) {
			for (int j = 0; j < bd.boxCount; j++) {
				if (bd.m_board[i][j].PtInRect(point)) {
					bd.chas_x = i;
					bd.chas_y = j;
				}
			}
		}

		bd.check[bd.chas_x][bd.chas_y] = 1;

		if (bd.check[bd.chas_x][bd.chas_y] == 1 && bd.mine[bd.chas_x][bd.chas_y] < 0) {

		}
	}

	

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


void CMFCTeamProjectView::DrawButton(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.
	CRect Textbox_Reset(230, 30, 280, 50);
	CRect Textbox_Timer(80, 60, 180, 80);
	CRect Textbox_Score(330, 60, 430, 80);

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
