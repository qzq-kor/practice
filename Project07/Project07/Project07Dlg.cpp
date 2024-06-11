
// Project07Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project07.h"
#include "Project07Dlg.h"
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


// CProject07Dlg 대화 상자



CProject07Dlg::CProject07Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT07_DIALOG, pParent)

	, m_iRadio_Type(FALSE)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProject07Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO_ORIGINAL, m_iRadio_Type);

	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CProject07Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CProject07Dlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_RADIO_ORIGINAL, &CProject07Dlg::OnBnClickedRadioOriginal)
	ON_BN_CLICKED(IDC_STATIC_SHARP, &CProject07Dlg::OnBnClickedStaticSharp)
	ON_BN_CLICKED(IDC_RADIO_SMOOTH, &CProject07Dlg::OnBnClickedRadioSmooth)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CProject07Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CProject07Dlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CProject07Dlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CProject07Dlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CProject07Dlg 메시지 처리기

BOOL CProject07Dlg::OnInitDialog()
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


	theApp.m_Vision.InitVB(true);

	theApp.m_Overlay[0].Init(0, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[0], GetDlgItem(IDC_STATIC_IMAGE), 0, 0, DISP_SIZE_X, DISP_SIZE_Y);
	theApp.m_Overlay[1].Init(1, theApp.m_Vision.MilSystem, theApp.m_Vision.MilImageDisp[1], GetDlgItem(IDC_STATIC_IMAGE2), DISP_SIZE_X, 0, DISP_SIZE_X, DISP_SIZE_Y);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProject07Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProject07Dlg::OnPaint()
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
HCURSOR CProject07Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProject07Dlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.*)|*.*||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		OnBnClickedButtonStop();
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufClear(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], 0);
		MbufLoad(filePath, theApp.m_Vision.MilImage[IMAGE_ORIGINAL]);

		theApp.m_Vision.m_ZoomPoint = CPoint(0, 0);

		theApp.m_Vision.m_nNewBufW = IMG_SIZE_X;
		theApp.m_Vision.m_nNewBufH = IMG_SIZE_Y;
		theApp.m_Vision.m_dZoomRate = DISP_IMG_RATE_X;

		theApp.m_Vision.Select_Image(0, 0);
		theApp.m_Vision.Select_Image(0, 1);

				MbufGet(theApp.m_Vision.MilImage[0], theApp.m_Vision.m_Image);
				MbufPut(theApp.m_Vision.MilImage[1], theApp.m_Vision.m_Image);
				MbufPut(theApp.m_Vision.MilImage[2], theApp.m_Vision.m_Image);
		// 초기 영상 버퍼 = 원본

	}
}


	void CProject07Dlg::OnBnClickedRadioOriginal()
	{
		UpdateData(TRUE);
		ProcessImage(m_iRadio_Type);
		theApp.m_Vision.Select_Image(m_iRadio_Type, 1);
	}


	void CProject07Dlg::OnBnClickedStaticSharp()
	{
		UpdateData(TRUE);
		ProcessImage(m_iRadio_Type);
		theApp.m_Vision.Select_Image(m_iRadio_Type, 1);
	}


	void CProject07Dlg::OnBnClickedRadioSmooth()
	{
		UpdateData(TRUE);
		ProcessImage(m_iRadio_Type);
		theApp.m_Vision.Select_Image(m_iRadio_Type, 1);
	}

	void CProject07Dlg::ProcessImage(int m_iRadio_Type)
	{
		MbufGet(theApp.m_Vision.MilImage[0], theApp.m_Vision.m_Image);


		if (m_iRadio_Type == 1) // Sharp
		{
			ApplySharpeningFilter();
		}
		else if (m_iRadio_Type == 2) // Smooth
		{
			ApplySmoothingFilter();
		}

		if(m_iRadio_Type == 1 || m_iRadio_Type == 2)
		MbufPut(theApp.m_Vision.MilImage[m_iRadio_Type], theApp.m_Vision.m_ImageProcess);
	}

	/*void CProject07Dlg::ApplySharpeningFilter()
	{
		int width = IMG_SIZE_X - 1;
		int height = IMG_SIZE_Y - 1;
		int offset = IMG_SIZE_X * IMG_SIZE_Y;
		int pos;

		for (int channel = 0; channel < 3; channel++)
		{
			for (int y = 1; y < height; y++)
			{
				pos = y * IMG_SIZE_X + 1 + channel * offset;
		
				for (int x = 1; x < width; x++)
				{
					int sharp =
						theApp.m_Vision.m_Image[pos] * 5
						- (theApp.m_Vision.m_Image[pos - 1] +
						theApp.m_Vision.m_Image[pos + 1] +
						theApp.m_Vision.m_Image[pos - IMG_SIZE_X] +
						theApp.m_Vision.m_Image[pos + IMG_SIZE_X]);

					sharp = (sharp > 255) ? 255 : (sharp < 0) ? 0 : sharp;
					theApp.m_Vision.m_ImageProcess[pos] = sharp;

					pos++;
				}
			}
		}
	}*/
	void CProject07Dlg::ApplySharpeningFilter()
	{
		int width = IMG_SIZE_X - 1;
		int height = IMG_SIZE_Y - 1;

		for (int y = 1; y < height; y++)
		{
			int pos = y * IMG_SIZE_X + 1;

			for (int x = 1; x < width; x++)
			{
				int sharp =
					theApp.m_Vision.m_Image[pos] * 5
					- (theApp.m_Vision.m_Image[pos - 1] +
						theApp.m_Vision.m_Image[pos + 1] +
						theApp.m_Vision.m_Image[pos - IMG_SIZE_X] +
						theApp.m_Vision.m_Image[pos + IMG_SIZE_X]);

				sharp = (sharp > 255) ? 255 : (sharp < 0) ? 0 : sharp;
				theApp.m_Vision.m_ImageProcess[pos] = sharp;

				pos++;
			}
		}
	}

	/*void CProject07Dlg::ApplySmoothingFilter()
	{
		int width = IMG_SIZE_X;
		int height = IMG_SIZE_Y;
		int offset = width * height;

		for (int y = 1; y < height - 1; y++) {
			for (int x = 1; x < width - 1; x++) {
				for (int channel = 0; channel < 3; channel++) {
					int pos = y * width + x + channel * offset;

					int sum =
						theApp.m_Vision.m_Image[pos - 1] +
						theApp.m_Vision.m_Image[pos + 1] +
						theApp.m_Vision.m_Image[pos - width] +
						theApp.m_Vision.m_Image[pos + width] +
						theApp.m_Vision.m_Image[pos - width - 1] +
						theApp.m_Vision.m_Image[pos - width + 1] +
						theApp.m_Vision.m_Image[pos + width - 1] +
						theApp.m_Vision.m_Image[pos + width + 1] +
						theApp.m_Vision.m_Image[pos];

					int average = sum / 9;
					theApp.m_Vision.m_ImageProcess[pos] = average;
				}
			}
		}
	}*/
	void CProject07Dlg::ApplySmoothingFilter()
	{
		int width = IMG_SIZE_X - 1;
		int height = IMG_SIZE_Y - 1;

		for (int y = 1; y < height - 1; y++) {
			int pos = y * IMG_SIZE_X + 1;

			for (int x = 1; x < width - 1; x++) {

				int sum =
					theApp.m_Vision.m_Image[pos - 1] +
					theApp.m_Vision.m_Image[pos + 1] +
					theApp.m_Vision.m_Image[pos - width] +
					theApp.m_Vision.m_Image[pos + width] +
					theApp.m_Vision.m_Image[pos - width - 1] +
					theApp.m_Vision.m_Image[pos - width + 1] +
					theApp.m_Vision.m_Image[pos + width - 1] +
					theApp.m_Vision.m_Image[pos + width + 1] +
					theApp.m_Vision.m_Image[pos];

				pos++;

				int average = sum / 9;
				average = (average > 255) ? 255 : (average < 0) ? 0 : average;

				theApp.m_Vision.m_ImageProcess[pos] = average;
			}
		}
	}

	int CProject07Dlg::GetRadioType() const
	{
		return m_iRadio_Type;  // m_iRadio_Type의 값을 반환
	}

	void CProject07Dlg::OnBnClickedButtonSave()
	{
		CFileDialog dlg(FALSE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.bmp)|*.bmp||"), NULL);

		if (dlg.DoModal() == IDOK)
		{
			TCHAR filePath[MAX_PATH];
			_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

			if(m_iRadio_Type == 0)
				MbufSave(filePath, theApp.m_Vision.MilImage[0]);
			else if (m_iRadio_Type == 1)
				MbufSave(filePath, theApp.m_Vision.MilImage[1]);
			else if (m_iRadio_Type == 2)
				MbufSave(filePath, theApp.m_Vision.MilImage[2]);


		}
	}


	void CProject07Dlg::OnBnClickedButtonExit()
	{
		CDialogEx::OnOK();
	}


	void CProject07Dlg::OnBnClickedButtonPlay()
	{
		theApp.m_Vision.UserHookData.nGrabCnt = 0;
		theApp.m_Vision.GrabProcessStart(true);
	}


	void CProject07Dlg::OnBnClickedButtonStop()
	{
		theApp.m_Vision.GrabProcessStart(false);
	}


/*
	void CProject07Dlg::OnLButtonDown(UINT nFlags, CPoint point)
	{
		CRect rect[2];
		GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect[0]);
		GetDlgItem(IDC_STATIC_IMAGE_2)->GetWindowRect(&rect[1]);

		ScreenToClient(&rect[0]);
		ScreenToClient(&rect[1]);

		// 이미지 영역 내의 상대적 클릭 위치 계산
		theApp.m_Vision.m_dZoomRate = DISP_IMG_RATE_X;

		/ *int x = point.x- rect[0].left;
		int y = point.y- rect[0].top;* /

		for (int i = 0; i < 2; i++)
		{
			if (rect[i].PtInRect(point))
			{

				// 이미지 데이터 가져오기
				if(i == 1 && m_iRadio_Type == 2)
				{
					MbufGet(theApp.m_Vision.MilImage[2], theApp.m_Vision.m_ImageProcess);
				}
				else
				{
					MbufGet(theApp.m_Vision.MilImage[i], theApp.m_Vision.m_ImageProcess);
				}

				int x = (point.x - rect[i].left);
				int y = (point.y - rect[i].top) ;

				int dispX = (point.x - rect[i].left) / theApp.m_Vision.m_dZoomRate;
				int dispY = (point.y - rect[i].top) / theApp.m_Vision.m_dZoomRate;
		
				int pos = dispY * IMG_SIZE_X + dispX, offset = IMG_SIZE_X * IMG_SIZE_Y;

				// RGB 데이터 추출
				int r = theApp.m_Vision.m_ImageProcess[pos];
				int g = theApp.m_Vision.m_ImageProcess[pos + offset];
				int b = theApp.m_Vision.m_ImageProcess[pos + 2 * offset];

				// 오버레이 텍스트 생성 및 출력
				CString tmpStr;
				int index = m_list.GetCount() + 1;  // 리스트 박스의 현재 아이템 수 + 1로 인덱스 설정

				if (i == 0) {
					tmpStr.Format(L"[%d] Original: (%d, %d) R: %d, G: %d, B: %d", index, dispX, dispY, r, g, b);
				}
				else {
					tmpStr.Format(L"[%d] Processed: (%d, %d) R: %d, G: %d, B: %d", index, dispX, dispY, r, g, b);
				}

				int nIndex = m_list.AddString(tmpStr);
				m_list.SetCurSel(nIndex);
				m_list.SetTopIndex(nIndex);
				theApp.m_Overlay[i].DrawOverlayDC(false);
				theApp.m_Overlay[i].AddTextList(x, y, tmpStr, M_COLOR_GREEN, 8, 18);
				theApp.m_Overlay[i].AddCrossList(x, y, 5, 5, M_COLOR_GREEN);
				theApp.m_Overlay[i].DrawOverlayDC(true);
			}
		}

		CDialogEx::OnLButtonDown(nFlags, point);
	}*/


	void CProject07Dlg::OnLButtonDown(UINT nFlags, CPoint point)
	{
		CRect rect[2];
		GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect[0]);
		GetDlgItem(IDC_STATIC_IMAGE_2)->GetWindowRect(&rect[1]);

		ScreenToClient(&rect[0]);
		ScreenToClient(&rect[1]);

		// 이미지 영역 내의 상대적 클릭 위치 계산
		theApp.m_Vision.m_dZoomRate = DISP_IMG_RATE_X;

		/*int x = point.x- rect[0].left;
		int y = point.y- rect[0].top;*/

		for (int i = 0; i < 2; i++)
		{
			if (rect[i].PtInRect(point))
			{

				// 이미지 데이터 가져오기
				if (i == 1 && m_iRadio_Type == 2)
				{
					MbufGet(theApp.m_Vision.MilImage[2], theApp.m_Vision.m_ImageProcess);
				}
				else
				{
					MbufGet(theApp.m_Vision.MilImage[i], theApp.m_Vision.m_ImageProcess);
				}

				int x = (point.x - rect[i].left);
				int y = (point.y - rect[i].top);

				int dispX = (point.x - rect[i].left) / theApp.m_Vision.m_dZoomRate;
				int dispY = (point.y - rect[i].top) / theApp.m_Vision.m_dZoomRate;

				int pos = dispY * IMG_SIZE_X + dispX, offset = IMG_SIZE_X * IMG_SIZE_Y;

				// RGB 데이터 추출
				int Grayscale = theApp.m_Vision.m_ImageProcess[pos];

				// 오버레이 텍스트 생성 및 출력
				CString tmpStr;
				int index = m_list.GetCount() + 1;  // 리스트 박스의 현재 아이템 수 + 1로 인덱스 설정

				if (i == 0) {
					tmpStr.Format(L"[%d] Original: (%d, %d) Grayscale: %d", index, dispX, dispY, Grayscale);
				}
				else {
					tmpStr.Format(L"[%d] Processed: (%d, %d) Grayscale: %d", index, dispX, dispY, Grayscale);
				}

				int nIndex = m_list.AddString(tmpStr);
				m_list.SetCurSel(nIndex);
				m_list.SetTopIndex(nIndex);
				theApp.m_Overlay[i].DrawOverlayDC(false);
				theApp.m_Overlay[i].AddTextList(x, y, tmpStr, M_COLOR_GREEN, 8, 18);
				theApp.m_Overlay[i].AddCrossList(x, y, 5, 5, M_COLOR_GREEN);
				theApp.m_Overlay[i].DrawOverlayDC(true);
			}
		}

		CDialogEx::OnLButtonDown(nFlags, point);
	}

