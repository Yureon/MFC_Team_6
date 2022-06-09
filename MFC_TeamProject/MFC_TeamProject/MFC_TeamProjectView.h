
// MFC_TeamProjectView.h: CMFCTeamProjectView 클래스의 인터페이스
//

#pragma once
#include "Board.h"
#include <atlstr.h>

class CMFCTeamProjectView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCTeamProjectView() noexcept;
	DECLARE_DYNCREATE(CMFCTeamProjectView)

// 특성입니다.
public:
	CMFCTeamProjectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCTeamProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	Board bd;// 상자들의 좌표,상자에 지뢰를 넣는 메소드,지뢰 주위에 상자 계산하는 메소드들이 있는 해시파일

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	//마우스 좌클
	afx_msg void OnDifficultyEasy();	//난이도
	afx_msg void OnDifficultyMiddle();	//난이도
	afx_msg void OnDifficultyHard();	//난이도
	afx_msg void OnDifficultyChallenge();	//난이도
	int difficulty;
	
	
	bool Game_status; // 게임이 진행중인지,정지된 건지 확인하기 위한 변수 ( True - 진행중 / False - 승리 or 패배 )
	void DrawNumber(CDC* pDC); // Ondraw에서 상자에 숫자를 넣기 위한 메소드
	CString str; // 박스에 숫자 채워 넣을 때 int -> CString 변환을 위한 버퍼
	
				 
				 /*레이아웃을 위한 변수들*/
	void DrawButton(CDC* pDC); // 초기화 버튼,점수,시간을 그리기 위한 메소드
	void DrawBox(CDC* pDC); // 박스 상자를 그리기 위한 메소드
	CRect Windowbox; //배경으로 쓸 박스
	CRect Textbox_Reset;
	CRect Textbox_Timer;
	CRect Textbox_Score;
	CRect Textbox_Flag;
	CString Reset;
	CString Timer;
	CString Score;
	CString Flag;
	int m_flag;
	int m_timer;
	int m_score;
	bool time_run;
	
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawFlag(CDC* pDC);
	bool DrawFromFile(CDC* pDC, int destX, int destY, int destWidth, int destHeight, LPCWSTR filePath, int srcX, int srcY);
	
	
	
	CString MenuText(CString str, int val, char c);
	void F_Reset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFC_TeamProjectView.cpp의 디버그 버전
inline CMFCTeamProjectDoc* CMFCTeamProjectView::GetDocument() const
   { return reinterpret_cast<CMFCTeamProjectDoc*>(m_pDocument); }
#endif

