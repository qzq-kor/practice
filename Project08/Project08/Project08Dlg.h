
// Project08Dlg.h: 헤더 파일
//
#include "mil.h"
#pragma once


// CProject08Dlg 대화 상자
class CProject08Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProject08Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT08_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	bool m_bClickFlag;
	int m_nDispSelect;
	CPoint m_mouseClickPos;
	int m_imgLeft;
	int m_imgTop;
	int m_imgRight;
	int m_imgBottom;
	int m_dispLeft;
	int m_dispTop;
	int m_dispRight;
	int m_dispBottom;
	void UpdateImage();
	void OnButtonResizing(int nDirection);
	void OnButtonMove(int nDirection);
	void OnFindEdge();

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonMoveLeft();
	afx_msg void OnButtonMoveRight();
	afx_msg void OnButtonMoveUp();
	afx_msg void OnButtonMoveDown();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);

	CListBox m_list;
	BOOL m_iRadio;
	afx_msg void OnBnClickedRadioMove();
	afx_msg void OnBnClickedRadioSize();
	int m_nMovePixel;
};
