// Mymodaless.cpp: 구현 파일
//

#include "pch.h"
#include "MFControl2.h"
#include "afxdialogex.h"
#include "Mymodaless.h"


// Mymodaless 대화 상자

IMPLEMENT_DYNAMIC(Mymodaless, CDialogEx)

Mymodaless::Mymodaless(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODALESS_DIALOG, pParent)
{

}

Mymodaless::~Mymodaless()
{
}

void Mymodaless::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Mymodaless, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Mymodaless::OnBnClickedCancel)
END_MESSAGE_MAP()


// Mymodaless 메시지 처리기


void Mymodaless::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


BOOL Mymodaless::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
