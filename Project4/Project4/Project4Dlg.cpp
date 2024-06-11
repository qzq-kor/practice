
// Project4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project4.h"
#include "Project4Dlg.h"
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


// CProject4Dlg 대화 상자



CProject4Dlg::CProject4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT4_DIALOG, pParent)

	, m_iRadio(0)
	, m_nVal(1)
	, m_nThreshold(160)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProject4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO, m_iRadio);
	DDX_Text(pDX, IDC_EDIT_PRAMETER, m_nVal);
	DDX_Text(pDX, IDC_EDIT_PRAMETER2, m_nThreshold);

	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CProject4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO, IDC_RADIO_3, &CProject4Dlg::OnBnClickedRadio)
	ON_LBN_SELCHANGE(IDC_LIST1, &CProject4Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_LOAD_BUTTON, &CProject4Dlg::OnBnClickedLoadButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CProject4Dlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CProject4Dlg::OnBnClickedExitButton)
END_MESSAGE_MAP()


// CProject4Dlg 메시지 처리기

BOOL CProject4Dlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProject4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProject4Dlg::OnPaint()
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
HCURSOR CProject4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CProject4Dlg::OnBnClickedRadio(UINT id)
{
	switch (id)
	{
	case IDC_RADIO:
		m_iRadio = 0;
		break;
	case IDC_RADIO_1:
		m_iRadio = 1;
		break;
	case IDC_RADIO_2:
		m_iRadio = 2;
		break;
	case IDC_RADIO_3:
		m_iRadio = 3;
		break;
	default:
		break;
	}

	if (m_iRadio != -1) {
		ProcessImage(m_iRadio); // m_iRadio 값에 따라 이미지 처리
	}
}

void CProject4Dlg::ProcessImage(int m_iRadio)
{
	if (m_iRadio == 0)
	{
		MbufPut(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_Image);
	}
	else if (m_iRadio == 1)
	{
		int nOffset = IMG_SIZE_X * IMG_SIZE_Y;
		unsigned char* m_imageR, *m_imageG, *m_imageB;
		m_imageR = theApp.m_Vision.m_Image;
		m_imageG = (theApp.m_Vision.m_Image + nOffset);
		m_imageB = (theApp.m_Vision.m_Image + nOffset*2);

		// 엣지 감지 및 출력
	//	MbufGet(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_Image);
		int nPos;
		int prevPos;
		int nVal = m_nVal;


			// 간단한 차분 엣지 감지
			for (int y = 0; y < IMG_SIZE_Y; y++)
			{
				nPos = y * IMG_SIZE_X + 1;
				prevPos = nPos - 1;
				for (int x = 1; x < IMG_SIZE_X; x++)  // x = 0은 경계 처리 안함
				{

					int edgeStrength = abs(m_imageR[nPos] - m_imageR[prevPos]);
					int edgeStrength1 = abs(m_imageG[nPos] - m_imageG[prevPos]);
					int edgeStrength2 = abs(m_imageB[nPos] - m_imageB[prevPos]);


					theApp.m_Vision.m_ImageProcess[nPos] = edgeStrength * nVal;  // 엣지가 강한 곳은 흰색으로 표시
					theApp.m_Vision.m_ImageProcess[nPos + nOffset] = edgeStrength1 * nVal;
					theApp.m_Vision.m_ImageProcess[nPos + nOffset * 2] = edgeStrength2 * nVal;

					nPos++;
					prevPos++;

				}
			}
		
		// 결과 이미지 저장 및 출력
		MbufPut(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_ImageProcess);

	}

	
	// 기타 `radioId` 조건을 위한 추가 `else if` 블록을 여기에 구현할 수 있습니다.
	else if (m_iRadio == 2)
	{
		int nOffset = IMG_SIZE_X * IMG_SIZE_Y;
		unsigned char* m_imageR, * m_imageG, * m_imageB;
		m_imageR = theApp.m_Vision.m_Image;
		m_imageG = theApp.m_Vision.m_Image + nOffset;
		m_imageB = theApp.m_Vision.m_Image + nOffset * 2;

		int nVal = m_nVal;


		// Y 방향 엣지 감지
	//	MbufGet(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_Image);
		int nPos, prevPos;

		// 간단한 차분 엣지 감지를 Y 방향으로 수행
		for (int x = 0; x < IMG_SIZE_X; x++)  // 모든 열에 대해 처리
		{
			for (int y = 1; y < IMG_SIZE_Y; y++)  // 첫 행은 경계 처리 안 함
			{
				nPos = y * IMG_SIZE_X + x;
				prevPos = (y - 1) * IMG_SIZE_X + x;  // 이전 행의 같은 열

				int edgeStrength = abs(m_imageR[nPos] - m_imageR[prevPos]);
				int edgeStrength1 = abs(m_imageG[nPos] - m_imageG[prevPos]);
				int edgeStrength2 = abs(m_imageB[nPos] - m_imageB[prevPos]);

				theApp.m_Vision.m_ImageProcess[nPos] = edgeStrength * nVal;  // 엣지 강도에 따라 값 설정
				theApp.m_Vision.m_ImageProcess[nPos + nOffset] = edgeStrength1 * nVal;
				theApp.m_Vision.m_ImageProcess[nPos + nOffset * 2] = edgeStrength2 * nVal;

			}
		}

		// 결과 이미지 저장 및 출력
		MbufPut(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_ImageProcess);

	}

	else if (m_iRadio == 3)
	{
		int threshold = m_nThreshold;
		int nPos, nOffset = IMG_SIZE_X * IMG_SIZE_Y;
	
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

		MbufPut(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_ImageProcess);
	}


}

BOOL CProject4Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString str;
		int nEdit;

		if (pMsg->hwnd == GetDlgItem(IDC_EDIT_PRAMETER)->m_hWnd)
		{
			GetDlgItemText(IDC_EDIT_PRAMETER, str);
			nEdit = _ttoi(str); // CString에서 int로 변환
			m_nVal = nEdit; // 첫 번째 Edit Box에서 값 가져오기
			UpdateData(TRUE);
			return TRUE; // 이벤트 처리를 나타내며 추가 처리 방지
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_EDIT_PRAMETER2)->m_hWnd)
		{
			GetDlgItemText(IDC_EDIT_PRAMETER2, str);
			nEdit = _ttoi(str); // CString에서 int로 변환
			m_nThreshold = nEdit; // 두 번째 Edit Box에서 값을 가져오기
			UpdateData(TRUE);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CProject4Dlg::OnLbnSelchangeList1()
{
	UpdateData(TRUE);
}


void CProject4Dlg::OnBnClickedLoadButton()
{
		CFileDialog dlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.*)|*.*||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufClear(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], 0);

		MbufLoad(filePath, theApp.m_Vision.MilImage[IMAGE_ORIGINAL]);
	

		MbufGet(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_Image);
	}
}


void CProject4Dlg::OnBnClickedSaveButton()
{
	CFileDialog dlg(FALSE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("파일(*.bmp)|*.bmp||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		TCHAR filePath[MAX_PATH];
		_tcscpy_s(filePath, dlg.GetPathName().GetBuffer());

		MbufSave(filePath, theApp.m_Vision.MilImage[IMAGE_ORIGINAL]);
	}
}


void CProject4Dlg::OnBnClickedExitButton()
{
	CDialogEx::OnOK();
}

void CProject4Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	CRect rect;
	GetDlgItem(IDC_STATIC_IMAGE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	CString tmpStr;

	if (rect.PtInRect(point))
	{
		int x = point.x - rect.left;
		int y = point.y - rect.top;
		int pos = y * IMG_SIZE_X + x, offset = IMG_SIZE_X * IMG_SIZE_Y;
		MbufGet(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.m_ImageProcess);


		int r = theApp.m_Vision.m_ImageProcess[pos];
		int g = theApp.m_Vision.m_ImageProcess[pos + offset];
		int b = theApp.m_Vision.m_ImageProcess[pos + 2 * offset];
		tmpStr.Format(L"(%d, %d) %d, %d, %d", x, y, r, g, b);
		//theApp.m_Overlay[0].DrawOverlayDC(false);

		theApp.m_Overlay[0].DrawOverlayDC(false);
		theApp.m_Overlay[0].AddTextList(x, y, tmpStr, M_COLOR_GREEN, 8, 18);
		theApp.m_Overlay[0].AddCrossList(x, y, 10, 10, M_COLOR_GREEN);
		theApp.m_Overlay[0].DrawOverlayDC(true);

		CString listBoxStr;
		int index = m_list.GetCount() + 1;  // 리스트 박스의 현재 아이템 수 + 1로 인덱스 설정
		listBoxStr.Format(L"[%d] (%d, %d) R: %d, G: %d, B: %d",index, x, y, r, g, b);
	
		int nIndex = m_list.AddString(listBoxStr);
		m_list.SetCurSel(nIndex);
		m_list.SetTopIndex(nIndex);
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}
