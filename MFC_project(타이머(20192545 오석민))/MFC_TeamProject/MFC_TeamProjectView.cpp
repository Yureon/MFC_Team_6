
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

#define USER_TIMER 1000
#include <time.h>




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
	bd.Difficulty(3);
	bd.Reset();
	bd.timer = 0;
	Windowbox = CRect(0, 0, 550, 600);
	Game_status = true;
	
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
	if (Game_status) {
		DrawBox(pDC);
		DrawNumber(pDC);
		
	}
	else {
		CRect Fail(300, 300, 500, 500);
		pDC->DrawTextW(L"지뢰를 밟았다!", Fail, DT_VCENTER && DT_CENTER);
	}
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

	if (Game_status) {
		if (Windowbox.PtInRect(point)) {
			for (int i = 0; i < bd.boxCount; i++) {
				for (int j = 0; j < bd.boxCount; j++) {
					if (bd.m_board[i][j].PtInRect(point)) {
						bd.chas_x = i;
						bd.chas_y = j;
					} //선택된 상자의 위치를 추적함.
				}
			}

			bd.check[bd.chas_x][bd.chas_y] = 1; //상자가 선택되었음을 배열에 표시함

			if (bd.check[bd.chas_x][bd.chas_y] == 1 && bd.mine[bd.chas_x][bd.chas_y] < 0) {
				Game_status = false;
			}//선택된 상자에 지뢰가 있는 경우
			else if (bd.check[bd.chas_x][bd.chas_y] == 1 && bd.mine[bd.chas_x][bd.chas_y] > 0) {
				Game_status = true;
			}//선택된 상자에 지뢰가 없는 경우

			Invalidate();
		}
	}
	

	CView::OnLButtonDown(nFlags, point);
}


void CMFCTeamProjectView::OnDifficultyEasy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(1);
	bd.Reset();
	Game_status = true;
	Invalidate();
}


void CMFCTeamProjectView::OnDifficultyMiddle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(2);
	bd.Reset();
	Game_status = true;
	Invalidate();
}


void CMFCTeamProjectView::OnDifficultyHard()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(3);
	bd.Reset();
	Game_status = true;
	Invalidate();
}


void CMFCTeamProjectView::OnDifficultyChallenge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	bd.Difficulty(4);
	bd.Reset();
	Game_status = true;
	Invalidate();
}


void CMFCTeamProjectView::DrawButton(CDC* pDC)
{
	// 초기화,시간,점수를 그리기 위한 메소드

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
	// Ondraw에 박스를 그리기 위한 메소드

	for (int i = 1; i < bd.boxCount; i++) {
		for (int j = 1; j < bd.boxCount; j++) {
			bd.m_board[i][j] = CRect(i * bd.boxSize+41, j * bd.boxSize+101, (i + 1) * bd.boxSize+40, (j + 1) * bd.boxSize+100);
			pDC->Rectangle(bd.m_board[i][j]);
		}
	}
}


void CMFCTeamProjectView::OnTimer(UINT_PTR nIDEvent)
{
	int a = 0;





#define USER_TIMER 1000

	SetTimer(USER_TIMER, 1000 / 9, NULL); // 1초에 9번 호출

	switch (nIDEvent)
	{
	case USER_TIMER:
		a = a + 1;    // 1초에 9씩 증가하는 예제        
		break;
	default:
		break;
	}


	BOOL KillTimer(
		UINT_PTR nIDEvent
	);


}





void CMFCTeamProjectView::DrawFlag(CDC* pDC)
{
	// Ondraw에 삽입할 메소드로 깃발을 그리기 위한 메소드
	
	
}

void CMFCTeamProjectView::DrawNumber(CDC* pDC)
{
	// Ondraw에 삽입할 메소드로 박스를 누를경우 주위 박스에 숫자를 표기할 메소드
	CBrush BoxBrush,*pOldBrush;
	BoxBrush.CreateSolidBrush(RGB(180, 180, 180));
	pOldBrush = pDC->SelectObject(&BoxBrush);

	for (int i = 1; i < bd.boxCount; i++) {
		for (int j = 1; j < bd.boxCount; j++) {
			if (bd.check[i][j] == 1) {   //사용자가 해당 박스를 눌렀는지 확인
				for (int m = -1; m <= 1; m++) {
					for (int n = -1; n <= 1; n++) {
						if (bd.mine[i + m][j + n] >= 0) {
							str.Format(_T("%d"), bd.mine[i + m][j + n]);
							
							pDC->DrawTextW(str, bd.m_board[i + m][j + n], DT_CENTER && DT_VCENTER);

						}
					}
				}
			}
		}
	}
	pDC->SelectObject(pOldBrush);
}

