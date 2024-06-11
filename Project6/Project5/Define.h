#pragma once


#define M_PI       3.14159265358979323846   // pi




//#define		ON_LINE_VISION


#define		MAX_DEFECT_CNT			500
#define		MAX_BLOB_CNT			MAX_DEFECT_CNT

#define		MAX_GRAB_CNT			10

#define		WINDOW_SIZE_X			2560
#define		WINDOW_SIZE_Y			1440

#define		IMG_SIZE_X				1280
#define		IMG_SIZE_Y				1024

#define		DISP_SIZE_X				1024	// Main 화면 카메라 Display 크기
#define		DISP_SIZE_Y				768

#define		DISP_SELECT_SIZE_X		512	// SELECT 화면 카메라 Display 크기
#define		DISP_SELECT_SIZE_Y		384

#define		DISP_ZOOM_SIZE_X		640	// ZOOM Dialog 화면 카메라 Display 크기
#define		DISP_ZOOM_SIZE_X		480

#define		DISP_IMG_RATE_X			(double)DISP_SIZE_X / (double)IMG_SIZE_X
#define		DISP_IMG_RATE_Y			(double)DISP_SIZE_Y / (double)IMG_SIZE_Y

#define		DISP2_IMG_RATE_X			(double)DISP_SELECT_SIZE_X / (double)IMG_SIZE_X
#define		DISP2_IMG_RATE_Y			(double)DISP_SELECT_SIZE_Y / (double)IMG_SIZE_Y


#define		PARAMETER_SIZE			64
#define		MESSAGE_SIZE			256
#define		PATH_MESSAGE_SIZE		MESSAGE_SIZE * 4


enum Disp_Type { DISP_CAM_0 = 0, DISP_CAM_1, DISP_CAM_2, DISP_CAM_ZOOM, MAX_DISP_CNT };

enum class INSP_DIR { LEFT = 0, RIGHT, TOP, BOTTOM, nCnt };

enum Select_Image
{
	IMAGE_FIRST = 0, IMAGE_SECOND , IMAGE_MAIN, IMAGE_EDGE, IMAGE_ZOOM, MAX_BUFFER_CNT
};


class CDPoint
{
public:
	double x, y;
	CDPoint()
	{
		x = y = 0.0;
	}
	CDPoint(double a, double b)
	{
		x = a;
		y = b;
	}
};