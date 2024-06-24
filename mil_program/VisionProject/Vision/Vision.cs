
using System;
using System.Windows.Forms;
using Matrox.MatroxImagingLibrary;

using define_List;
using namespace_Overlay;
using VisionProject;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Rebar;


namespace namespace_Vision
{
    public unsafe class Vision
    {
        Logic _logic;

        public MIL_ID MilApplication;
        public MIL_ID MilSystem;
        public MIL_ID MilDigitizer;

        public MIL_ID[] MilImage;
        public MIL_ID MilImageMainDisp;
        public MIL_ID[] MilImageSubDisp;

        int nSubImageCnt;
        int iRealSizeX, iRealSizeY;
        int iBandSize;


        public byte* m_Image;
        public byte[]? m_ImageProc;
        public byte* m_ImageBin;


        public double m_dZoom;
        public int offsetX, offsetY;

        public int m_nPitch;

        public Vision(Logic logic, int imgSizeX, int imgSizeY)
        {
            _logic = logic;

            MilApplication = MIL.M_NULL;
            MilSystem = MIL.M_NULL;
            MilDigitizer = MIL.M_NULL;

            MilImage = new MIL_ID[(int)ImageIndex.Img_Cnt];
            MilImageMainDisp = MIL.M_NULL;
            MilImageSubDisp = new MIL_ID[Def.subImageCnt];

            m_dZoom = 1;
            offsetX = offsetY = 0;

            iRealSizeX = imgSizeX;
            iRealSizeY = imgSizeY;
            iBandSize = 3;
            this.nSubImageCnt = nSubImageCnt;
        }

        public bool Init(int nMode)
        {
            MIL_INT milWidth = 0;
            MIL_INT milHeight = 0;

            long bufAttri_Image = MIL.M_IMAGE + MIL.M_PROC;
            long bufAttri_Disp = bufAttri_Image + MIL.M_DISP;
            long bufAttri_Grab = bufAttri_Image;

            MIL.MappAlloc(MIL.M_NULL, MIL.M_DEFAULT, ref MilApplication);
            MIL.MappControl(MIL.M_DEFAULT, MIL.M_ERROR, MIL.M_PRINT_ENABLE);
            MIL.MsysAlloc(MilApplication, MIL.M_SYSTEM_GIGE_VISION, MIL.M_DEV0, MIL.M_COMPLETE, ref MilSystem);

            MIL_INT iDlgCnt = MIL.MsysInquire(MilSystem, MIL.M_DIGITIZER_NUM, MIL.M_NULL);  //연결된 카메라 갯수 받아옴
            MIL_INT iBoardType = MIL.MsysInquire(MilSystem, MIL.M_BOARD_TYPE, MIL.M_NULL);  //연결된 보드 타입 유에스빈지  VGA인지

            if(nMode  == 1)
                MIL.MdigAlloc(MilSystem, MIL.M_DEV0, "C:\\Wintec\\Vision\\DCF\\Default.dcf", MIL.M_DEFAULT, ref MilDigitizer); //카메라 할당 

            if (MilDigitizer != MIL.M_NULL)
            {
                iBandSize = (int)MIL.MdigInquire(MilDigitizer, MIL.M_SIZE_BAND, MIL.M_NULL);
                iRealSizeX = (int)MIL.MdigInquire(MilDigitizer, MIL.M_SIZE_X, MIL.M_NULL);
                iRealSizeY = (int)MIL.MdigInquire(MilDigitizer, MIL.M_SIZE_Y, MIL.M_NULL);

                MIL.MdigControl(MilDigitizer, MIL.M_GRAB_MODE, MIL.M_ASYNCHRONOUS);
                MIL.MdigControl(MilDigitizer, MIL.M_GRAB_TIMEOUT, 500);
                
                bufAttri_Grab += MIL.M_GRAB;
            }

            AllocImageBuffer(bufAttri_Grab, (int)ImageIndex.Img_Cnt, MilImage, iBandSize, iRealSizeX, iRealSizeY);

            AllocImageBuffer(bufAttri_Disp, (int)Def.subImageCnt, MilImageSubDisp, iBandSize, iRealSizeX, iRealSizeY);



            MIL.MbufAllocColor(MilSystem, iBandSize, Def.imgDispSizeX, Def.imgDispSizeY, 8 + MIL.M_UNSIGNED, bufAttri_Disp, ref MilImageMainDisp); //원본 이미지 버퍼 할당 
            if (MilImageMainDisp == MIL.M_NULL)
            {
                MessageBox.Show("원본 영상 버퍼 생성 실패!");
                return false;
            }
            MIL.MbufClear(MilImageMainDisp, 0x00);


            MIL_INT milPitch = 0;
            MIL.MbufInquire(MilImage[(int)ImageIndex.Img_Org], MIL.M_PITCH, ref milPitch);

            m_nPitch = (int)milPitch;


            MIL_INT MilPtr = MIL.M_NULL;

            MIL.MbufInquire(MilImage[(int)ImageIndex.Img_Org], MIL.M_HOST_ADDRESS, ref MilPtr);
            m_Image = (byte*)(IntPtr)MilPtr;

            MIL.MbufInquire(MilImage[(int)ImageIndex.Img_Org], MIL.M_HOST_ADDRESS_BAND, ref MilPtr);
            m_Image = (byte*)(IntPtr)MilPtr;

            m_ImageProc = new byte[m_nPitch * Def.imgSizeY * 3];
//             MIL.MbufInquire(MilImage[(int)Image.Proc], MIL.M_HOST_ADDRESS, ref MilPtr);
//             m_ImageProc = (byte*)(IntPtr)MilPtr;

           MIL.MbufInquire(MilImage[(int)ImageIndex.Img_Bin], MIL.M_HOST_ADDRESS, ref MilPtr);
           m_ImageBin = (byte*)(IntPtr)MilPtr;

            return true;
        }

        public bool AllocImageBuffer(long attribute, int nCnt, MIL_ID[] milBuffer, int nBand, int nWidth, int nHeight)
        {
            MIL_INT band;

            for (int i = 0; i < nCnt; i++)
            {
                if (i == (int)ImageIndex.Img_Bin)
                    band = 1;
                else
                    band = nBand;

                MIL.MbufAllocColor(MilSystem, nBand, nWidth, nHeight, 8 + MIL.M_UNSIGNED, attribute, ref milBuffer[i]);    //카메라 영상 버퍼 할당
                if (milBuffer[i] == MIL.M_NULL)
                {
                    MessageBox.Show($"milBuffer[{i}] 영상 버퍼 생성 실패!");
                    return false;
                }
                MIL.MbufClear(milBuffer[i], 0x00);
            }

            return true;
        }

        public double GetZoomRate()
        {
            return m_dZoom;
        }

        public Point GetOffset()
        {
            Point ptRtn = new Point (offsetX, offsetY);
            return ptRtn;
        }

        public void SetZoomImage(double fi_dRate, int fi_nOffsetX, int fi_nOffsetY)
        {
            if (fi_dRate <= 0)
                fi_dRate = 1;
            else if (fi_dRate > 32)
                fi_dRate = 32;

            m_dZoom = fi_dRate;
            offsetX = fi_nOffsetX;
            offsetY = fi_nOffsetY;

            if (offsetX < 0)
                offsetX = 0;
            if (offsetY < 0)
                offsetY = 0;

            int nDispSizeX = (int)(Def.imgDispSizeX / m_dZoom + 0.5);
            int nDispSizeY = (int)(Def.imgDispSizeY / m_dZoom + 0.5);

            if (offsetX > Def.imgSizeX - nDispSizeX)
                offsetX = Def.imgSizeX - nDispSizeX;
            if (offsetY > Def.imgSizeY - nDispSizeY)
                offsetY = Def.imgSizeY - nDispSizeY;

            MIL.MbufCopyColor2d(MilImage[(int)ImageIndex.Img_Org], MilImage[(int)ImageIndex.Img_Temp], MIL.M_ALL_BAND, (MIL_INT)offsetX, (MIL_INT)offsetY, MIL.M_ALL_BAND, 0, 0, nDispSizeX, nDispSizeY);
            MIL.MimResize(MilImage[(int)ImageIndex.Img_Temp], MilImageMainDisp, m_dZoom, m_dZoom, MIL.M_DEFAULT);
        }

        public double ChangeZoomRate(int nStep, int x, int y)
        {
            double dOldZoom = m_dZoom;

            double dMinZoomX = (double)Def.imgDispSizeX / Def.imgSizeX;
            double dMinZoomY = (double)Def.imgDispSizeY / Def.imgSizeY;
            double dMinZoom = (dMinZoomX > dMinZoomY) ? dMinZoomX : dMinZoomY;

            if (nStep > 0)
            {
                if (m_dZoom < 0.1)
                    m_dZoom = 0.1;
                else if (m_dZoom < 0.2)
                    m_dZoom = 0.2;
                else if (m_dZoom < 0.4)
                    m_dZoom = 0.4;
                else if (m_dZoom < 0.6)
                    m_dZoom = 0.6;
                else if (m_dZoom < 1)
                    m_dZoom = 1;
                else if (m_dZoom < 2)
                    m_dZoom = 2;
                else if (m_dZoom < 4)
                    m_dZoom = 4;
                else if (m_dZoom < 8)
                    m_dZoom = 8;
                else if (m_dZoom < 16)
                    m_dZoom = 16;
                else
                    m_dZoom = 32;
            }
            else if (nStep < 0)
            {
                if (m_dZoom <= 0.2)
                    m_dZoom = 0.1;
                else if (m_dZoom <= 0.4)
                    m_dZoom = 0.2;
                else if (m_dZoom <= 0.6)
                    m_dZoom = 0.4;
                else if (m_dZoom <= 1)
                    m_dZoom = 0.6;
                else if (m_dZoom <= 2)
                    m_dZoom = 1;
                else if (m_dZoom <= 4)
                    m_dZoom = 2;
                else if (m_dZoom <= 8)
                    m_dZoom = 4;
                else if (m_dZoom <= 16)
                    m_dZoom = 8;
                else if (m_dZoom <= 32)
                    m_dZoom = 16;
                else
                    m_dZoom = 32;

                if (m_dZoom < dMinZoom)
                    m_dZoom = dMinZoom;
            }

            int imgSizeX = (int)(Def.imgDispSizeX / m_dZoom);
            int imgSizeY = (int)(Def.imgDispSizeY / m_dZoom);

            offsetX = (int)(offsetX + x / dOldZoom - (x / m_dZoom));
            offsetY = (int)(offsetY + y / dOldZoom - (y / m_dZoom));

            if(offsetX < 0) offsetX = 0;
            if(offsetY < 0) offsetY = 0;

            return m_dZoom;
        }

        public void ImageCopy(int nIndex, int nSubIndex)
        {
            MIL.MbufCopy(MilImageSubDisp[nIndex], MilImage[nSubIndex]);
        }

        public void LoadImage(string path, MIL_ID milSrcimg)
        {
            if (path == null)
                return;

            if (milSrcimg == MIL.M_NULL)
                return;

            MIL.MbufClear(milSrcimg, 0);
            MIL.MbufImport(path, MIL.M_DEFAULT, MIL.M_LOAD, MilSystem, ref milSrcimg);


            double dZoom = (double)Def.imgDispSizeX / (double)Def.imgSizeX;
            SetZoomImage(dZoom, 0, 0);
        }

        public void SaveImage(string path, MIL_ID milSrcimg)
        {
            MIL.MbufExport(path, MIL.M_BMP, milSrcimg);
        }

        public int ProcBinaryImage()
        {
            MIL.MbufClear(MilImage[(int)ImageIndex.Img_Bin], 0x00);

//             int minTh = 60;
//             int maxTh = 120;
//             int minTh_R = 100;
// 
//             int R_G = 30;
//             int R_B = 30;
//             int G_B = 10;
// 
//             int pos = 0;
//             int val;
// 
//             int ref_R_G, ref_R_B, ref_G_B;
// 
//             for (int y = 0; y < Def.imgSizeY; y++)
//             {
//                 pos = y * m_nPitch;
// 
//                 for (int x = 0; x < Def.imgSizeX; x++)
//                 {
//                     val = m_Image_proc[pos];
// 
//                     ref_R_G = val * R_G / 100;
//                     ref_R_B = val * R_B / 100;
//                     ref_G_B = val * G_B / 100;
// 
// 
//                     if (minTh <= val && val <= maxTh && (minTh_R <= m_Image_proc[RED][pos]))
//                     {
//                         if ((m_Image_proc[RED][pos] >= (m_Image_proc[GREEN][pos] + ref_R_G) || ((m_Image_proc[RED][pos] >= 240) && (m_Image_proc[RED][pos] >= m_Image_proc[GREEN][pos])))
//                             && ((m_Image_proc[RED][pos] >= (val + ref_R_B) || m_Image_proc[RED][pos] >= 250))
//                             && ((m_Image_proc[GREEN][pos] >= (val + ref_G_B) || (m_Image_proc[RED][pos] >= 240 && (m_Image_proc[GREEN][pos] >= (val + 10)))))
//                             )
//                         {
//                             m_Image_bin[pos] = (byte)255;
//                         }
//                     }
// 
//                     pos++;
//                 }
//             }

            MIL.MimClose(MilImage[(int)ImageIndex.Img_Bin], MilImage[(int)ImageIndex.Img_Bin], 2, MIL.M_BINARY);      // 2~6 범위에서 선택

            return 1;
        }
    }
}
