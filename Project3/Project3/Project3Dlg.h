
// Project3Dlg.h: 헤더 파일
//

#pragma once


// CProject3Dlg 대화 상자
class CProject3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProject3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT3_DIALOG };
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

	int m_nDispSelect;
	int m_Edit;
	bool m_bClickFlag;
	int m_itemCounter = 0; // 리스트박스 항목 번호를 추적하는 카운터

	CListBox m_list;
	CPoint m_mouseClickPos;
	CPoint m_imageClickPos;
	CSliderCtrl m_Slider;

	void OnBinarize();

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBinarizeSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStnClickedStaticImage();
};
