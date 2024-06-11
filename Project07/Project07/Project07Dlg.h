
// Project07Dlg.h: 헤더 파일
//

#pragma once


// CProject07Dlg 대화 상자
class CProject07Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProject07Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT07_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수

	void OnOK() { return; }
	void OnCancel() { return; }


	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ProcessImage(int radioId);
	void ApplySharpeningFilter();
	void ApplySmoothingFilter();

	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedRadioOriginal();
	afx_msg void OnBnClickedStaticSharp();
	afx_msg void OnBnClickedRadioSmooth();
	afx_msg void OnBnClickedButtonSave();
	BOOL m_iRadio_Type;
	int m_nVal;
	int GetRadioType() const;
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	CListBox m_list;
};
