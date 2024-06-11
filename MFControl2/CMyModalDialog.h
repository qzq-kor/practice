#pragma once
#include "afxdialogex.h"


// CMyModalDialog 대화 상자

class CMyModalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyModalDialog)

public:
	CMyModalDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMyModalDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCONTROL2_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
