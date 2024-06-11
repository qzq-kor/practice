
// MFControl2Dlg.h: 헤더 파일
//

#pragma once

#include "MyModal.h"
#include "MyModaless.h"

// CMFControl2Dlg 대화 상자
class CMFControl2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFControl2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	int m_nTimerCount;
	CListBox m_listBox;
	CSliderCtrl m_sliderCtrl;
	Mymodaless* m_pDlg;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCONTROL2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	void UpdateListBoxWithControlsState();


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedMfcbutton3();
	afx_msg void OnBnClickedMfcbutton4();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedMfcbutton5();
	afx_msg void OnStnClickedStaticTime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);




	CComboBox m_comboBox;
	BOOL m_iRadio;
	BOOL m_iRadio_2;
	BOOL m_iRadio_3;
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();

	void SetControl(int nNo, bool bCheckFlag = false);

	BOOL m_bCheck1;
	BOOL m_bCheck2;
	BOOL m_bCheck3;
	CString m_strEdit;
	CListBox m_listData;
	
	void PutListData(CString strData);

private:
	

};
