using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using define_List;
using Matrox.MatroxImagingLibrary;
using VisionProject;

namespace namespace_Overlay
{
    public class CDrawPixel
    {
        public int cnt;
        public Point[] p = new Point[Def.MAX_PIXEL_CNT];
        public double[] c = new double[Def.MAX_PIXEL_CNT];
    };

    public class CDrawLine
    {
        public int cnt;
        public Point[,] p = new Point[Def.MAX_LINE_CNT, 2];
        public double[] c = new double[Def.MAX_LINE_CNT];
    };

    public class CDrawBox
    {
        public int cnt;
        public Rectangle[] r = new Rectangle[Def.MAX_BOX_CNT];
        public double[] c = new double[Def.MAX_BOX_CNT];
    };

    public class CDrawCircle
    {
        public int cnt;
        public Rectangle[] r = new Rectangle[Def.MAX_CIRCLE_CNT];
        public double[] c = new double[Def.MAX_CIRCLE_CNT];
    };

    public class CDrawCross
    {
        public int cnt;
        public Point[] p = new Point[Def.MAX_CROSS_CNT];
        public double[] c = new double[Def.MAX_CROSS_CNT];
        public int[] w = new int[Def.MAX_CROSS_CNT];
    };

    public class CDrawText
    {
        public int cnt;
        public Point[] p = new Point[Def.MAX_TEXT_CNT];
        public double[] c = new double[Def.MAX_TEXT_CNT];
        public string[] str = new string[Def.MAX_TEXT_CNT];
    };


    public class Overlay
    {
        CDrawPixel  pixelList;
        CDrawLine   lineList;
        CDrawBox    boxList;
        CDrawCircle circleList;
        CDrawCross  crossList;
        CDrawText   textList;


        public MIL_ID MilSystem;
        public MIL_ID MilDisplay;
        public MIL_ID MilOverlayImage;
        public MIL_INT TransColor;

        MIL_ID MilGraContext;

        double m_dZoom;
        int _offsetX, _offsetY;
        int nSizeX, nSizeY;

        public Overlay()
        {
            pixelList = new CDrawPixel();
            lineList = new CDrawLine();
            boxList = new CDrawBox();
            circleList = new CDrawCircle();
            crossList = new CDrawCross();
            textList = new CDrawText();

            MilSystem = MIL.M_NULL;
            MilDisplay = MIL.M_NULL;
            MilOverlayImage = MIL.M_NULL;

            m_dZoom = (double)Def.imgDispSizeX / (double)Def.imgSizeX;
            _offsetX = _offsetY = 0;
            nSizeX = 640;
            nSizeY = 480;
        }

        public void Init(MIL_ID dispImage, Control control, bool bDispZoomFlag = false)
        {
            MIL.MbufInquire(dispImage, MIL.M_OWNER_SYSTEM, ref MilSystem);

            MilDisplay = MIL.M_NULL;
            MilOverlayImage = MIL.M_NULL;

            MIL.MdispAlloc(MilSystem, MIL.M_DEFAULT, "M_DEFAULT", MIL.M_DEFAULT, ref MilDisplay);
            MIL.MdispSelectWindow(MilDisplay, dispImage, control.Handle); //디스플레이버퍼와 픽쳐 컨트롤 연결

            nSizeX = control.Width;
            nSizeY = control.Height;

            if (bDispZoomFlag == true)
            {
                double dRateX = (double)nSizeX / Def.imgSizeX;
                double dRateY = (double)nSizeY / Def.imgSizeY;

                MIL.MdispZoom(MilDisplay, dRateX, dRateY);
            }

            MilGraContext = MIL.MgraAlloc(MilSystem, MIL.M_NULL);
            MIL.MgraControl(MilGraContext, MIL.M_BACKGROUND_MODE, MIL.M_TRANSPARENT);

            m_dZoom = (double)Def.imgDispSizeX / (double)Def.imgSizeX;
            _offsetX = _offsetY = 0;

            if (MilDisplay != MIL.M_NULL)
            {
                MIL.MdispControl(MilDisplay, MIL.M_MOUSE_USE, MIL.M_DEFAULT);
                MIL.MdispControl(MilDisplay, MIL.M_MOUSE_CURSOR_CHANGE, MIL.M_DISABLE);

                MIL.MdispControl(MilDisplay, MIL.M_OVERLAY_SHOW, MIL.M_ENABLE);
                MIL.MdispControl(MilDisplay, MIL.M_OVERLAY, MIL.M_ENABLE);
                MIL.MdispInquire(MilDisplay, MIL.M_OVERLAY_ID, ref MilOverlayImage);
                MIL.MdispInquire(MilDisplay, MIL.M_TRANSPARENT_COLOR, ref TransColor);

                MIL.MbufClear(MilOverlayImage, TransColor);
                MIL.MgraControl(MIL.M_DEFAULT, MIL.M_BACKGROUND_MODE, MIL.M_TRANSPARENT);

                MIL.MbufControl(MilOverlayImage, MIL.M_DC_ALLOC, MIL.M_DEFAULT);
                MIL.MbufControl(MilOverlayImage, MIL.M_MODIFIED, MIL.M_DEFAULT);
            }
        }

        public Overlay(MIL_ID dispImage, MIL_WINDOW_HANDLE wHandle)
        {
            pixelList = new CDrawPixel();
            lineList = new CDrawLine();
            boxList = new CDrawBox();
            circleList = new CDrawCircle();
            crossList = new CDrawCross();
            textList = new CDrawText();

            MilDisplay = MIL.M_NULL;
            MilOverlayImage = MIL.M_NULL;

            MIL.MbufInquire(dispImage, MIL.M_OWNER_SYSTEM, ref MilSystem);

            MIL.MdispAlloc(MilSystem, MIL.M_DEFAULT, "M_DEFAULT", MIL.M_DEFAULT, ref MilDisplay);
            MIL.MdispSelectWindow(MilDisplay, dispImage, wHandle); //디스플레이버퍼와 픽쳐 컨트롤 연결

            MilGraContext = MIL.MgraAlloc(MilSystem, MIL.M_NULL);
            MIL.MgraControl(MilGraContext, MIL.M_BACKGROUND_MODE, MIL.M_TRANSPARENT);


            m_dZoom = (double)Def.imgDispSizeX / (double)Def.imgSizeX;
            _offsetX = _offsetY = 0;

            if (MilDisplay != MIL.M_NULL)
            {
                MIL.MdispControl(MilDisplay, MIL.M_MOUSE_USE, MIL.M_DEFAULT);
                MIL.MdispControl(MilDisplay, MIL.M_MOUSE_CURSOR_CHANGE, MIL.M_DISABLE);

                MIL.MdispControl(MilDisplay, MIL.M_OVERLAY_SHOW, MIL.M_ENABLE);
                MIL.MdispControl(MilDisplay, MIL.M_OVERLAY, MIL.M_ENABLE);
                MIL.MdispInquire(MilDisplay, MIL.M_OVERLAY_ID, ref MilOverlayImage);
                MIL.MdispInquire(MilDisplay, MIL.M_TRANSPARENT_COLOR, ref TransColor);

                MIL.MbufClear(MilOverlayImage, TransColor);
                MIL.MgraControl(MIL.M_DEFAULT, MIL.M_BACKGROUND_MODE, MIL.M_TRANSPARENT);

                MIL.MbufControl(MilOverlayImage, MIL.M_DC_ALLOC, MIL.M_DEFAULT);
                MIL.MbufControl(MilOverlayImage, MIL.M_MODIFIED, MIL.M_DEFAULT);
            }
        }

        public void SetZoomRate(double dZoom, int fi_nOffsetX, int fi_nOffsetY)
        {
            m_dZoom = dZoom;
            _offsetX = -fi_nOffsetX;
            _offsetY = -fi_nOffsetY;
        }

        public void SetZoomRate(double dZoom, Point offset)
        {
            m_dZoom = dZoom;
            _offsetX = -offset.X;
            _offsetY = -offset.Y;
        }

        public void AddTextList(int x, int y, string text, double color)
        {
            if (textList.cnt < Def.MAX_TEXT_CNT)
            {
                textList.p[textList.cnt].X = x;
                textList.p[textList.cnt].Y = y;
                textList.str[textList.cnt] = text;
                textList.c[textList.cnt] = color;
                textList.cnt++;
            }
        }

        public void AddCrossList(int x, int y, int width, double color)
        {
            if (crossList.cnt < Def.MAX_CROSS_CNT)
            {// Camera Disp
                crossList.c[crossList.cnt] = color;
                crossList.p[crossList.cnt].X = x;
                crossList.p[crossList.cnt].Y = y;
                crossList.w[crossList.cnt] = width;
                crossList.cnt++;
            }
        }

        public void AddCrossList(double x, double y, int width, double color)
        {
            if (crossList.cnt < Def.MAX_CROSS_CNT)
            {// Camera Disp
                crossList.c[crossList.cnt] = color;
                crossList.p[crossList.cnt].X = (int)(x + 0.5);
                crossList.p[crossList.cnt].Y = (int)(y + 0.5);
                crossList.w[crossList.cnt] = width;
                crossList.cnt++;
            }
        }

        public void AddLineList(int sX, int sY, int eX, int eY, double color)
        {
            if (lineList.cnt < Def.MAX_LINE_CNT)
            {// Camera Disp
                lineList.c[lineList.cnt] = color;
                lineList.p[lineList.cnt, 0].X = sX;
                lineList.p[lineList.cnt, 0].Y = sY;
                lineList.p[lineList.cnt, 1].X = eX;
                lineList.p[lineList.cnt, 1].Y = eY;
                lineList.cnt++;
            }
        }

        public void AddLineList(double sX, double sY, double eX, double eY, double color)
        {
            if (lineList.cnt < Def.MAX_LINE_CNT)
            {// Camera Disp
                lineList.c[lineList.cnt] = color;
                lineList.p[lineList.cnt, 0].X = (int)(sX + 0.5);
                lineList.p[lineList.cnt, 0].Y = (int)(sY + 0.5);
                lineList.p[lineList.cnt, 1].X = (int)(eX + 0.5);
                lineList.p[lineList.cnt, 1].Y = (int)(eY + 0.5);
                lineList.cnt++;
            }
        }

        public void AddLineList(System.Drawing.Point sP, System.Drawing.Point eP, double color)
        {
            if (lineList.cnt < Def.MAX_LINE_CNT)
            {// Camera Disp
                lineList.c[lineList.cnt] = color;
                lineList.p[lineList.cnt, 0].X = sP.X;
                lineList.p[lineList.cnt, 0].Y = sP.Y;
                lineList.p[lineList.cnt, 1].X = eP.X;
                lineList.p[lineList.cnt, 1].Y = eP.Y;
                lineList.cnt++;
            }
        }

        public void AddPixelList(int x, int y, double color)
        {
            if (pixelList.cnt < Def.MAX_PIXEL_CNT)
            {// Camera Disp
                pixelList.c[pixelList.cnt] = color;
                pixelList.p[pixelList.cnt].X = x;
                pixelList.p[pixelList.cnt].Y = y;
                pixelList.cnt++;
            }
        }

        public void AddBoxList(int left, int top, int right, int bottom, double color)
        {
            if (boxList.cnt < Def.MAX_BOX_CNT)
            {// Camera Disp
                boxList.c[boxList.cnt] = color;
                boxList.r[boxList.cnt] = new Rectangle(left, top, right, bottom);
                boxList.cnt++;
            }
        }

        public void AddBoxList(double left, double top, double right, double bottom, double color)
        {
            if (boxList.cnt < Def.MAX_BOX_CNT)
            {// Camera Disp
                boxList.c[boxList.cnt] = color;
                boxList.r[boxList.cnt] = new Rectangle((int)(left + 0.5), (int)(top + 0.5), (int)(right + 0.5), (int)(bottom + 0.5));
                boxList.cnt++;
            }
        }

        public void AddBoxList(System.Drawing.Point sP, System.Drawing.Point eP, double color)
        {
            if (boxList.cnt < Def.MAX_BOX_CNT)
            {// Camera Disp
                boxList.c[boxList.cnt] = color;
                boxList.r[boxList.cnt] = new Rectangle(sP.X, sP.Y, eP.X, eP.Y);
                boxList.cnt++;
            }
        }

        public void AddCircleList(int left, int top, int right, int bottom, double color)
        {
            if (circleList.cnt < Def.MAX_CIRCLE_CNT)
            {
                circleList.r[circleList.cnt] = new Rectangle(left, top, right, bottom);
                circleList.c[circleList.cnt] = color;
                circleList.cnt++;
            }
        }


        public void drawOverlay(bool bDrawFlag)
        {
            MIL.MbufClear(MilOverlayImage, TransColor);

            if (!bDrawFlag)
            {
                pixelList.cnt = lineList.cnt = boxList.cnt = circleList.cnt = crossList.cnt = textList.cnt = 0;
                return;
            }

            int i, x, y, w;
            int x1, x2, y1, y2;
            long cx, cy, rx, ry;

            for (i = 0; i < pixelList.cnt; i++)
            {
                MIL.MgraColor(MIL.M_DEFAULT, pixelList.c[i]);

                x = (int)((_offsetX + pixelList.p[i].X) * m_dZoom + 0.5);
                y = (int)((_offsetY + pixelList.p[i].Y) * m_dZoom + 0.5);

                MIL.MgraDot(MIL.M_DEFAULT, MilOverlayImage, x, y);
            }

            for (i = 0; i < lineList.cnt; i++)
            {
                MIL.MgraColor(MIL.M_DEFAULT, lineList.c[i]);

                x1 = (int)((_offsetX + lineList.p[i, 0].X) * m_dZoom + 0.5);
                y1 = (int)((_offsetY + lineList.p[i, 0].Y) * m_dZoom + 0.5);
                x2 = (int)((_offsetX + lineList.p[i, 1].X) * m_dZoom + 0.5);
                y2 = (int)((_offsetY + lineList.p[i, 1].Y) * m_dZoom + 0.5);
                MIL.MgraLine(MIL.M_DEFAULT, MilOverlayImage, x1, y1, x2, y2);
            }

            for (i = 0; i < crossList.cnt; i++)
            {
                MIL.MgraColor(MIL.M_DEFAULT, crossList.c[i]);

                w = crossList.w[i];
                x = (int)((_offsetX + crossList.p[i].X) * m_dZoom + 0.5);
                y = (int)((_offsetY + crossList.p[i].Y) * m_dZoom + 0.5);

                MIL.MgraLine(MIL.M_DEFAULT, MilOverlayImage, x, (y - w), x, (y + w));
                MIL.MgraLine(MIL.M_DEFAULT, MilOverlayImage, (x - w), y, (x + w), y);
            }

            for (i = 0; i < circleList.cnt; i++)
            {
                MIL.MgraColor(MIL.M_DEFAULT, circleList.c[i]);

                cx = (int)((_offsetX + circleList.r[i].Left + circleList.r[i].Right) / 2 * m_dZoom + 0.5);
                cy = (int)((_offsetY + circleList.r[i].Top + circleList.r[i].Bottom) / 2 * m_dZoom + 0.5);
                rx = (int)((_offsetX + circleList.r[i].Right - circleList.r[i].Left + 1) / 2 * m_dZoom + 0.5);
                ry = (int)((_offsetY + circleList.r[i].Bottom - circleList.r[i].Top + 1) / 2 * m_dZoom + 0.5);

                MIL.MgraArc(MIL.M_DEFAULT, MilOverlayImage, cx, cy, rx, ry, 0, 360);
            }

            for (i = 0; i < boxList.cnt; i++)
            {
                MIL.MgraColor(MIL.M_DEFAULT, boxList.c[i]);

                x1 = (int)((_offsetX + boxList.r[i].Left) * m_dZoom + 0.5);
                y1 = (int)((_offsetY + boxList.r[i].Top) * m_dZoom + 0.5);
                x2 = (int)((_offsetX + boxList.r[i].Right) * m_dZoom + 0.5);
                y2 = (int)((_offsetY + boxList.r[i].Bottom) * m_dZoom + 0.5);

                MIL.MgraRect(MIL.M_DEFAULT, MilOverlayImage, x1, y1, x2, y2);
            }

            for (i = 0; i < textList.cnt; i++)
            {
                MIL.MgraColor(MIL.M_DEFAULT, textList.c[i]);

                x = (int)((_offsetX + textList.p[i].X) * m_dZoom + 0.5);
                y = (int)((_offsetY + textList.p[i].Y) * m_dZoom + 0.5);

                MIL.MgraFontScale(MIL.M_DEFAULT, (double)1, (double)1);
                MIL.MgraText(MIL.M_DEFAULT, MilOverlayImage, x, y, textList.str[i]);
            }


            MIL.MgraColor(MIL.M_DEFAULT, MIL.M_COLOR_GREEN);

            x = 20;
            y = Def.imgDispSizeY - 50;

            MIL.MgraFontScale(MIL.M_DEFAULT, (double)1.5, (double)1.5);
            MIL.MgraText(MIL.M_DEFAULT, MilOverlayImage, x, y, $"Zoom {m_dZoom:f2}, Offset ({-_offsetX}, {-_offsetY})");
        }
    }
}
