#pragma once
#include "afxdialogex.h"


// MyModal 대화 상자

class MyModal : public CDialogEx
{
	DECLARE_DYNAMIC(MyModal)

public:
	MyModal(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MyModal();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODAL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
