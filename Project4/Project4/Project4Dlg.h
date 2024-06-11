
// Project4Dlg.h: 헤더 파일
//

#pragma once


// CProject4Dlg 대화 상자
class CProject4Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProject4Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void ProcessImage(int radioId);
	
	afx_msg void OnEnChangeEditPrameter();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedLoadButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedExitButton();
	afx_msg void OnBnClickedRadio(UINT id);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int GetEditValue();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);

	int m_iRadio;

	

	int m_nVal;
	int m_nThreshold;
	CListBox m_list;
};
