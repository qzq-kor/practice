
// Project3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project3.h"
#include "Project3Dlg.h"
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


// CProject3Dlg 대화 상자



CProject3Dlg::CProject3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT3_DIALOG, pParent)
	, m_Edit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProject3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, m_Slider);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CProject3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()

	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CProject3Dlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CProject3Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CProject3Dlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CProject3Dlg::OnBnClickedButtonExit)
	ON_WM_HSCROLL()

END_MESSAGE_MAP()


// CProject3Dlg 메시지 처리기

BOOL CProject3Dlg::OnInitDialog()
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

	theApp.m_Vision.InitVB(0);
	theApp.m_Overlay[0].Init(0, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImage[IMAGE_ORIGINAL], GetDlgItem(IDC_STATIC_IMAGE), 0, 0, DISP_SIZE_X, DISP_SIZE_Y);
	theApp.m_Overlay[1].Init(1, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImage[IMAGE_GRAY], GetDlgItem(IDC_STATIC_IMAGE_2), DISP_SIZE_X, 0, DISP_SIZE_X, DISP_SIZE_Y);

	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	if (pSlider != nullptr)
	{
		pSlider->SetRange(0, 255);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProject3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProject3Dlg::OnPaint()
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
HCURSOR CProject3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProject3Dlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.*)|*.*||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufClear(theApp.m_Vision.MilImage[0], 0);
		MbufClear(theApp.m_Vision.MilImage[1], 0);

		MbufLoad(filePath, theApp.m_Vision.MilImage[0]);
		MbufLoad(filePath, theApp.m_Vision.MilImage[1]);
	}
}


void CProject3Dlg::OnBnClickedButtonSave()
{
	CFileDialog dlg(FALSE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.bmp)|*.bmp||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufSave(filePath, theApp.m_Vision.MilImage[IMAGE_ORIGINAL]);
	}
}


void CProject3Dlg::OnBnClickedButtonClear()
{
	theApp.m_Overlay[0].DrawOverlayDC(false);
	theApp.m_Overlay[1].DrawOverlayDC(false);

	theApp.m_Overlay[0].DrawOverlayDC(true);
	theApp.m_Overlay[1].DrawOverlayDC(true);
}


void CProject3Dlg::OnBnClickedButtonExit()
{
	CDialogEx::OnOK();
}

void CProject3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect[2];
	GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect[0]);
	GetDlgItem(IDC_STATIC_IMAGE_2)->GetWindowRect(&rect[1]);

	ScreenToClient(&rect[0]);
	ScreenToClient(&rect[1]);

	// 이미지 영역 내의 상대적 클릭 위치 계산
	CPoint relPoint[2]; // 각 이미지에 대한 상대적 위치

	if (rect[0].PtInRect(point)){
		relPoint[0] = point - rect[0].TopLeft();
		relPoint[1] = point - rect[0].TopLeft(); // rect[0]에 point 찍혔을 때 x,y 좌표 동일하게 해줌
	}
	else if (rect[1].PtInRect(point)){
		relPoint[0] = point - rect[1].TopLeft(); // rect[1]에 point 찍혔을 때 x,y 좌표 동일하게 해줌
		relPoint[1] = point - rect[1].TopLeft(); 
	}
	// 모든 이미지에 대해 처리
	for (int i = 0; i < 2; i++) {
		{
		// 이미지 데이터 가져오기
		MbufGet(theApp.m_Vision.MilImage[i], theApp.m_Vision.m_Image);

		// 오버레이를 적용할 위치
		int x = relPoint[i].x;
		int y = relPoint[i].y;
		int pos = y * IMG_SIZE_X + x, offset = IMG_SIZE_X * IMG_SIZE_Y;

		// RGB 데이터 추출
		int r = theApp.m_Vision.m_Image[pos];
		int g = theApp.m_Vision.m_Image[pos + offset];
		int b = theApp.m_Vision.m_Image[pos + 2 * offset];

		// 오버레이 텍스트 생성 및 출력
		CString tmpStr;
		tmpStr.Format(L"(%d, %d) %d, %d, %d", x, y, r, g, b);
		theApp.m_Overlay[i].AddTextList(x, y, tmpStr, M_COLOR_GREEN, 8, 18);
		theApp.m_Overlay[i].AddCrossList(x, y, 5, 5, M_COLOR_GREEN);
		theApp.m_Overlay[i].DrawOverlayDC(true);

		CString listBoxStr;
		if (i == 0) {
			listBoxStr.Format(L"Original: (%d, %d) %d, %d, %d", x, y, r, g, b);
		}
		else {
			listBoxStr.Format(L"Binary: (%d, %d) %d, %d, %d", x, y, r, g, b);
		}
		m_list.AddString(listBoxStr);
	
	}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CProject3Dlg::OnBinarizeSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}


void CProject3Dlg::OnBinarize()
{

	int threshold = m_Slider.GetPos();
	MbufGet(theApp.m_Vision.MilImage[0], theApp.m_Vision.m_Image);
	//원본 데이터 기준으로 이진화를 진행해야함
	

	int pos, offset = IMG_SIZE_X * IMG_SIZE_Y;
	for (int y = 0; y < IMG_SIZE_Y; y++)
	{
		for (int x = 0; x < IMG_SIZE_X; x++)
		{
			pos = y * IMG_SIZE_X + x;
			// 이미지 버퍼에서 RGB 값을 추출합니다.
			int r = theApp.m_Vision.m_Image[pos];
			int g = theApp.m_Vision.m_Image[pos + offset];
			int b = theApp.m_Vision.m_Image[pos + 2 * offset];

			// 그레이스케일 값 계산
			int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

			// 이진화 처리
			theApp.m_Vision.m_Image[pos] = gray > threshold ? 255 : 0;
			theApp.m_Vision.m_Image[pos + offset] = gray > threshold ? 255 : 0;
			theApp.m_Vision.m_Image[pos + 2 * offset] = gray > threshold ? 255 : 0;
		
		
		}
	}

	MbufPut(theApp.m_Vision.MilImage[1], theApp.m_Vision.m_Image);
}


void CProject3Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar); // 기본 스크롤 처리를 위해 필요

	// 슬라이더 이벤트 확인
	if (pScrollBar == (CScrollBar*)&m_Slider) {
		int sliderValue = m_Slider.GetPos();  // 슬라이더의 현재 위치를 가져옴
		m_Edit = sliderValue;  // m_Edit 변수 업데이트

		// m_Edit 값을 에디트 박스에 반영
		SetDlgItemInt(IDC_EDIT1, m_Edit, FALSE);  // IDC_EDIT1는 에디트 컨트롤의 식별자입니다.

		OnBinarize();
	}
}
