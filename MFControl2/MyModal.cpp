// MyModal.cpp: 구현 파일
//

#include "pch.h"
#include "MFControl2.h"
#include "afxdialogex.h"
#include "MyModal.h"


// MyModal 대화 상자

IMPLEMENT_DYNAMIC(MyModal, CDialogEx)

MyModal::MyModal(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODAL_DIALOG, pParent)
{

}

MyModal::~MyModal()
{
}

void MyModal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyModal, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &MyModal::OnBnClickedCancel)
END_MESSAGE_MAP()


// MyModal 메시지 처리기


void MyModal::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
