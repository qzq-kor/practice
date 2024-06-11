#pragma once
#include "afxdialogex.h"


// Mymodaless 대화 상자

class Mymodaless : public CDialogEx
{
	DECLARE_DYNAMIC(Mymodaless)

public:
	Mymodaless(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Mymodaless();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODALESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
