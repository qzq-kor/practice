

namespace define_List
{
    enum ImageIndex { Img_Org = 0, Img_Proc, Img_Bin, Img_Temp, Img_Cnt };
    public struct RECT
    {
        public int Left;
        public int Top;
        public int Right;
        public int Bottom;
    }

    public static class Def
    {
        public const int mainFormSizeX = 1900;
        public const int mainFormSizeY = 1060;

        public const int subImageCnt = 10;
        public const int subImageGap = 5;
        public const int subImageSizeX = 120;
        public const int subImageSizeY = 95;

        public const int imgSizeX = 2448;
        public const int imgSizeY = 2048;

        public const int imgDispSizeX = 1326;
        public const int imgDispSizeY = 995;

        public const double IMG_ZOOM_RATE = (double)imgDispSizeX / imgSizeX;


        public const int MAX_PIXEL_CNT = 500;
        public const int MAX_LINE_CNT = 100;
        public const int MAX_BOX_CNT = 100;
        public const int MAX_CROSS_CNT = 10000;
        public const int MAX_CIRCLE_CNT = 100;
        public const int MAX_TEXT_CNT = 100;
        public const string strDcfPath = "C:\\Vision\\DCF\\Default.dcf";
    }
}

