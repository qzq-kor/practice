#pragma once


#define M_PI       3.14159265358979323846   // pi




//#define		ON_LINE_VISION


#define		MAX_DEFECT_CNT			500
#define		MAX_BLOB_CNT			MAX_DEFECT_CNT

#define		MAX_GRAB_CNT			10


#define		WINDOW_SIZE_X			2000
#define		WINDOW_SIZE_Y			1500

#define		IMG_SIZE_X				2448
#define		IMG_SIZE_Y				2048

#define		DISP_SIZE_X				1024	// Main 화면 카메라 Display 크기
#define		DISP_SIZE_Y				856

#define		DISP_ZOOM_SIZE_X				512	// ZOOM 화면 카메라 Display 크기
#define		DISP_ZOOM_SIZE_Y				428

#define		DISP_IMG_RATE_X			(double)DISP_SIZE_X / (double)IMG_SIZE_X
#define		DISP_IMG_RATE_Y			(double)DISP_SIZE_Y / (double)IMG_SIZE_Y

#define		DISP_IMG_ZOOM_RATE_X			(double)DISP_ZOOM_SIZE_X / (double)IMG_SIZE_X
#define		DISP_IMG_ZOOM_RATE_Y			(double)DISP_ZOOM_SIZE_Y / (double)IMG_SIZE_Y

#define		PARAMETER_SIZE			64
#define		MESSAGE_SIZE			256
#define		PATH_MESSAGE_SIZE		MESSAGE_SIZE * 4


enum Disp_Type { DISP_CAM_0 = 0, DISP_CAM_ZOOM, DISP_CAM_1, DISP_CAM_2, MAX_DISP_CNT };

enum class INSP_DIR { LEFT = 0, RIGHT, TOP, BOTTOM, nCnt };

enum Select_Image
{
	IMAGE_ORIGINAL = 0, IMAGE_ZOOM, IMAGE_SHARP , IMAGE_SMOOTH, IMAGE_MAIN, MAX_BUFFER_CNT
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