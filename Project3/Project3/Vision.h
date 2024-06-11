#pragma once


#include "pch.h"
#include "MIL.H"
#include <algorithm>

typedef struct
{
	int nGrabCnt;

} HookDataStruct;

class CVision
{
public:

	int		m_nWidth;

	/*CPoint m_ptOffset = CPoint(0,0); // 현재 확대/축소 오프셋 위치
	
	void SetOffset(int x, int y) {
		m_ptOffset = CPoint(x, y);
	}*/

	MIL_ID		MilApplication,
		MilSystem,
		MilDigitizer,
		MilImage[MAX_BUFFER_CNT],
		MilDisplay;


	HANDLE		hImg;	
	unsigned	char* m_Image;			// 자동 검사 시 시편 위치 검색 용..
	
	HANDLE		hImgProcess;
	unsigned	char* m_ImageProcess;


	CVision(void);
	~CVision(void);

	bool	InitVB(bool fi_bMode);
	void	CloseVB(void);		

	void ErrMsg(const TCHAR* fi_szMsg, int fi_nFontSize = 10);
	void ExtractRGB(int x, int y, int& r, int& g, int& b);
};

