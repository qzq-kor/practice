
// Project5Dlg.h: 헤더 파일
//

#pragma once
#include "ZoomDialog.h"


// CProject5Dlg 대화 상자
class CProject5Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProject5Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	ZoomDialog* m_pDlg;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CSliderCtrl m_Slider;
	int m_Edit;
	virtual BOOL OnInitDialog();
	int m_nDispSelect;
	CPoint m_mouseClickPos;
	CPoint m_imageClickPos;
	int m_imgLeft;
	int m_imgTop;
	int m_imgRight;
	int m_imgBottom;


	bool m_bClickFlag;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedExitButton();
	afx_msg void OnChangeScreen();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);



	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
