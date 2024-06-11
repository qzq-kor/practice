#include "PCH.h"
#include "Vision.h"

#include "Project3.h"


CVision::CVision(void)
{
	hImg = NULL;
	hImgProcess = NULL;

	m_nWidth = M_NULL;

	MilApplication = M_NULL;
	MilSystem = M_NULL;
	MilDigitizer = M_NULL;

	hImg = NULL;

	for (int nBuffer = 0; nBuffer < MAX_BUFFER_CNT; nBuffer++)
	{
		MilImage[nBuffer] = M_NULL;
	}

	MilDisplay = M_NULL;
}


CVision::~CVision(void)
{
}


bool CVision::InitVB(bool fi_bMode)
{
	MIL_INT	iRealSizeX, iRealSizeY, iBandSize;
	long iBufAttriGrab = M_IMAGE + M_PROC + M_GRAB;
	long iBufAttriDisp = M_IMAGE + M_PROC + M_DISP;
	long iBufAttriProc = M_IMAGE + M_PROC + M_DISP;

	CString strDcfName, szTemp;


	MappAlloc(M_DEFAULT, &MilApplication);
	MappControl(M_ERROR, M_PRINT_ENABLE);

	if (fi_bMode)
		MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEV0, M_COMPLETE, &MilSystem);
	else
		MsysAlloc(M_SYSTEM_VGA, M_DEV0, M_COMPLETE, &MilSystem);


	if (fi_bMode)
	{
		strDcfName.Format(_T("defaultGigE.dcf"));

		MdigAlloc(MilSystem, M_DEV0, strDcfName, M_DEFAULT, &MilDigitizer);
	}



	if(MilDigitizer != M_NULL)
	{
		MdigInquire(MilDigitizer, M_SIZE_BAND, &iBandSize);
		MdigInquire(MilDigitizer, M_SIZE_X, &iRealSizeX);
		MdigInquire(MilDigitizer, M_SIZE_Y, &iRealSizeY);
		MdigControl(MilDigitizer, M_GRAB_MODE, M_ASYNCHRONOUS);
		MdigControl(MilDigitizer, M_GRAB_TIMEOUT, 1000);
	}
	else
	{
		iRealSizeX = IMG_SIZE_X;
		iRealSizeY = IMG_SIZE_Y;

		iBandSize = 3;

		iBufAttriGrab = M_IMAGE + M_PROC;
	}

	
	for (int iBufferCnt = 0; iBufferCnt < MAX_BUFFER_CNT; iBufferCnt++)
	{
		MbufAllocColor(MilSystem, iBandSize, iRealSizeX, iRealSizeY, 8 + M_UNSIGNED, iBufAttriProc, &MilImage[iBufferCnt]);

		if (MilImage[iBufferCnt])
			MbufClear(MilImage[iBufferCnt], 0x00);
		else
		{
			szTemp.Format(_T("MilImage[%d] 버퍼 생성 실패! "), iBufferCnt);
			ErrMsg(szTemp);
			return FALSE;
		}
	}

	m_Image = new unsigned char[(IMG_SIZE_X * IMG_SIZE_Y) * iBandSize];
	m_ImageProcess = new unsigned char[(IMG_SIZE_X * IMG_SIZE_Y) * iBandSize];

	return TRUE;
}

void CVision::CloseVB(void)
{
	if (m_Image)
	{
		delete m_Image;
	}
	if (m_ImageProcess)
	{
		delete m_ImageProcess;
	}


	for (int nBuffer = 0; nBuffer < MAX_BUFFER_CNT; nBuffer++)
	{
		if (MilImage[nBuffer] != M_NULL)
		{
			MbufFree(MilImage[nBuffer]);
			MilImage[nBuffer] = M_NULL;
		}
	}

	if (MilDigitizer != M_NULL)
	{
		MdigFree(MilDigitizer);
		MilDigitizer = M_NULL;
	}

	if (MilSystem != M_NULL)
	{
		MsysFree(MilSystem);
		MilSystem = M_NULL;
	}

	if (MilApplication != M_NULL)
	{
		MappFree(MilApplication);
		MilApplication = M_NULL;
	}
}


void CVision::ErrMsg(const TCHAR* fi_szMsg, int fi_nFontSize)
{
	AfxMessageBox(fi_szMsg);
}

/*
void CVision::ExtractRGB(int x, int y, int& r, int& g, int& b)
{
	int pos = y * IMG_SIZE_X + x, offset = IMG_SIZE_X * IMG_SIZE_Y;

	// 이미지 버퍼에서 RGB 값을 추출
	r = theApp.m_Vision.m_Image[pos];
	g = theApp.m_Vision.m_Image[pos + offset];
	b = theApp.m_Vision.m_Image[pos + 2 * offset];
}*/