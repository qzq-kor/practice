
// MFControl2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFControl2.h"
#include "MFControl2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


enum { 	TIMER_TIME = 0, TIMER_COUNT};

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
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMFControl2Dlg 대화 상자



CMFControl2Dlg::CMFControl2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCONTROL2_DIALOG, pParent)
	, m_iRadio(FALSE)
	, m_iRadio_2(FALSE)
	, m_iRadio_3(FALSE)
	, m_bCheck1(FALSE)
	, m_bCheck2(FALSE)
	, m_bCheck3(FALSE)
	, m_strEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMFControl2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Radio(pDX, IDC_RADIO1, m_iRadio);
	DDX_Radio(pDX, IDC_RADIO5, m_iRadio_2);
	DDX_Radio(pDX, IDC_RADIO7, m_iRadio_3);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	DDX_Check(pDX, IDC_CHECK2, m_bCheck2);
	DDX_Check(pDX, IDC_CHECK3, m_bCheck3);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	DDX_Control(pDX, IDC_LIST1, m_listData);
}

BEGIN_MESSAGE_MAP(CMFControl2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO1, &CMFControl2Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFControl2Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMFControl2Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_CHECK1, &CMFControl2Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMFControl2Dlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CMFControl2Dlg::OnBnClickedCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFControl2Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CMFControl2Dlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMFControl2Dlg::OnBnClickedMfcbutton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFControl2Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CMFControl2Dlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CMFControl2Dlg::OnBnClickedMfcbutton4)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMFControl2Dlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFControl2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFControl2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFControl2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CMFControl2Dlg::OnBnClickedMfcbutton5)
	ON_STN_CLICKED(IDC_STATIC_TIME, &CMFControl2Dlg::OnStnClickedStaticTime)
	ON_BN_CLICKED(IDC_RADIO5, &CMFControl2Dlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO4, &CMFControl2Dlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO6, &CMFControl2Dlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CMFControl2Dlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CMFControl2Dlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CMFControl2Dlg::OnBnClickedRadio9)
END_MESSAGE_MAP()


// CMFControl2Dlg 메시지 처리기

BOOL CMFControl2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	CTime currentTime = CTime::GetCurrentTime();
	CString strTime = currentTime.Format("%Y-%m-%d %H:%M:%S");
	 
	SetDlgItemText(IDC_STATIC_TIME, strTime);
	SetTimer(TIMER_TIME, 1000, NULL); // 1초마다 WM_TIMER 메시지를 발생시킵니다.
	m_nTimerCount = 0;

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

	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	if (pSlider != nullptr)
	{
		pSlider->SetRange(0, 255);
	}

	m_comboBox.AddString(_T("1 선택"));
	m_comboBox.AddString(_T("2 선택"));
	m_comboBox.AddString(_T("3 선택"));

	m_comboBox.SetCurSel(0);

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}               

void CMFControl2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_TIME) // 타이머 ID 1을 확인
	{
		CTime currentTime = CTime::GetCurrentTime();
		CString strTime = currentTime.Format("%Y-%m-%d %H:%M:%S");
		SetDlgItemText(IDC_STATIC_TIME, strTime);
	}
	else if (nIDEvent == TIMER_COUNT) // 타이머 ID 1을 확인
	{
		CString strCount;
		m_nTimerCount++; // 카운트 증가
		strCount.Format(_T("%d"), m_nTimerCount); // 카운트를 문자열로 변환
		PutListData(strCount);
	}

	CDialogEx::OnTimer(nIDEvent); // 기본 타이머 이벤트 처리기 호출
}

void CMFControl2Dlg::PutListData(CString strData)
{
	int nCnt = m_listData.GetCount();

	if (nCnt > 5000)
	{
		m_listData.ResetContent();
		nCnt = 0;
	}

	m_listData.AddString(strData); // 리스트박스에 카운트 출력
	m_listData.SetCurSel(nCnt);
}

void CMFControl2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFControl2Dlg::OnPaint()
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
HCURSOR CMFControl2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFControl2Dlg::OnBnClickedRadio1()
{
	SetControl(0);
}


void CMFControl2Dlg::OnBnClickedRadio2()
{
	SetControl(1);
}


void CMFControl2Dlg::OnBnClickedRadio3()
{
	SetControl(2);
}


void CMFControl2Dlg::OnBnClickedCheck1()
{
	SetControl(0, true);
}


void CMFControl2Dlg::OnBnClickedCheck2()
{
	SetControl(1, true);
}


void CMFControl2Dlg::OnBnClickedCheck3()
{
	SetControl(2, true);
}


void CMFControl2Dlg::OnCbnSelchangeCombo1()
{
	int nIndex = m_comboBox.GetCurSel(); // m_comboBox는 콤보 박스 컨트롤 변수입니다.

	SetControl(nIndex, false);
}


void CMFControl2Dlg::OnBnClickedMfcbutton2()
{
	MyModal dlg;
	dlg.DoModal(); // 모달 대화 상자를 띄웁니다.
}


void CMFControl2Dlg::OnBnClickedMfcbutton1()
{
	if (m_pDlg == NULL)
	{
		m_pDlg = new Mymodaless(this);
		m_pDlg->Create(IDD_MODALESS_DIALOG, this);
		m_pDlg->ShowWindow(SW_SHOW);
	}
}


void CMFControl2Dlg::OnLbnSelchangeList1()
{
	UpdateData(TRUE); // 체크 박스의 상태를 멤버 변수에 업데이트
	m_listData.AddString(L"1 선택"); // 
	m_listData.AddString(L"2 선택"); //
	m_listData.AddString(L"3 선택"); //
	UpdateData(FALSE); // 멤버 변수의 최신 상태를 UI에 반영
}


void CMFControl2Dlg::OnBnClickedMfcbutton3()
{
	SetTimer(TIMER_COUNT, 100, NULL); // 0.1초 간격으로 타이머 설정
}


void CMFControl2Dlg::OnBnClickedMfcbutton4()
{
	KillTimer(TIMER_COUNT); // 타이머 정지
}


void CMFControl2Dlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CMFControl2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// 슬라이더 컨트롤의 포인터를 얻습니다.
	CSliderCtrl* pSlider = reinterpret_cast<CSliderCtrl*>(pScrollBar);

	// 이 이벤트가 슬라이더 컨트롤로부터 발생했는지 확인합니다.
	if (pSlider->GetDlgCtrlID() == IDC_SLIDER1) // IDC_SLIDER1은 슬라이더 컨트롤의 ID입니다.
	{
		// 슬라이더의 현재 위치(값)를 가져옵니다.
		int nValue = pSlider->GetPos();

		// 에디트 컨트롤에 값을 표시합니다.
		CString strValue;
		strValue.Format(_T("%d"), nValue);
		SetDlgItemText(IDC_EDIT1, strValue); // IDC_EDIT1은 에디트 컨트롤의 ID입니다.
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMFControl2Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFControl2Dlg::OnBnClickedButton1() // 데이터 불러오기 함수
{
	CStdioFile file;
	if (!file.Open(_T("log.txt"), CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox(_T("파일을 열 수 없습니다."));
		return;
	}

	CString strLine, strKey, strValue;
	while (file.ReadString(strLine))
	{
		int pos = strLine.Find(':');
		if (pos != -1)
		{
			strKey = strLine.Left(pos);
			strValue = strLine.Mid(pos + 1);

			if (strKey == _T("SliderPosition"))
			{
				int nValue = _ttoi(strValue);
				CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1); 
				if (pSlider) pSlider->SetPos(nValue);
			}
			else if (strKey == _T("EditContent"))
			{
				m_strEdit = strValue;
			}
			else if (strKey == _T("CheckBoxes"))
			{
				int b1, b2, b3;
				// CString에서 C 스타일 문자열을 얻어 사용합니다.
				_stscanf_s(strValue, _T("%d,%d,%d"), &b1, &b2, &b3);
				m_bCheck1 = b1;
				m_bCheck2 = b2;
				m_bCheck3 = b3;
			}
			else if (strKey == _T("RadioButtons"))
			{
				int r1, r2, r3;
				// CString에서 C 스타일 문자열을 얻어 사용합니다.
				_stscanf_s(strValue, _T("%d,%d,%d"), &r1, &r2, &r3);
				m_iRadio = r1;
				m_iRadio_2 = r2;
				m_iRadio_3 = r3;
			}
			else if (strKey == _T("ComboBoxIndex"))
			{
				int nIndex = _ttoi(strValue);
				m_comboBox.SetCurSel(nIndex);
			}
			else if (strKey == _T("ListBoxItem"))
			{
				m_listData.AddString(strValue);
			}
		}
	}

	file.Close();
	UpdateData(FALSE); // 컨트롤에 데이터 업데이트
}


void CMFControl2Dlg::OnBnClickedButton2() // 데이터 저장 함수
{
	UpdateData(TRUE);

	CStdioFile file;
	CFileException e;

	if (!file.Open(_T("log.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return;
	}

	// 슬라이더 위치 저장
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int nSliderValue = pSlider ? pSlider->GetPos() : 0;
	CString strLine;
	strLine.Format(_T("SliderPosition:%d\n"), nSliderValue);
	file.WriteString(strLine);

	// 에디트박스 내용 저장
	strLine.Format(_T("EditContent:%s\n"), m_strEdit);
	file.WriteString(strLine);

	// 체크박스 상태 저장
	strLine.Format(_T("CheckBoxes:%d,%d,%d\n"), m_bCheck1, m_bCheck2, m_bCheck3);
	file.WriteString(strLine);

	// 라디오 버튼 상태 저장
	strLine.Format(_T("RadioButtons:%d,%d,%d\n"), m_iRadio, m_iRadio_2, m_iRadio_3);
	file.WriteString(strLine);

	// 콤보박스 선택 인덱스 저장
	int comboIndex = m_comboBox.GetCurSel();
	strLine.Format(_T("ComboBoxIndex:%d\n"), comboIndex);
	file.WriteString(strLine);

	// 리스트박스 항목 저장
	int nCount = m_listData.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CString strItem;
		m_listData.GetText(i, strItem);
		strLine.Format(_T("ListBoxItem:%s\n"), strItem);
		file.WriteString(strLine);
	}

	file.Close();
}


void CMFControl2Dlg::OnBnClickedMfcbutton5()
{
	OnBnClickedButton2(); // 데이터 저장

	// 프로그램 종료
	PostMessage(WM_CLOSE);
}


void CMFControl2Dlg::OnStnClickedStaticTime()
{
	
	SetTimer(TIMER_TIME, 1000, NULL); // 1초마다 WM_TIMER 메시지를 발생시킵니다.

}


void CMFControl2Dlg::OnBnClickedRadio5()
{
	UpdateData(TRUE);
}


void CMFControl2Dlg::OnBnClickedRadio4()
{
	UpdateData(TRUE);
}


void CMFControl2Dlg::OnBnClickedRadio6()
{
	UpdateData(TRUE);
}


void CMFControl2Dlg::OnBnClickedRadio7()
{
	UpdateData(TRUE);
}


void CMFControl2Dlg::OnBnClickedRadio8()
{
	UpdateData(TRUE);
}


void CMFControl2Dlg::OnBnClickedRadio9()
{
	UpdateData(TRUE);
}



void CMFControl2Dlg::SetControl(int nNo, bool bCheckFlag)
{
	
	UpdateData(true);


	CString str;
	str.Format(L"%d_선택", nNo + 1);
	m_listData.AddString(str);

	
	if (bCheckFlag == false)
	{
		if (nNo == 0)
		{
			m_bCheck1 = m_bCheck1 ? FALSE : TRUE;
		}
		else if (nNo == 1)
		{
			m_bCheck2 = m_bCheck2 ? FALSE : TRUE;
		}
		else if (nNo == 2)
		{
			m_bCheck3 = m_bCheck3 ? FALSE : TRUE;
		}
	}

	m_iRadio = nNo;
	m_iRadio_2 = nNo;
	m_iRadio_3 = nNo;
	m_comboBox.SetCurSel(nNo);





	UpdateData(FALSE);
}