#include "PCH.h"
#include "Overlay.h"

#include "Project5.h"


COverlay::COverlay(void)
	: m_LastOverlayPosition(0, 0)
{
	m_nDispIndex = 0;
	m_dZoom = 1;
	m_rcZoomRoi = CRect(0, 0, DISP_SIZE_X, DISP_SIZE_Y);
	m_ptOffset = CPoint(0, 0);
	m_ptClick = CPoint(-1, -1);
	m_szClickText[0] = 0;
	
	clBoxList.cnt = clCircleList.cnt = clCrossList.cnt = clLineList.cnt = clPixelList.cnt = clTextList.cnt = 0;

	m_MilDisplay = M_NULL;
	m_MilOverlay = M_NULL;
	m_TransColor = M_NULL;


	InitOverlayList();

	InitializeCriticalSection(&m_csOverlay);
}

COverlay::~COverlay(void)
{
	if (m_MilDisplay)
	{
		MdispFree(m_MilDisplay);
		m_MilDisplay = M_NULL;
	}
	FreeOverlayList();

	DeleteCriticalSection(&m_csOverlay);
}

void COverlay::UpdateOverlayPosition(int x, int y)
{
	// 오버레이 위치 업데이트
	m_LastOverlayPosition.x = x;
	m_LastOverlayPosition.y = y;
}

void COverlay::Init(int fi_nDisp, MIL_ID fi_MilSystem, MIL_ID fi_MilImage, CWnd* pWnd, int sx, int sy, int sizeX, int sizeY)

{
	m_nDispIndex = fi_nDisp;

	m_nDispPositionX = sx;
	m_nDispPositionY = sy;

	m_nDispSizeX = sizeX;
	m_nDispSizeY = sizeY;


	pWnd->MoveWindow(sx, sy, sizeX, sizeY);

	m_dZoom = 0.8;
	m_ptOffset = CPoint(0, 0);

	MdispAlloc(fi_MilSystem, M_DEFAULT, _T("M_DEFAULT"), M_WINDOWED, &m_MilDisplay);

	if (m_MilDisplay)
	{
		if (pWnd != NULL)
		{
			MdispSelectWindow(m_MilDisplay, fi_MilImage, pWnd->m_hWnd);
		}

		MdispControl(m_MilDisplay, M_OVERLAY_SHOW, M_ENABLE);		   //오버레이 사용가능
		MdispControl(m_MilDisplay, M_OVERLAY, M_ENABLE);
		MdispControl(m_MilDisplay, M_MOUSE_USE, M_ENABLE);			   //마우스사용가능
		MdispControl(m_MilDisplay, M_MOUSE_CURSOR_CHANGE, M_ENABLE);  //커서모양바꾸기 가능

		MdispInquire(m_MilDisplay, M_OVERLAY_ID, &m_MilOverlay);
		MdispInquire(m_MilDisplay, M_TRANSPARENT_COLOR, &m_TransColor);
		MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
	}

}


void COverlay::InitOverlayList()
{
	clPixelList.c = new	COLORREF[MAX_CNT_PIXEL];
	clPixelList.p = new	POINT[MAX_CNT_PIXEL];
}

void COverlay::FreeOverlayList()
{
	free(clPixelList.c);
	free(clPixelList.p);
}

void COverlay::Free()
{
	if (m_MilOverlay)
	{
		m_MilOverlay = M_NULL;
	}

	if (m_MilDisplay)
	{
		m_MilDisplay = M_NULL;
	}
}

void COverlay::AddTextList(int fi_iX, int fi_iY, CString fi_sText, COLORREF fi_color, int fi_iSizeX, int fi_iSizeY, bool fi_bEgdeFlag)
{
	if (clTextList.cnt < MAX_CNT_TEXT)
	{// Camera Disp
		clTextList.p[clTextList.cnt].x = fi_iX;
		clTextList.p[clTextList.cnt].y = fi_iY;
		_stprintf_s(clTextList.str[clTextList.cnt], 1000, fi_sText);
		fi_sText.ReleaseBuffer();

		clTextList.c[clTextList.cnt] = fi_color;
		clTextList.size[clTextList.cnt].x = fi_iSizeX;
		clTextList.size[clTextList.cnt].y = fi_iSizeY;

		clTextList.edgeFlag[clTextList.cnt] = fi_bEgdeFlag;
		clTextList.cnt++;
	}
}

void COverlay::AddCrossList(int fi_iX, int fi_iY, int fi_iWdt1, int fi_iWdt2, COLORREF fi_color)
{
	if (clCrossList.cnt < MAX_CNT_CROSS)
	{// Camera Disp
		clCrossList.c[clCrossList.cnt] = fi_color;
		clCrossList.p[clCrossList.cnt].x = fi_iX;
		clCrossList.p[clCrossList.cnt].y = fi_iY;
		clCrossList.w1[clCrossList.cnt] = fi_iWdt1;
		clCrossList.w2[clCrossList.cnt] = fi_iWdt2;
		clCrossList.cnt++;
	}
}

void COverlay::AddLineList(int fi_iSx, int fi_iSy, int fi_iEx, int fi_iEy, COLORREF fi_color, int fi_iStyle)
{
	if (clLineList.cnt < MAX_CNT_LINE)
	{// Camera Disp
		clLineList.c[clLineList.cnt] = fi_color;
		clLineList.p[clLineList.cnt][0].x = fi_iSx;
		clLineList.p[clLineList.cnt][0].y = fi_iSy;
		clLineList.p[clLineList.cnt][1].x = fi_iEx;
		clLineList.p[clLineList.cnt][1].y = fi_iEy;
		clLineList.style[clLineList.cnt] = fi_iStyle;
		clLineList.cnt++;
	}
}

void COverlay::AddLineList(double fi_dSx, double fi_dSy, double fi_dEx, double fi_dEy, COLORREF fi_color, int fi_iStyle)
{
	if (clLineList.cnt < MAX_CNT_LINE)
	{// Camera Disp
		clLineList.c[clLineList.cnt] = fi_color;
		clLineList.p[clLineList.cnt][0].x = (int)(fi_dSx + 0.5);
		clLineList.p[clLineList.cnt][0].y = (int)(fi_dSy + 0.5);
		clLineList.p[clLineList.cnt][1].x = (int)(fi_dEx + 0.5);
		clLineList.p[clLineList.cnt][1].y = (int)(fi_dEy + 0.5);
		clLineList.style[clLineList.cnt] = fi_iStyle;
		clLineList.cnt++;
	}
}

void COverlay::AddLineList(CDPoint ptStart, CDPoint ptEnd, COLORREF fi_color, int fi_iStyle)
{
	if (clLineList.cnt < MAX_CNT_LINE)
	{// Camera Disp
		clLineList.c[clLineList.cnt] = fi_color;
		clLineList.p[clLineList.cnt][0].x = (int)(ptStart.x + 0.5);
		clLineList.p[clLineList.cnt][0].y = (int)(ptStart.y + 0.5);
		clLineList.p[clLineList.cnt][1].x = (int)(ptEnd.x + 0.5);
		clLineList.p[clLineList.cnt][1].y = (int)(ptEnd.y + 0.5);
		clLineList.style[clLineList.cnt] = fi_iStyle;
		clLineList.cnt++;
	}
}

void COverlay::AddPixelList(int fi_iX, int fi_iY, COLORREF fi_color)
{
	if (clPixelList.cnt < MAX_CNT_PIXEL)
	{// Camera Disp
		clPixelList.c[clPixelList.cnt] = fi_color;
		clPixelList.p[clPixelList.cnt].x = fi_iX;
		clPixelList.p[clPixelList.cnt].y = fi_iY;
		clPixelList.cnt++;
	}
}

void COverlay::AddBoxList(int fi_iLeft, int fi_iTop, int fi_iRight, int fi_iBottom, COLORREF fi_color, int fi_iStyle)
{
	if (clBoxList.cnt < MAX_CNT_BOX)
	{// Camera Disp
		clBoxList.c[clBoxList.cnt] = fi_color;
		clBoxList.r[clBoxList.cnt].left = fi_iLeft;
		clBoxList.r[clBoxList.cnt].right = fi_iRight;
		clBoxList.r[clBoxList.cnt].top = fi_iTop;
		clBoxList.r[clBoxList.cnt].bottom = fi_iBottom;
		clBoxList.style[clBoxList.cnt] = fi_iStyle;
		clBoxList.cnt++;
	}
}

void COverlay::AddBoxList(RECT fi_rect, COLORREF fi_color, int fi_iStyle)
{
	if (clBoxList.cnt < MAX_CNT_BOX)
	{// Camera Disp
		clBoxList.c[clBoxList.cnt] = fi_color;
		clBoxList.r[clBoxList.cnt] = CRect(fi_rect);
		clBoxList.style[clBoxList.cnt] = fi_iStyle;
		clBoxList.cnt++;
	}
}

void COverlay::AddCircleList(int fi_iLeft, int fi_iTop, int fi_iRight, int fi_iBottom, COLORREF fi_color)
{
	if (clCircleList.cnt < MAX_CNT_CIRCLE)
	{// Camera Disp
		clCircleList.r[clCircleList.cnt].left = fi_iLeft;
		clCircleList.r[clCircleList.cnt].top = fi_iTop;
		clCircleList.r[clCircleList.cnt].right = fi_iRight;
		clCircleList.r[clCircleList.cnt].bottom = fi_iBottom;
		clCircleList.c[clCircleList.cnt] = fi_color;
		clCircleList.cnt++;
	}
}

void COverlay::OverlayDC_Box(CDC* fi_DC)
{
	fi_DC->SelectStockObject(NULL_BRUSH);

	CPen     m_pen;
	CPen* m_penOld;

	int iCnt;
	int x1, x2, y1, y2, offsetX, offsetY;

	offsetX = m_ptOffset.x;
	offsetY = m_ptOffset.y;

	for (iCnt = 0; iCnt < clBoxList.cnt; iCnt++)
	{
		m_pen.CreatePen(clBoxList.style[iCnt], 1, clBoxList.c[iCnt]);
		m_penOld = fi_DC->SelectObject(&m_pen);

		x1 = (long)((clBoxList.r[iCnt].left));
		x2 = (long)((clBoxList.r[iCnt].right));
		y1 = (long)((clBoxList.r[iCnt].top));
		y2 = (long)((clBoxList.r[iCnt].bottom));

		int newX1 = (int)(m_dZoom * (x1 - offsetX) + 0.5);
		int newY1 = (int)(m_dZoom * (y1 - offsetY) + 0.5);
		int newX2 = (int)(m_dZoom * (x2 - offsetX) + 0.5);
		int newY2 = (int)(m_dZoom * (y2 - offsetY) + 0.5);

		fi_DC->Rectangle(newX1, newY1, newX2, newY2);

		fi_DC->SelectObject(m_penOld);
		m_pen.DeleteObject();
	}
}

void COverlay::OverlayDC_Cross(CDC* fi_DC)
{
	fi_DC->SelectStockObject(NULL_BRUSH);

	CPen     m_pen;
	CPen* m_penOld;


	int iCnt;
	int x, y, w1, w2;

	int offsetX = m_ptOffset.x;
	int offsetY = m_ptOffset.y;


	for (iCnt = 0; iCnt < clCrossList.cnt; iCnt++)
	{
		m_pen.CreatePen(PS_SOLID, 1, clCrossList.c[iCnt]);
		m_penOld = fi_DC->SelectObject(&m_pen);

		w1 = (long)(clCrossList.w1[iCnt]);
		w2 = (long)(clCrossList.w2[iCnt]);
		x = (long)clCrossList.p[iCnt].x;
		y = (long)clCrossList.p[iCnt].y;

		int newX = m_dZoom * (x - offsetX + 0.5);
		int newY = m_dZoom * (y - offsetX + 0.5);

		fi_DC->MoveTo(newX - w1, newY);
		fi_DC->LineTo(newX + w1 + 1, newY);
		fi_DC->MoveTo(newX, newY - w2);
		fi_DC->LineTo(newX, newY + w2 + 1);

		fi_DC->SelectObject(m_penOld);
		m_pen.DeleteObject();
	}
}

void COverlay::OverlayDC_Circle(CDC* fi_DC)
{
	fi_DC->SelectStockObject(NULL_BRUSH);

	CPen     m_pen;
	CPen* m_penOld;


	int iCnt;
	long x1, y1, x2, y2;
	int offsetX = m_ptOffset.x;
	int offsetY = m_ptOffset.y;


	for (iCnt = 0; iCnt < clCircleList.cnt; iCnt++)
	{
		m_pen.CreatePen(PS_SOLID, 1, clCircleList.c[iCnt]);
		m_penOld = fi_DC->SelectObject(&m_pen);

		x1 = (long)((clCircleList.r[iCnt].left - offsetX) * m_dZoom + 0.5);
		y1 = (long)((clCircleList.r[iCnt].top - offsetY) * m_dZoom + 0.5);
		x2 = (long)((clCircleList.r[iCnt].right - offsetX) * m_dZoom + 0.5);
		y2 = (long)((clCircleList.r[iCnt].bottom - offsetY) * m_dZoom + 0.5);

		fi_DC->Ellipse(x1, y1, x2, y2);

		fi_DC->SelectObject(m_penOld);
		m_pen.DeleteObject();
	}
}

void COverlay::OverlayDC_Line(CDC* fi_DC)
{
	fi_DC->SelectStockObject(NULL_BRUSH);

	CPen     m_pen;
	CPen* m_penOld;


	int iCnt;
	int x1, x2, y1, y2;


	int offsetX = m_ptOffset.x;
	int offsetY = m_ptOffset.y;


	for (iCnt = 0; iCnt < clLineList.cnt; iCnt++)
	{
		m_pen.CreatePen(clLineList.style[iCnt], 2, clLineList.c[iCnt]);
		m_penOld = fi_DC->SelectObject(&m_pen);

		x1 = (long)(clLineList.p[iCnt][0].x + 0.5);
		y1 = (long)(clLineList.p[iCnt][0].y + 0.5);
		x2 = (long)(clLineList.p[iCnt][1].x + 0.5);
		y2 = (long)(clLineList.p[iCnt][1].y + 0.5);

		int newX1 = (int)(m_dZoom * (x1 - offsetX) + 0.5);
		int newY1 = (int)(m_dZoom * (y1 - offsetY) + 0.5);
		int newX2 = (int)(m_dZoom * (x2 - offsetX) + 0.5);
		int newY2 = (int)(m_dZoom * (y2 - offsetY) + 0.5);

		fi_DC->MoveTo(newX1, newY1);
		fi_DC->LineTo(newX2, newY2);

		fi_DC->SelectObject(m_penOld);
		m_pen.DeleteObject();
	}

	// Detach the device context.
	fi_DC->Detach();
}

void COverlay::OverlayDC_Pixel(CDC* fi_DC)
{
	CPen     m_pen;
	CPen* m_penOld;

	int iCnt;
	int x, y;

	int offsetX = m_ptOffset.x;
	int offsetY = m_ptOffset.y;


	for (iCnt = 0; iCnt < clPixelList.cnt; iCnt++)
	{
		m_pen.CreatePen(PS_SOLID, 1, clPixelList.c[iCnt]);
		m_penOld = fi_DC->SelectObject(&m_pen);

		x = (long)((clPixelList.p[iCnt].x - offsetX) * m_dZoom + 0.5);
		y = (long)((clPixelList.p[iCnt].y - offsetY) * m_dZoom + 0.5);

		fi_DC->SetPixel(x, y, clPixelList.c[iCnt]);

		fi_DC->SelectObject(m_penOld);
		//		fi_DC->SelectObject(pOldBrush);
		m_pen.DeleteObject();
	}
}

void COverlay::OverlayDC_Text(CDC* fi_DC)
{
	CFont font, * oldfont;

	int iCnt;
	int x, y;
	TCHAR tmpChar[1000];

	int offsetX = m_ptOffset.x;
	int offsetY = m_ptOffset.y;


	if (m_ptClick.x > 0 && m_ptClick.y > 0)
	{
		font.CreateFont(16, 8, 0, 0,
			FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));

		oldfont = fi_DC->SelectObject(&font);

		x = (long)((m_ptClick.x - offsetX) * m_dZoom + 0.5);
		y = (long)((m_ptClick.y - offsetY) * m_dZoom + 0.5);

		fi_DC->SetTextColor(M_COLOR_GREEN);
		fi_DC->TextOut(x+5, y+5, m_szClickText, (int)_tcsclen(m_szClickText));

		fi_DC->SelectObject(oldfont);
		font.DeleteObject();
	}


	font.CreateFont(16, 8, 0, 0,
		FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));

	oldfont = fi_DC->SelectObject(&font);

	TCHAR	szZoom[256];
	_stprintf_s(szZoom, 256, _T("Zoom %.02f"), m_dZoom);

	fi_DC->SetTextColor(M_COLOR_RED);
	fi_DC->TextOut(20, DISP_SIZE_Y - 30, szZoom, (int)_tcsclen(szZoom));

	fi_DC->SelectObject(oldfont);
	font.DeleteObject();

	for (iCnt = 0; iCnt < clTextList.cnt; iCnt++)
	{
		font.CreateFont(clTextList.size[iCnt].y, clTextList.size[iCnt].x, 0, 0,
			FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));

		oldfont = fi_DC->SelectObject(&font);

		x = (long)clTextList.p[iCnt].x;
		y = (long)clTextList.p[iCnt].y;

		int newX = (int)(m_dZoom * (x - offsetX) + 0.5);
		int newY = (int)(m_dZoom * (y - offsetY) + 0.5);

		_stprintf_s(tmpChar, 256, clTextList.str[iCnt]);

		if (clTextList.edgeFlag[iCnt])
		{
			fi_DC->SetTextColor(RGB(0, 0, 0));

			for (int a = -1; a <= 1; a++)
			{
				for (int b = -1; b <= 1; b++)
				{
					fi_DC->TextOut(newX + a, newY + b, tmpChar, (int)_tcsclen(tmpChar));
				}
			}
		}

		fi_DC->SetTextColor(clTextList.c[iCnt]);
		fi_DC->TextOut(newX, newY, tmpChar, (int)_tcsclen(tmpChar));

		fi_DC->SelectObject(oldfont);
		font.DeleteObject();
	}
}

void COverlay::DrawOverlayDC(bool fi_bDrawFlag)
{
	if (!fi_bDrawFlag)
	{
		clBoxList.cnt = clCrossList.cnt = clPixelList.cnt = clCircleList.cnt = clLineList.cnt = clTextList.cnt = 0;

		return;
	}

	MdispControl(m_MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);

	MbufControl(m_MilOverlay, M_DC_ALLOC, M_DEFAULT);
	HDC OverlayDC = (HDC)MbufInquire(m_MilOverlay, M_DC_HANDLE, M_NULL);

	CDC NewDC;

	if (OverlayDC != M_NULL)
	{
		NewDC.Attach(OverlayDC);
		NewDC.SetBkMode(TRANSPARENT);

		OverlayDC_Box(&NewDC);
		OverlayDC_Cross(&NewDC);

		OverlayDC_Text(&NewDC);
		OverlayDC_Circle(&NewDC);
		OverlayDC_Line(&NewDC);
		OverlayDC_Pixel(&NewDC);

		NewDC.Detach();
		MbufControl(m_MilOverlay, M_DC_FREE, M_DEFAULT);
	}

	MbufControl(m_MilOverlay, M_MODIFIED, M_DEFAULT);
}

void COverlay::SetRoi(CRect fi_rcRect)
{
	m_rcZoomRoi = fi_rcRect;
	m_ptOffset = fi_rcRect.TopLeft();
}

CRect COverlay::GetRoi()
{
	return m_rcZoomRoi;
}

CRect COverlay::SetOffset(int nOffsetX, int nOffsetY)
{
	m_ptOffset.x = nOffsetX;
	m_ptOffset.y = nOffsetY;

	m_rcZoomRoi.left = nOffsetX;
	m_rcZoomRoi.top = nOffsetY;

	m_rcZoomRoi.right = (int)(nOffsetX + DISP_SIZE_X / m_dZoom + 0.5);
	m_rcZoomRoi.bottom = (int)(nOffsetY + DISP_SIZE_Y / m_dZoom + 0.5);

	return m_rcZoomRoi;
}

CPoint COverlay::GetOffset()
{
	return m_ptOffset;
}

void COverlay::SetZoomRate(double fi_dRate)
{
	m_dZoom = fi_dRate;
}

double COverlay::GetZoomRate()
{
	return m_dZoom;
}
