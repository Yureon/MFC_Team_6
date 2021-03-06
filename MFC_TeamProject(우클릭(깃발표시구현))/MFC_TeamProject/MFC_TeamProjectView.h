
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
	Board bd;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDifficultyEasy();
	afx_msg void OnDifficultyMiddle();
	afx_msg void OnDifficultyHard();
	afx_msg void OnDifficultyChallenge();
	void DrawReset_Button(CDC* pDC);
	void DrawBox(CDC* pDC);
	void Flag(CDC *pc);
	bool IsLbtnClicked;
	bool IsRbtnClicked;
	void OpenSurround(int x, int y);
	int m_nflag;
	int m_nmine;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	bool DrawFromFile(CDC* pDC, int destX, int destY, int destWidth, int destHeight, LPCWSTR filePath, int srcX, int srcY);
	void DrawButton(CDC* pDC);
	bool Game_status;
	CRect Windowbox;
	void DrawNumber(CDC* pDC);
	CString str;
};

#ifndef _DEBUG  // MFC_TeamProjectView.cpp의 디버그 버전
inline CMFCTeamProjectDoc* CMFCTeamProjectView::GetDocument() const
   { return reinterpret_cast<CMFCTeamProjectDoc*>(m_pDocument); }
#endif

