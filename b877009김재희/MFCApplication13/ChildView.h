
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "Shape.h"
#include "Eraser.h"
#include "Paint.h"


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

// 작업입니다.
public:

	bool DrawReady = false;
	bool DrawReady2 = false;

	bool R_Down = false;
	bool L_Down = false;

	int PaintNum = 0;
	CList <Paint> MousePaint;

	int PutColor = 0;
	bool PutRect = true;

	Eraser ErRect;
	int X_P = 0;
	int Y_P = 0;

	// 그린방향
	bool RDraw = true;
	bool DDraw = true;

	bool ErmoveReady = false;

	CRect rect;



// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnRect();
	afx_msg void OnUpdateRect(CCmdUI *pCmdUI);
	afx_msg void OnCircle();
	afx_msg void OnUpdateCircle(CCmdUI *pCmdUI);
	afx_msg void OnErr();
	afx_msg void OnUpdateErr(CCmdUI *pCmdUI);
};

