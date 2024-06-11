
// Project5Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project5.h"
#include "Project5Dlg.h"
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


// CProject5Dlg 대화 상자



CProject5Dlg::CProject5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT5_DIALOG, pParent)
	
	, m_Edit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProject5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CProject5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_BUTTON, &CProject5Dlg::OnBnClickedLoadButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CProject5Dlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CProject5Dlg::OnBnClickedExitButton)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CProject5Dlg::OnBnClickedButtonTest)


	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CProject5Dlg 메시지 처리기

BOOL CProject5Dlg::OnInitDialog()
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
	theApp.m_Vision.InitVB(0);
	theApp.m_Overlay[0].Init(0, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[0], GetDlgItem(IDC_STATIC_IMAGE), 0, 0, DISP_SELECT_SIZE_X, DISP_SELECT_SIZE_Y);
	theApp.m_Overlay[1].Init(1, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[1], GetDlgItem(IDC_STATIC_IMAGE2), 0, DISP_SELECT_SIZE_Y, DISP_SELECT_SIZE_X, DISP_SELECT_SIZE_Y);
	theApp.m_Overlay[2].Init(2, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[2], GetDlgItem(IDC_STATIC_IMAGE3), DISP_SELECT_SIZE_X, 0, DISP_SIZE_X, DISP_SIZE_Y);
	//theApp.m_Overlay[3].Init(3, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[3], GetDlgItem(IDC_STATIC_ZOOM), 0, DISP_SELECT_SIZE_Y * 2, DISP_SIZE_X, DISP_SIZE_Y);


	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	if (pSlider != nullptr)
	{
		pSlider->SetRange(0, 100);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProject5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProject5Dlg::OnPaint()
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

HCURSOR CProject5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProject5Dlg::OnBnClickedLoadButton()
{
	theApp.m_Vision.m_dZoomRate = DISP2_IMG_RATE_X;

	CFileDialog dlg1(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.*)|*.*||"), NULL);
	if (dlg1.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg1.GetPathName().GetBuffer());
		MbufClear(theApp.m_Vision.MilImage[IMAGE_FIRST], 0);
		MbufLoad(filePath, theApp.m_Vision.MilImage[IMAGE_FIRST]);
			theApp.m_Vision.Load_Image(0, 0);
		}
	
	CFileDialog dlg2(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.*)|*.*||"), NULL);
    if (dlg2.DoModal() == IDOK)
    {
        TCHAR filePath[MAX_PATH];
        _tcscpy_s(filePath, dlg2.GetPathName().GetBuffer());
        MbufClear(theApp.m_Vision.MilImage[IMAGE_SECOND], 0);
        MbufLoad(filePath, theApp.m_Vision.MilImage[IMAGE_SECOND]);
            theApp.m_Vision.Load_Image(1, 1);

    }
}

void CProject5Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CRect rect[3];

	GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect[0]);
	GetDlgItem(IDC_STATIC_IMAGE2)->GetWindowRect(&rect[1]);
	GetDlgItem(IDC_STATIC_IMAGE3)->GetWindowRect(&rect[2]);

	ScreenToClient(&rect[0]);
	ScreenToClient(&rect[1]);
	ScreenToClient(&rect[2]);

	if (rect[0].PtInRect(point))
	{
		m_nDispSelect = 0;

	}
	else if (rect[1].PtInRect(point))
	{
		m_nDispSelect = 1;
	}

	else if (rect[2].PtInRect(point))
	{

		m_nDispSelect = 2; // 해당 영역에 대한 처리
		
		m_mouseClickPos = point;  // 드래그 시작 위치 저장
		m_bClickFlag = true;
	}

	if (m_nDispSelect == 0)
	{
		MbufGet(theApp.m_Vision.MilImage[IMAGE_FIRST], theApp.m_Vision.m_Image);
		OnChangeScreen();

	}
	else if (m_nDispSelect == 1)
	{
		MbufGet(theApp.m_Vision.MilImage[IMAGE_SECOND], theApp.m_Vision.m_Image);
		OnChangeScreen();
	}



	if (m_pDlg != NULL && !m_pDlg->IsDialogClicked(point))
	{
		m_pDlg->DestroyWindow();
		m_pDlg = NULL;
	}


	CDialogEx::OnLButtonDown(nFlags, point); // 기본 처리 호출
}

void CProject5Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nDispSelect == 2 && m_bClickFlag)
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_IMAGE3)->GetWindowRect(&rect);
		ScreenToClient(&rect);

		if (rect.PtInRect(point) && rect.PtInRect(m_mouseClickPos))
		{

			int width = m_imgRight - m_imgLeft;
			int height = m_imgBottom - m_imgTop;

			if (width > 0 && height > 0) {
				MbufClear(theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM], 0);

				MbufCopyColor2d(theApp.m_Vision.MilImage[IMAGE_EDGE], theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM],
					M_ALL_BANDS, m_imgLeft, m_imgTop, M_ALL_BANDS, 0, 0, width, height);

				MIL_DOUBLE scaleFactorX = static_cast<MIL_DOUBLE>(DISP_SIZE_X) / width;
				MIL_DOUBLE scaleFactorY = static_cast<MIL_DOUBLE>(DISP_SIZE_Y) / height;
				MIL_DOUBLE scaleFactor = min(scaleFactorX, scaleFactorY);


				MimResize(theApp.m_Vision.MilImageZoom[DISP_CAM_ZOOM], theApp.m_Vision.MilImageDisp[DISP_CAM_ZOOM],
					scaleFactor, scaleFactor, M_DEFAULT);
				
				if (m_pDlg != NULL)
				{
					m_pDlg->DestroyWindow();
					m_pDlg = NULL;
				}

				m_pDlg = new ZoomDialog(this);
				m_pDlg->Create(IDD_DIALOG_ZOOM, this);
				m_pDlg->ShowWindow(SW_SHOW);
			}
		}
	}
	m_bClickFlag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CProject5Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nDispSelect == 2)
	{
		if ((nFlags & MK_LBUTTON) && m_bClickFlag)
		{
			CRect rect;
			GetDlgItem(IDC_STATIC_IMAGE3)->GetWindowRect(&rect);
			ScreenToClient(&rect);

			if (rect.PtInRect(point))
			{
				//MbufGet(theApp.m_Vision.MilImage[IMAGE_EDGE], theApp.m_Vision.m_ImageEdge);

				theApp.m_Vision.m_dZoomRate = DISP_IMG_RATE_X;
				int dispX = (point.x - rect.left) / theApp.m_Vision.m_dZoomRate;
				int dispY = (point.y - rect.top) / theApp.m_Vision.m_dZoomRate;

				CString tmpStr;
				tmpStr.Format(L"(%d, %d)", dispX, dispY);

				int left = min(m_mouseClickPos.x, point.x);
				int top = min(m_mouseClickPos.y, point.y);
				int right = max(m_mouseClickPos.x, point.x);
				int bottom = max(m_mouseClickPos.y, point.y);

				m_imgLeft = (left - rect.left) / theApp.m_Vision.m_dZoomRate;
				m_imgTop = (top - rect.top) / theApp.m_Vision.m_dZoomRate;
				m_imgRight = (right - rect.left) / theApp.m_Vision.m_dZoomRate;
				m_imgBottom = (bottom - rect.top) / theApp.m_Vision.m_dZoomRate;

				theApp.m_Overlay[2].DrawOverlayDC(false);
				theApp.m_Overlay[2].AddBoxList(m_imgLeft, m_imgTop, m_imgRight, m_imgBottom, M_COLOR_GREEN);
				theApp.m_Overlay[2].AddTextList(dispX, dispY, tmpStr, M_COLOR_GREEN, 8, 18);
				theApp.m_Overlay[2].DrawOverlayDC(true);

			}
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CProject5Dlg::OnBnClickedSaveButton()
{
	CFileDialog dlg(FALSE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.bmp)|*.bmp||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufSave(filePath, theApp.m_Vision.MilImage[IMAGE_EDGE]);
	}
}

void CProject5Dlg::OnBnClickedExitButton()
{
	CDialogEx::OnOK();
}

void CProject5Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	// 슬라이더 이벤트 확인
	if (pScrollBar == (CScrollBar*)&m_Slider) {
		int sliderValue = m_Slider.GetPos();  // 슬라이더의 현재 위치를 가져옴
		m_Edit = sliderValue;  // m_Edit 변수 업데이트

		// m_Edit 값을 에디트 박스에 반영
		SetDlgItemInt(IDC_EDIT1, m_Edit, FALSE);  // IDC_EDIT1는 에디트 컨트롤의 식별자입니다.

	}

	OnChangeScreen();
	UpdateData(FALSE);
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar); // 기본 스크롤 처리를 위해 필요
}


void CProject5Dlg::OnChangeScreen()
{
	int threshold = m_Slider.GetPos();
	int nPos;

	int nOffset = IMG_SIZE_X * IMG_SIZE_Y;

	for (int y = 0; y < IMG_SIZE_Y; y++)  // 경계 처리를 위해 1부터 시작
	{
		for (int x = 0; x < IMG_SIZE_X; x++)  // 마찬가지로 경계 처리
		{
			nPos = y * IMG_SIZE_X + x;
			// 이미지 버퍼에서 RGB 값을 추출하여 그레이스케일 값 계산
			int r = theApp.m_Vision.m_Image[nPos];
			int g = theApp.m_Vision.m_Image[nPos + nOffset];
			int b = theApp.m_Vision.m_Image[nPos + 2 * nOffset];
			int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

			theApp.m_Vision.m_ImageGray[nPos] = gray;
		}
	}

	for (int y = 1; y < IMG_SIZE_Y - 1; y++)  // 경계 처리를 위해 1부터 시작
	{
		for (int x = 1; x < IMG_SIZE_X - 1; x++)  // 마찬가지로 경계 처리
		{
			nPos = y * IMG_SIZE_X + x;
			// 이미지 버퍼에서 RGB 값을 추출하여 그레이스케일 값 계산

			// 라플라시안 필터 적용
			int laplacian = 8 * theApp.m_Vision.m_ImageGray[nPos]
				- theApp.m_Vision.m_ImageGray[nPos + 1]
				- theApp.m_Vision.m_ImageGray[nPos - 1]
				- theApp.m_Vision.m_ImageGray[nPos + IMG_SIZE_X]
				- theApp.m_Vision.m_ImageGray[nPos - IMG_SIZE_X]
				- theApp.m_Vision.m_ImageGray[nPos + IMG_SIZE_X + 1]
				- theApp.m_Vision.m_ImageGray[nPos + IMG_SIZE_X - 1]
				- theApp.m_Vision.m_ImageGray[nPos - IMG_SIZE_X + 1]
				- theApp.m_Vision.m_ImageGray[nPos - IMG_SIZE_X - 1];

			// 결과를 이진화하여 저장
			theApp.m_Vision.m_ImageProcess[nPos] = (abs(laplacian) > threshold) ? 255 : 0;
			theApp.m_Vision.m_ImageProcess[nPos + nOffset] = (abs(laplacian) > threshold) ? 255 : 0;
			theApp.m_Vision.m_ImageProcess[nPos + 2 * nOffset] = (abs(laplacian) > threshold) ? 255 : 0;


		}

	}
	MbufPut(theApp.m_Vision.MilImage[IMAGE_MAIN], theApp.m_Vision.m_ImageProcess); // main에 display하기 위함
	theApp.m_Vision.Select_Image(2, 2);
 	MbufPut(theApp.m_Vision.MilImage[IMAGE_EDGE], theApp.m_Vision.m_ImageProcess); // Overay 작업하기 위함
}

void CProject5Dlg::OnBnClickedButtonTest()
{


	

}
