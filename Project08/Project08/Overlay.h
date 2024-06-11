#pragma once

#define MAX_CNT_PIXEL	200
#define MAX_CNT_LINE	500
#define MAX_CNT_BOX		500
#define MAX_CNT_CROSS	10000
#define MAX_CNT_CIRCLE	5
#define MAX_CNT_TEXT	500

//----------Point----------//
class CDrawDcPixel {
public:
	int			cnt;
	COLORREF*	c;
	POINT*		p;
};

//----------Line----------//
class CDrawDcLine {
public:
	int			cnt;
	COLORREF	c[MAX_CNT_LINE];
	POINT		p[MAX_CNT_LINE][2];
	int			style[MAX_CNT_LINE];
};

//----------Box----------//
class CDrawDcBox {
public:
	int			cnt;
	CRect		r[MAX_CNT_BOX];
	COLORREF	c[MAX_CNT_BOX];
	int			style[MAX_CNT_BOX];
};

//----------Circle----------//
class CDrawDcCircle {
public:
	int			cnt;
	CRect		r[MAX_CNT_CIRCLE];
	COLORREF	c[MAX_CNT_CIRCLE];
};

//----------Cross----------//
class CDrawDcCross {
public:
	int			cnt;
	CPoint		p[MAX_CNT_CROSS];
	COLORREF	c[MAX_CNT_CROSS];
	int			w1[MAX_CNT_CROSS];
	int			w2[MAX_CNT_CROSS];
};

//----------Text----------//
class CDrawDcText {
public:
	int			cnt;							//개수
	CPoint		p[MAX_CNT_TEXT];				//좌표
	COLORREF	c[MAX_CNT_TEXT];				//색깔
	TCHAR		str[MAX_CNT_TEXT][1000];				//내용
	CPoint		size[MAX_CNT_TEXT];				//폰트 크기	
	TCHAR		fontname[MAX_CNT_TEXT][100];	//폰트명
	bool		edgeFlag[MAX_CNT_TEXT];			//외각선
};

class COverlay
{
public:
	COverlay(void);
	~COverlay(void);

	MIL_ID			m_MilDisplay;
	MIL_ID			m_MilOverlay;
	MIL_INT			m_TransColor;


	int		m_nDispIndex;

	int		m_nDispPositionX;
	int		m_nDispPositionY;

	int		m_nDispSizeX;
	int		m_nDispSizeY;

	CRect	m_rcZoomRoi;
	double	m_dZoom;
	CPoint	m_ptOffset;
	CPoint  m_LastOverlayPosition;
	POINT	m_ptClick;
	TCHAR	m_szClickText[256];

	void Init(int fi_nDisp, MIL_ID fi_MilSystem, MIL_ID fi_MilImage, CWnd* pWnd, int sx, int sy, int sizeX, int sizeY);
	void Free();

	void InitOverlayList();
	void FreeOverlayList();

	void DrawOverlayDC(bool fi_bDrawFlag);
	void UpdateOverlayPosition(int x, int y);

	void OverlayDC_Text(CDC* fi_DC);
	void OverlayDC_Pixel(CDC* fi_DC);
	void OverlayDC_Line(CDC* fi_DC);
	void OverlayDC_Circle(CDC* fi_DC);
	void OverlayDC_Cross(CDC* fi_DC);
	void OverlayDC_Box(CDC* fi_DC);
	
	void AddCircleList(int fi_iLeft, int fi_iTop, int fi_iRight, int fi_iBottom, COLORREF fi_color);
	void AddBoxList(int fi_iLeft, int fi_iTop, int fi_iRight, int fi_iBottom, COLORREF fi_color, int fi_iStyle = PS_SOLID);
	void AddBoxList(RECT fi_rect, COLORREF fi_color, int fi_iStyle = PS_SOLID);
	void AddPixelList(int fi_iX, int fi_iY, COLORREF fi_color);
	void AddLineList(int fi_iSx, int fi_iSy, int fi_iEx, int fi_iEy, COLORREF fi_color, int fi_iStyle = PS_SOLID);
	void AddLineList(double fi_dSx, double fi_dSy, double fi_dEx, double fi_dEy, COLORREF fi_color, int fi_iStyle = PS_SOLID);
	void AddLineList(CDPoint ptStart, CDPoint ptEnd, COLORREF fi_color, int fi_iStyle = PS_SOLID);
	void AddCrossList(int fi_iX, int fi_iY, int fi_iWdt1, int fi_iWdt2, COLORREF fi_color);
	void AddTextList(int fi_iX, int fi_iY, CString fi_sText, COLORREF fi_color, int fi_iSizeX = 12, int fi_iSizeY = 20, bool fi_bEgdeFlag = false);
	void ExpandLeft(int nPixels);
	void ExpandRight(int nPixels);
	void ExpandTop(int nPixels);
	void ExpandBottom(int nPixels);
	void SetRoi(CRect fi_rcRect);
	CRect GetRoi();

	CRect SetOffset(int nOffsetX, int nOffsetY);
	CPoint GetOffset();

	void SetZoomRate(double fi_dZoomRate);
	double GetZoomRate();


	CDrawDcLine		clLineList;
	CDrawDcPixel	clPixelList;
	CDrawDcBox		clBoxList;
	CDrawDcCircle	clCircleList;
	CDrawDcCross	clCrossList;
	CDrawDcText		clTextList;

	CRITICAL_SECTION m_csOverlay;
};

