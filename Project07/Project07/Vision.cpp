#include "PCH.h"
#include "Vision.h"

#include "Project07.h"


MIL_INT MFTYPE ProcGrab(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr)
{
	HookDataStruct* UserHookDataPtr = (HookDataStruct*)HookDataPtr;

	int nGrabCnt = UserHookDataPtr->nGrabCnt;
	int nCurCnt = (nGrabCnt - 1) % MAX_GRAB_CNT;
	MIL_ID ModifiedBufferId;
	MdigGetHookInfo(HookId, M_MODIFIED_BUFFER + M_BUFFER_ID, &ModifiedBufferId);

	CProject07Dlg* pDlg = (CProject07Dlg*)theApp.m_pMainWnd;
	if (!pDlg)
		return -1;  

	int radioType = pDlg->GetRadioType();  

		MbufCopy(theApp.m_Vision.MilImageGrab[UserHookDataPtr->nGrabCnt % MAX_GRAB_CNT], theApp.m_Vision.MilImage[IMAGE_ORIGINAL]);

		MimResize(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.MilImageDisp[DISP_CAM_0], (MIL_DOUBLE)DISP_IMG_RATE_X, (MIL_DOUBLE)DISP_IMG_RATE_X, M_DEFAULT);
		
		if (radioType == 0){
			MimResize(theApp.m_Vision.MilImage[IMAGE_ORIGINAL], theApp.m_Vision.MilImageDisp[DISP_CAM_1],(MIL_DOUBLE)DISP_IMG_RATE_X, (MIL_DOUBLE)DISP_IMG_RATE_X,M_DEFAULT);
		}
		else if (radioType == 1) {
			pDlg->ProcessImage(radioType);  // 샤프닝 처리
		
			MimResize(theApp.m_Vision.MilImage[IMAGE_SHARP], theApp.m_Vision.MilImageDisp[DISP_CAM_1], (MIL_DOUBLE)DISP_IMG_RATE_X, (MIL_DOUBLE)DISP_IMG_RATE_X, M_DEFAULT);
		}
		else if (radioType == 2) {
			pDlg->ProcessImage(radioType);  // 스무딩 처리
			MimResize(theApp.m_Vision.MilImage[IMAGE_SMOOTH], theApp.m_Vision.MilImageDisp[DISP_CAM_1], (MIL_DOUBLE)DISP_IMG_RATE_X, (MIL_DOUBLE)DISP_IMG_RATE_X, M_DEFAULT);
		}

	theApp.m_Overlay[0].DrawOverlayDC(true);
	theApp.m_Overlay[1].DrawOverlayDC(true);

	UserHookDataPtr->nGrabCnt++;

	return 0;
}

CVision::CVision(void)
{
	hImg = NULL;
	hImgProcess = NULL;
	hImgGray = NULL;

	m_dZoomRate = 1.;
	m_nNewBufW = IMG_SIZE_X;
	m_nNewBufH = IMG_SIZE_Y;

	m_ZoomPoint = CPoint(0, 0);


	m_nWidth = M_NULL;

	MilApplication = M_NULL;
	MilSystem = M_NULL;
	MilDigitizer = M_NULL;

	for (int nGrab = 0; nGrab < MAX_GRAB_CNT; nGrab++)
	{
		MilImageGrab[nGrab] = M_NULL;
	}

	for (int nBuffer = 0; nBuffer < MAX_BUFFER_CNT; nBuffer++)
	{
		MilImage[nBuffer] = M_NULL;
	}


	for (int nDisp = 0; nDisp < MAX_DISP_CNT; nDisp++)
	{
		MilImageDisp[nDisp] = M_NULL;
		MilDisplay[nDisp] = M_NULL;
		MilImageZoom[nDisp] = M_NULL;
	}
}


CVision::~CVision(void)
{
}

void CVision::GrabProcessStart(int fi_InspNo)
{
	if (fi_InspNo == FALSE)
		MdigProcess(MilDigitizer, MilImageGrab, MAX_GRAB_CNT, M_STOP, M_DEFAULT, ProcGrab, &UserHookData);
	else
		MdigProcess(MilDigitizer, MilImageGrab, MAX_GRAB_CNT, M_START, M_DEFAULT, ProcGrab, &UserHookData);
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
		strDcfName.Format(_T("C:\\Temp\\defaultGigE.dcf"));

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

		iBufAttriGrab = M_IMAGE + M_PROC + M_GRAB;
	}
	iBandSize = 1;

	
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

	for (int iDispCnt = 0; iDispCnt < MAX_DISP_CNT; iDispCnt++)
	{
		MbufAllocColor(MilSystem, iBandSize, DISP_SIZE_X, DISP_SIZE_Y, 8 + M_UNSIGNED, iBufAttriDisp, &MilImageDisp[iDispCnt]);
		if (MilImageDisp[iDispCnt])
		{
			MbufClear(MilImageDisp[iDispCnt], 0x00);
		}
		else
		{
			ErrMsg(_T("MilImageDisplay[%d] 버퍼 생성 실패!"), iDispCnt);
			return FALSE;
		}

		MbufAllocColor(MilSystem, iBandSize, iRealSizeX, iRealSizeY, 8 + M_UNSIGNED, iBufAttriProc, &MilImageZoom[iDispCnt]);
		if (MilImageZoom[iDispCnt] == M_NULL)
		{
			AfxMessageBox(_T("MilImageZoom[%d] 버퍼 생성 실패!"), iDispCnt);
			return FALSE;
		}
	}
	
	for (int iGrabCnt = 0; iGrabCnt < MAX_GRAB_CNT; iGrabCnt++)
	{
		MbufAllocColor(MilSystem, iBandSize, iRealSizeX, iRealSizeY, 8 + M_UNSIGNED, iBufAttriGrab, &MilImageGrab[iGrabCnt]);
		if (MilImageGrab[iGrabCnt])
			MbufClear(MilImageGrab[iGrabCnt], 0x00);
		else
		{
			szTemp.Format(_T("MilImageGrab[%d] 버퍼 생성 실패! "), iGrabCnt);
			ErrMsg(szTemp);
			return FALSE;
		}
	}


	hImg = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (IMG_SIZE_X * IMG_SIZE_Y) * iBandSize);
	if (hImg)
	{
		m_Image = (unsigned char*)GlobalLock(hImg);
		memset(theApp.m_Vision.m_Image, 0x0, IMG_SIZE_X * IMG_SIZE_Y * iBandSize);
	}
	else
	{
		szTemp.Format(_T("라인 카메라 검사 메모리 할당 실패!"));
		ErrMsg(szTemp);
		return FALSE;
	}

	hImgProcess = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (IMG_SIZE_X * IMG_SIZE_Y) * iBandSize);
	if (hImgProcess)
	{
		m_ImageProcess = (unsigned char*)GlobalLock(hImgProcess);
		memset(theApp.m_Vision.m_ImageProcess, 0x00, IMG_SIZE_X * IMG_SIZE_Y * iBandSize);
	}

	hImgGray = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (IMG_SIZE_X * IMG_SIZE_Y) * iBandSize);
	if (hImgGray)
	{
		m_ImageGray= (unsigned char*)GlobalLock(hImgGray);
		memset(theApp.m_Vision.m_ImageGray, 0x00, IMG_SIZE_X * IMG_SIZE_Y * iBandSize);
	}
	hImgEdge = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (IMG_SIZE_X * IMG_SIZE_Y) * iBandSize);
	if (hImgEdge)
	{
		m_ImageEdge = (unsigned char*)GlobalLock(hImgEdge);
		memset(theApp.m_Vision.m_ImageEdge, 0x00, IMG_SIZE_X * IMG_SIZE_Y * iBandSize);
	}


	UserHookData.nGrabCnt = 0;

	m_dZoomRate = 1;

	m_Image = new unsigned char[(IMG_SIZE_X * IMG_SIZE_Y) * iBandSize];
	m_ImageGray = new unsigned char[(IMG_SIZE_X * IMG_SIZE_Y) * iBandSize];
	m_ImageProcess = new unsigned char[(IMG_SIZE_X * IMG_SIZE_Y) * iBandSize];
	m_ImageEdge = new unsigned char[(IMG_SIZE_X * IMG_SIZE_Y) * iBandSize];


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
	if (m_ImageGray)
	{
		delete m_ImageGray;
	}
	if (m_ImageEdge)
	{
		delete m_ImageEdge;
	}

	for (int nGrab = 0; nGrab < MAX_GRAB_CNT; nGrab++)
	{
		if (MilImageGrab[nGrab] != M_NULL)
		{
			MbufFree(MilImageGrab[nGrab]);
			MilImageGrab[nGrab] = M_NULL;
		}
	}

	for (int nBuffer = 0; nBuffer < MAX_BUFFER_CNT; nBuffer++)
	{
		if (MilImage[nBuffer] != M_NULL)
		{
			MbufFree(MilImage[nBuffer]);
			MilImage[nBuffer] = M_NULL;
		}
	}

	for (int nDisp = 0; nDisp < MAX_DISP_CNT; nDisp++)
	{
		if (MilImageDisp[nDisp] != M_NULL)
		{
			MbufFree(MilImageDisp[nDisp]);
			MilImageDisp[nDisp] = M_NULL;
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


void CVision::Select_Image(int ImageNumber, int SelectScreen)
{
	MimResize(MilImage[ImageNumber], MilImageDisp[SelectScreen], DISP_IMG_RATE_X, DISP_IMG_RATE_Y, M_DEFAULT);
}

