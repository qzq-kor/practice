
// Project3.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "Vision.h"
#include "Overlay.h"
#include "Project3Dlg.h"

// CProject3App:
// 이 클래스의 구현에 대해서는 Project3.cpp을(를) 참조하세요.
//

class CProject3App : public CWinApp
{
public:
	CProject3App();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	CProject3Dlg* m_pMainWnd;

	CVision m_Vision;
	COverlay m_Overlay[MAX_DISP_CNT];
	DECLARE_MESSAGE_MAP()
};

extern CProject3App theApp;
