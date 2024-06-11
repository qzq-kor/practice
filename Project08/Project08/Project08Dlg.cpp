
// Project08Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project08.h"
#include "Project08Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProject08Dlg 대화 상자



CProject08Dlg::CProject08Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT08_DIALOG, pParent)
	, m_iRadio(FALSE)
	, m_nMovePixel(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProject08Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Radio(pDX, IDC_RADIO_MOVE, m_iRadio);
	DDX_Text(pDX, IDC_EDIT1, m_nMovePixel);
}

BEGIN_MESSAGE_MAP(CProject08Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CProject08Dlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CProject08Dlg::OnBnClickedButtonLoad)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CProject08Dlg::OnButtonMoveLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CProject08Dlg::OnButtonMoveRight)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CProject08Dlg::OnButtonMoveUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CProject08Dlg::OnButtonMoveDown)
	ON_BN_CLICKED(IDC_RADIO_MOVE, &CProject08Dlg::OnBnClickedRadioMove)
	ON_BN_CLICKED(IDC_RADIO_SIZE, &CProject08Dlg::OnBnClickedRadioSize)
END_MESSAGE_MAP()


// CProject08Dlg 메시지 처리기

BOOL CProject08Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bClickFlag = false;
	m_imgBottom, m_imgLeft, m_imgRight, m_imgTop = 0;
	m_dispBottom, m_dispLeft, m_dispRight, m_dispTop = 0;

	theApp.m_Vision.InitVB(false);
	theApp.m_Overlay[0].Init(0, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[DISP_CAM_0] ,GetDlgItem(IDC_STATIC_ORIGINAL), 0, 0, DISP_SIZE_X, DISP_SIZE_Y);
	theApp.m_Overlay[1].Init(1, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[DISP_CAM_ZOOM], GetDlgItem(IDC_STATIC_ZOOM_IN), DISP_SIZE_X + 50 , 0, DISP_ZOOM_SIZE_X, DISP_ZOOM_SIZE_Y);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProject08Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProject08Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProject08Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProject08Dlg::OnBnClickedButtonExit()
{
	CDialogEx::OnOK();
}


void CProject08Dlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.*)|*.*||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufClear(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], 0);
		MbufLoad(filePath, theApp.m_Vision.MilImage[IMAGE_ORIGINAL]);

		theApp.m_Vision.m_ZoomPoint = CPoint(0, 0);

		theApp.m_Vision.m_nNewBufW = IMG_SIZE_X;
		theApp.m_Vision.m_nNewBufH = IMG_SIZE_Y;
		theApp.m_Vision.m_dZoomRate = DISP_IMG_RATE_X;

		theApp.m_Vision.Select_Image(0, 0);
	}
}


void CProject08Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) && m_bClickFlag)
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_ORIGINAL)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		theApp.m_Vision.m_dZoomRate = DISP_IMG_RATE_X;

		if (rect.PtInRect(point))
		{
			MbufGet(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_Image);
			int dispX = (point.x - rect.left);
			int dispY = (point.y - rect.top);
			int x = (point.x - rect.left) / theApp.m_Vision.m_dZoomRate;
			int y = (point.y - rect.top) / theApp.m_Vision.m_dZoomRate;

			int pos = y * IMG_SIZE_X + x, offset = IMG_SIZE_X * IMG_SIZE_Y;
			int Grayscale = theApp.m_Vision.m_ImageProcess[pos];

			CString tmpStr;
			tmpStr.Format(L"(%d, %d) Grayscale: %d", x, y, Grayscale);
			m_dispLeft = min(m_mouseClickPos.x, point.x);
			m_dispTop = min(m_mouseClickPos.y, point.y);
			m_dispRight = max(m_mouseClickPos.x, point.x);
			m_dispBottom = max(m_mouseClickPos.y, point.y);

			m_imgLeft = (m_dispLeft - rect.left) / theApp.m_Vision.m_dZoomRate;
			m_imgTop = (m_dispTop - rect.top) / theApp.m_Vision.m_dZoomRate;
			m_imgRight = (m_dispRight - rect.left) / theApp.m_Vision.m_dZoomRate;
			m_imgBottom = (m_dispBottom - rect.top) / theApp.m_Vision.m_dZoomRate;
			


			theApp.m_Overlay[0].DrawOverlayDC(false);
			theApp.m_Overlay[0].AddBoxList(m_dispLeft, m_dispTop, m_dispRight, m_dispBottom, M_COLOR_GREEN);
			theApp.m_Overlay[0].AddTextList(dispX, dispY, tmpStr, M_COLOR_GREEN, 8, 18);
			theApp.m_Overlay[0].DrawOverlayDC(true);

		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CProject08Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{

		CRect rect;
		GetDlgItem(IDC_STATIC_ORIGINAL)->GetWindowRect(&rect);
		ScreenToClient(&rect);

		if (rect.PtInRect(point))
		{
			/*m_imgBottom, m_imgLeft, m_imgRight, m_imgTop = 0;
			m_dispBottom, m_dispLeft, m_dispRight, m_dispTop = 0;
			m_tmpLeft, m_tmpTop, m_tmpRight, m_tmpBottom = 0;*/
			m_nDispSelect = 0;
			m_mouseClickPos = point;  // 드래그 시작 위치 저장
			m_bClickFlag = true;

		}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CProject08Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nDispSelect == 0 && m_bClickFlag)
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_ORIGINAL)->GetWindowRect(&rect);
		ScreenToClient(&rect);

		if (rect.PtInRect(point) && rect.PtInRect(m_mouseClickPos))
		{

			UpdateImage();
			
		}
	}
	m_bClickFlag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CProject08Dlg::UpdateImage()
{
	MIL_ID MilEdgeContext, MilEdgeResult;
	MIL_INT NumEdgesFound;

	// 오버레이 정보를 바탕으로 이미지 선택 영역 계산
	int width = m_imgRight - m_imgLeft;
	int height = m_imgBottom - m_imgTop;
	MbufClear(theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM], 0);

	if (width > 0 && height > 0) {
		// 이미지 복사 및 리사이징 파라미터 업데이트
		MbufCopyColor2d(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM],
			M_ALL_BANDS, m_imgLeft, m_imgTop, M_ALL_BANDS, 0, 0, width, height);

		// 확대/축소 비율 계산
		MIL_DOUBLE scaleFactorX = static_cast<MIL_DOUBLE>(DISP_ZOOM_SIZE_X) / width;
		MIL_DOUBLE scaleFactorY = static_cast<MIL_DOUBLE>(DISP_ZOOM_SIZE_Y) / height;
		MIL_DOUBLE scaleFactor = min(scaleFactorX, scaleFactorY);
		
		

		MimResize(theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM], theApp.m_Vision.MilImageDisp[DISP_CAM_ZOOM],
			scaleFactor, scaleFactor, M_DEFAULT);

		// 에지 파인더 컨텍스트 및 결과 버퍼 할당
		MedgeAlloc(theApp.m_Vision.MilSystem, M_CONTOUR, M_DEFAULT, &MilEdgeContext);
		MedgeAllocResult(theApp.m_Vision.MilSystem, M_DEFAULT, &MilEdgeResult);

		// 에지 추출 설정
		MedgeControl(MilEdgeContext, M_FILTER_SMOOTHNESS, 70); // 에지의 부드러움을 설정

		// 에지 추출 실행
		MimResize(theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM], theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM],
			scaleFactor, scaleFactor, M_DEFAULT);
		MedgeCalculate(MilEdgeContext, theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM], M_NULL, M_NULL, M_NULL, MilEdgeResult, M_DEFAULT);

		// 에지 개수 확인
		MedgeGetResult(MilEdgeResult, M_DEFAULT, M_NUMBER_OF_CHAINS + M_TYPE_MIL_INT, &NumEdgesFound, M_NULL);

		// 결과를 시각적으로 그리기
		if (NumEdgesFound > 0) {
			MgraColor(M_DEFAULT, M_COLOR_GREEN);  // 그리기 색상 설정
	
			MedgeDraw(M_DEFAULT, MilEdgeResult, theApp.m_Vision.MilImageDisp[DISP_CAM_ZOOM], M_DRAW_EDGES, M_DEFAULT, M_DEFAULT);

		}

	}

}

void CProject08Dlg::OnButtonMoveLeft()
{
	if(m_iRadio == 0)
		OnButtonMove(0); // Left
	else
		OnButtonResizing(0);
}

void CProject08Dlg::OnButtonMoveRight()
{
	if(m_iRadio == 0)
		OnButtonMove(1); // Right
	else
		OnButtonResizing(1);
}

void CProject08Dlg::OnButtonMoveUp()
{
	if (m_iRadio == 0)
		OnButtonMove(2); // Up
	else
		OnButtonResizing(2);
}

void CProject08Dlg::OnButtonMoveDown()
{
	if (m_iRadio == 0)
		OnButtonMove(3); // Down
	else
		OnButtonResizing(3);
}

void CProject08Dlg::OnButtonResizing(int nDirection)
{

	switch (nDirection) {
	case 0: // Left
		theApp.m_Overlay[0].ExpandLeft(m_nMovePixel);
		m_imgLeft -= m_nMovePixel; // 이미지 선택 영역 왼쪽 경계 업데이트
		break;
	case 1: // Right
		theApp.m_Overlay[0].ExpandRight(m_nMovePixel);
		m_imgRight += m_nMovePixel; // 이미지 선택 영역 오른쪽 경계 업데이트
		break;
	case 2: // Up
		theApp.m_Overlay[0].ExpandTop(m_nMovePixel);
		m_imgTop -= m_nMovePixel; // 이미지 선택 영역 상단 경계 업데이트
		break;
	case 3: // Down
		theApp.m_Overlay[0].ExpandBottom(m_nMovePixel);
		m_imgBottom += m_nMovePixel; // 이미지 선택 영역 하단 경계 업데이트
		break;
	}

	theApp.m_Overlay[0].DrawOverlayDC(true);
	UpdateImage();
}


void CProject08Dlg::OnButtonMove(int nDirection)
{
	// 이동 픽셀 설정
	

	// 임시 좌표를 사용하여 선택 영역만 이동시킴
	switch (nDirection) {
	case 0: // Left
		theApp.m_Overlay[0].ExpandLeft(m_nMovePixel);
		theApp.m_Overlay[0].ExpandRight(-m_nMovePixel);
		m_imgLeft -= m_nMovePixel;
		m_imgRight -= m_nMovePixel;
		break;
	case 1: // Right
		theApp.m_Overlay[0].ExpandLeft(-m_nMovePixel);
		theApp.m_Overlay[0].ExpandRight(m_nMovePixel);
		m_imgLeft += m_nMovePixel;
		m_imgRight += m_nMovePixel;
		break;
	case 2: // Up
		theApp.m_Overlay[0].ExpandTop(m_nMovePixel);
		theApp.m_Overlay[0].ExpandBottom(-m_nMovePixel);
		m_imgTop -= m_nMovePixel;
		m_imgBottom -= m_nMovePixel;
		break;
	case 3: // Down
		theApp.m_Overlay[0].ExpandTop(-m_nMovePixel);
		theApp.m_Overlay[0].ExpandBottom(m_nMovePixel);
		m_imgTop += m_nMovePixel;
		m_imgBottom += m_nMovePixel;
		break;
	}

	theApp.m_Overlay[0].DrawOverlayDC(true);
	UpdateImage();
}



void CProject08Dlg::OnBnClickedRadioMove()
{
	UpdateData(TRUE);
}


void CProject08Dlg::OnBnClickedRadioSize()
{
	UpdateData(TRUE);
}

BOOL CProject08Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString str;
		int nEdit;

		if (pMsg->hwnd == GetDlgItem(IDC_EDIT1)->m_hWnd)
		{
			GetDlgItemText(IDC_EDIT1, str);
			nEdit = _ttoi(str); 
			m_nMovePixel = nEdit; 
			UpdateData(TRUE);
			return TRUE; 
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}