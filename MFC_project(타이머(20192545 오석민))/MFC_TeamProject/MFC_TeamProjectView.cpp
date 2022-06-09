
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
#include <time.h>

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
//	ON_WM_RBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_CREATE()
ON_WM_TIMER()
ON_WM_DESTROY()
END_MESSAGE_MAP()



// CMFCTeamProjectView 생성/소멸

CMFCTeamProjectView::CMFCTeamProjectView() noexcept
{	
		m_timerRun= 0;
		m_timeType = 0;
	
		// TODO: 여기에 생성 코드를 추가합니다.
		bd.Difficulty(3);
		bd.Reset();
		bd.timer = 0;
		bd.chas_x = 0;
		bd.chas_y = 0;
		m_flag = bd.m_flag;
		Windowbox = CRect(0, 0, 550, 600);
		Game_status = true;

		Textbox_Reset = CRect(230, 30, 280, 50);
		Textbox_Timer = CRect(80, 60, 180, 80);
		Textbox_Score = CRect(330, 60, 430, 80);
		Textbox_Flag = CRect(180, 90, 320, 130);
		Reset.Append(L"초기화");
		Timer.Append(L"시간: ");
		Score.Append(L"점수:");
		Flag.Append(L"깃발 개수:");



	


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
		DrawFlag(pDC);
	}
	else {
		CRect Fail(200, 200, 500, 500);
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

	if (Game_status) { // 이전에 지뢰를 클릭하지 않았을 때
		if (Windowbox.PtInRect(point)) { // 포인터가 Windowbox 범위 내부를 클릭하였을 때 (추적 함수를 for로 돌리기 때문에 불필요한 연산을 줄이기 위해서)
			for (int i = 0; i < bd.boxCount; i++) { 
				for (int j = 0; j < bd.boxCount; j++) {
					if (bd.m_board[i][j].PtInRect(point)) {// 해당 상자의 위치를 for문으로 전부 추적함.
						bd.chas_x = i;
						bd.chas_y = j;
					} //선택된 상자의 위치를 추적함.
				}
			}
			if (bd.chas_x >= 0 && bd.chas_x <= 36 && bd.chas_y >= 0 && bd.chas_y <= 36) {
				if(bd.check[bd.chas_x][bd.chas_y] == 0)
				bd.check[bd.chas_x][bd.chas_y] = 1; //상자가 선택되었음을 배열에 표시함

			if (bd.check[bd.chas_x][bd.chas_y] == 1 && bd.mine[bd.chas_x][bd.chas_y] < 0) {
				Game_status = false;
			}//선택된 상자에 지뢰가 있는 경우 false로 변경, ondraw에서 상자를 안그림
			else if (bd.check[bd.chas_x][bd.chas_y] == 1 && bd.mine[bd.chas_x][bd.chas_y] > 0) {
				Game_status = true;
			}//선택된 상자에 지뢰가 없는 경우,ondraw에서 해당하는 메소드를 실행함.

			Invalidate();
}
		}
	}
	
	//if(Textbox_Reset.)

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

	pDC->Rectangle(Windowbox);
	pDC->Rectangle(Textbox_Reset);
	pDC->DrawText(Reset, Textbox_Reset, DT_CENTER && DT_VCENTER);
	
	pDC->DrawText(Timer, Textbox_Timer, DT_CENTER && DT_VCENTER);

	pDC->DrawText(Score, Textbox_Score, DT_CENTER && DT_VCENTER);
	
	Flag = MenuText(Flag, m_flag, 'f');
	pDC->DrawText(Flag, Textbox_Flag, DT_CENTER && DT_VCENTER);

	
	Timer = MenuText(Timer, UINT_PTR(0), 't');
	pDC->DrawText(m_strTimer, Textbox_Timer, DT_VCENTER && DT_CENTER);
}


void CMFCTeamProjectView::DrawBox(CDC* pDC)
{
	// Ondraw에 박스를 그리기 위한 메소드
	CBrush BoxBrush;
	BoxBrush.CreateSolidBrush(RGB(180, 180, 180));

	for (int i = 1; i < bd.boxCount; i++) {
		for (int j = 1; j < bd.boxCount; j++) {
			bd.m_board[i][j] = CRect(i * bd.boxSize+41, j * bd.boxSize+101, (i + 1) * bd.boxSize+40, (j + 1) * bd.boxSize+100);
			if (bd.check[i][j] == 1 || bd.check[i][j] == 9) {
				
				pDC->SelectObject(BoxBrush);
				pDC->Rectangle(bd.m_board[i][j]);

							
			}
			else if (bd.check[i][j] == 0) {

				pDC->SelectObject(GetStockObject(WHITE_BRUSH));
				pDC->Rectangle(bd.m_board[i][j]);
			}
		}
	}
}


void CMFCTeamProjectView::DrawNumber(CDC* pDC)
{
	// Ondraw에 삽입할 메소드로 박스를 누를경우 주위 박스에 숫자를 표기할 메소드
	

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
}


void CMFCTeamProjectView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (Game_status) {
		if (Windowbox.PtInRect(point)) {
			for (int i = 0; i < bd.boxCount; i++) {
				for (int j = 0; j < bd.boxCount; j++) {
					if (bd.m_board[i][j].PtInRect(point)) {
						bd.chas_x = i;
						bd.chas_y = j;
					}
				}
			}
			//유저가 클릭했을 때 클릭한 상자의 좌표를 추적함.

			if (bd.chas_x >= 0 && bd.chas_x <= 36 && bd.chas_y >= 0 && bd.chas_y <= 36) {

			if (bd.check[bd.chas_x][bd.chas_y] == 0) {
				bd.check[bd.chas_x][bd.chas_y] = 5; // 선택한 적 없는 상자에 깃발을 넣음.
				m_flag--;
			}
			else if (bd.check[bd.chas_x][bd.chas_y] == 5) {
				bd.check[bd.chas_x][bd.chas_y] = 0;	//깃발이 표시된 상자를 다시 한번 누르면 깃발을 해제함.
				m_flag++;
			}
			Invalidate();
			}		
		}
	}

	CView::OnRButtonDown(nFlags, point);
}


void CMFCTeamProjectView::DrawFlag(CDC* pDC)
{
	// TODO: 여기에 구현 코드 추가.

	CPoint board=(0,0); // 상자의 좌표를 임시로 담을 변수
	
	for (int i = 1; i < bd.boxCount; i++) {
		for (int j = 1; j < bd.boxCount; j++) {
			if (bd.check[i][j] == 5 && m_flag != 0) {   // 해당 박스의 좌표에 우클릭 한 경우
				board = bd.m_board[i][j].TopLeft(); // 박스의 좌표를 얻어오고
				DrawFromFile(pDC,board.x, board.y, 48, 48, L"./res/0.jpg", bd.boxSize, bd.boxSize); // 박스의 크기에 맞게 해당 박스의 좌표에 삽입한다.
			}
			else if (bd.check[i][j] == 5 && m_flag == 0) {
				bd.check[bd.chas_x][bd.chas_y] = 0;
				CRect done(180, 90, 320, 130);
				pDC->DrawTextW(L"깃발이 없습니다", done, DT_VCENTER && DT_CENTER);
				board = bd.m_board[i][j].TopLeft(); // 박스의 좌표를 얻어오고
				DrawFromFile(pDC, board.x, board.y, 48, 48, L"./res/0.jpg", bd.boxSize, bd.boxSize); // 박스의 크기에 맞게 해당 박스의 좌표에 삽입한다.
				m_flag++;
			}
		}
	}
}


bool CMFCTeamProjectView::DrawFromFile(CDC* pDC, int destX, int destY, int destWidth, int destHeight, LPCWSTR filePath, int srcX, int srcY)
{
	CImage image;
	if (FAILED(image.Load(filePath)))
	{
		return FALSE;
	}
	image.Draw(pDC->m_hDC, destX, destY,srcX,srcY);
	image.Detach();
	return TRUE;
}

CString CMFCTeamProjectView::MenuText(CString str,int val,char c) {

	CString buffer;
	str.Empty();

	switch (c) {
	case 's':
		str.Append(L"점수: ");
		break;
	case 't':
		str.Append(L"시간: ");
		break;
	case 'f':
		str.Append(L"깃발 개수: ");
		break;
	}

	buffer.Format(_T("%d"), val);
	str.Append(buffer);

	return str;


}

int CMFCTeamProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;


	m_Time = SetTimer(0, 1000, NULL);  // 타이머 설정
	m_timerRun = TRUE;    // 타이머 동작

	return 0;
}


void CMFCTeamProjectView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int hour;
	CString str;
	CTime timer;
	timer = CTime::GetTickCount(); // Visual Studio 2017부터 GetCurrentTime() 삭제


	if (m_timeType) {
		m_strTimer.Format(_T("%d초"), timer.GetSecond());


	}

		m_strTimer.Format(_T(" %d"), timer.GetSecond());

	


	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CMFCTeamProjectView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
