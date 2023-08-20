
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication13.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_COMMAND(ID_RECT, &CChildView::OnRect)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CChildView::OnUpdateRect)
	ON_COMMAND(ID_CIRCLE, &CChildView::OnCircle)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, &CChildView::OnUpdateCircle)
	ON_COMMAND(ID_ERR, &CChildView::OnErr)
	ON_UPDATE_COMMAND_UI(ID_ERR, &CChildView::OnUpdateErr)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	GetClientRect(rect);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);

	CBrush R(RGB(255, 0, 0));
	CBrush G(RGB(0, 255, 0));
	CBrush B(RGB(0, 0, 255));
	CBrush Black(RGB(0, 0, 0));



	memDC.Rectangle(0, 0, rect.Width(), rect.Height());



	if(DrawReady2 == true)
	{
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		memDC.SelectObject(&pen);

		memDC.Rectangle(ErRect.Pos_S.x, ErRect.Pos_S.y,
						ErRect.Pos_E.x, ErRect.Pos_E.y);
	}

	CPen pen1(PS_NULL, 1, RGB(0, 0, 255));
	memDC.SelectObject(&pen1);

	POSITION pos = MousePaint.GetHeadPosition();

	while(pos != NULL)
	{
		Paint value = MousePaint.GetNext(pos);
		if(DrawReady == true)
		{
			switch(value.ColorType)
			{
			case 0:
				memDC.SelectObject(&R);
				break;
			case 1:
				memDC.SelectObject(&G);
				break;
			case 2:
				memDC.SelectObject(&B);
				break;
			case 3:
				memDC.SelectObject(&Black);
				break;
			default:
				break;
			}


			if(value.RectType == true)
			{
				memDC.Rectangle(value.Pos_S.x, value.Pos_S.y,
								value.Pos_S.x+10, value.Pos_S.y+10);
			}
			else
			{
				memDC.Ellipse(value.Pos_S.x, value.Pos_S.y,
								value.Pos_S.x + 10, value.Pos_S.y + 10);
			}

		}
	}


	memDC.SetTextAlign(TA_CENTER);
	CString mew;
	PaintNum = MousePaint.GetSize();
	mew.Format(_T("점의 숫자 : %d"), PaintNum);
	memDC.TextOut(100, 100, mew);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	DrawReady = true;
	L_Down = true;

	MousePaint.AddTail({ point, PutColor, PutRect});

	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	L_Down = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	DrawReady2 = true;
	R_Down = true;
	//ErmoveReady = false;
	X_P = 0;
	Y_P = 0;
	ErRect.Pos_S = point;
	ErRect.Pos_E = point;

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	ErRect.Pos_E = point;
	//ErmoveReady = true;
	R_Down = false;

	CWnd::OnRButtonUp(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	SetTimer(0, 1, NULL);

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

#define S_X ErRect.Pos_S.x
#define S_Y ErRect.Pos_S.y

#define E_X ErRect.Pos_E.x
#define E_Y ErRect.Pos_E.y

	if(nIDEvent == 0)
	{
		if(S_X < E_X)// 위에서 아래로 그린 경우
		{
			DDraw = true;
		}
		else// 아래에서 위로 그린 경우
		{
			DDraw = false;
		}

		if(S_Y < E_Y)// 왼쪽에서 오른쪽으로 그린 경우
		{
			RDraw = true;
		}
		else//오른쪽에서 왼쪽으로 그린 경우
		{
			RDraw = false;
		}

		POSITION old;
		POSITION pos2 = MousePaint.GetHeadPosition();
		while(pos2 != NULL)
		{
			old = pos2;
			Paint value2 = MousePaint.GetNext(pos2);
#define V value2.Pos_S
			if(DrawReady == true)
			{
				if(RDraw == true && DDraw == true)//좌상 우하
				{
					if(V.x > S_X && V.x < E_X &&//시작 X보다 더 오른쪽에 있는 X를 가졌고 끝 X보다 더 왼쪽에 있는X를 가짐
					   V.y > S_Y && V.y < E_Y ||
					   V.x+10 > S_X && V.x+10 < E_X &&
					   V.y+10 > S_Y && V.y+10 < E_Y)
					{
						MousePaint.RemoveAt(old);
					}
				}

				if(RDraw == false && DDraw == true)//좌하 우상
				{
					if(V.x > S_X && V.x < E_X &&
					   V.y > E_Y && V.y < S_Y ||
					   V.x + 10 > S_X && V.x + 10 < E_X &&
					   V.y + 10 > E_Y && V.y + 10 < S_Y)
					{
						MousePaint.RemoveAt(old);
					}
				}

				if(RDraw == true && DDraw == false)//우상 좌하
				{
					if(V.x > E_X && V.x < S_X &&
					   V.y > S_Y && V.y < E_Y ||
					   V.x + 10 > E_X && V.x + 10 < S_X &&
					   V.y + 10 > S_Y && V.y + 10 < E_Y)
					{
						MousePaint.RemoveAt(old);
					}
				}

				if(RDraw == false && DDraw == false)//우하 좌상
				{
					if(V.x > E_X && V.x < S_X &&
					   V.y > E_Y && V.y < S_Y ||
					   V.x + 10 > E_X && V.x + 10 < S_X &&
					   V.y + 10 > E_Y && V.y + 10 < S_Y)
					{
						MousePaint.RemoveAt(old);
					}
				}
			}
		}


		if(ErmoveReady == true)
		{
			if(S_X < 0 || E_X > rect.Width() ||
			   E_X < 0 || S_X > rect.Width())
			{
				X_P *= -1;
			}

			if(S_Y < 0 || E_Y > rect.Height() ||
			   E_Y < 0 || S_Y > rect.Height())
			{
				Y_P *= -1;
			}


			S_X += X_P;
			E_X += X_P;



			S_Y += Y_P;
			E_Y += Y_P;


		}

		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(L_Down == true)
	{
		PaintNum++;
		MousePaint.AddTail({ point, PutColor, PutRect});
	}

	if(R_Down == true)
	{
		ErRect.Pos_E = point;
	}


	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;// CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch(nChar)
	{
	case VK_LEFT:
		X_P = -5;
		Y_P = 0;
		break;
	case VK_RIGHT:
		X_P = 5;
		Y_P = 0;
		break;
	case VK_UP:
		Y_P = -5;
		X_P = 0;
		break;
	case VK_DOWN:
		Y_P = 5;
		X_P = 0;
		break;
	default:
		break;
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PutColor = 0;
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->SetCheck(PutColor == 0);
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PutColor = 1;
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->SetCheck(PutColor == 1);
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PutColor = 2;
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->SetCheck(PutColor == 2);
}


void CChildView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PutColor = 3;
}


void CChildView::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->SetCheck(PutColor == 3);
}


void CChildView::OnRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PutRect = true;
}


void CChildView::OnUpdateRect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(PutRect == true);
}


void CChildView::OnCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	PutRect = false;
}


void CChildView::OnUpdateCircle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(PutRect == false);
}


void CChildView::OnErr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	X_P = 0;
	Y_P = 0;

	if(ErmoveReady == false)
	{
		ErmoveReady = true;
	}
	else
	{
		ErmoveReady = false;
	}
}


void CChildView::OnUpdateErr(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(ErmoveReady == true);
}
