﻿
// Project07.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//
#include "resource.h"		// 주 기호입니다.
#include "Vision.h"
#include "Overlay.h"
#include "Project07Dlg.h"


#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CProject07App:
// 이 클래스의 구현에 대해서는 Project07.cpp을(를) 참조하세요.
//

class CProject07App : public CWinApp
{
public:
	CProject07App();

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();  // 종료 메서드 오버라이드

// 구현입니다.

	CVision m_Vision;
	COverlay m_Overlay[MAX_DISP_CNT];
	DECLARE_MESSAGE_MAP()
};

extern CProject07App theApp;
