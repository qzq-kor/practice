﻿#pragma once


#include "pch.h"
#define NOMINMAX
#include <windows.h>
#include <algorithm>


typedef struct
{
	int nGrabCnt;

} HookDataStruct;

class CVision
{
public:

	int		m_nWidth;

	int m_nCamNo;
	int m_nType;

	/*CPoint m_ptOffset = CPoint(0,0); // 현재 확대/축소 오프셋 위치
	
	void SetOffset(int x, int y) {
		m_ptOffset = CPoint(x, y);
	}*/

	MIL_ID		MilApplication,
		MilSystem,
		MilDigitizer,
		MilImage[MAX_BUFFER_CNT],
		MilDisplay[MAX_DISP_CNT],
		MilImageDisp[MAX_DISP_CNT],
		MilImageGrab[MAX_GRAB_CNT],
		MilSearchContext,      // 검색 컨텍스트
		MilSearchResult,
		MilImageZoom[MAX_BUFFER_CNT];


	HANDLE		hImg;
	unsigned	char* m_Image;		

	HANDLE		hImgGray;
	unsigned	char* m_ImageGray;		

	HANDLE		hImgProcess;
	unsigned	char* m_ImageProcess;

	HANDLE		hImgEdge;
	unsigned	char* m_ImageEdge;

	HookDataStruct  UserHookData;


	CVision(void);
	~CVision(void);

	bool	InitVB(bool fi_bMode);
	void	CloseVB(void);		

	void ErrMsg(const TCHAR* fi_szMsg, int fi_nFontSize = 10);
	void Select_Image(int ImageNumber, int SelectScreen);

	double m_dZoomRate;
	int m_nNewBufW, m_nNewBufH;
	CPoint m_ZoomPoint;

	void GrabProcessStart(int fi_InspNo);

	void InitVision(MIL_ID MilSystem); // 시스템 초기화 함수
	void DefineModel();                // 모델을 정의하는 함수
	void PreprocessModel();            // 모델 전처리 함수
	void FindModel();                  // 모델을 찾는 함수
};
