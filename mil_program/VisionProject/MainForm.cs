using define_List;
using namespace_Overlay;
using namespace_Vision;
using Matrox.MatroxImagingLibrary;
using System.Drawing;
using System;
using System.Windows.Forms;


using VisionProject.Data;
using Microsoft.VisualBasic.Logging;
using System.Net.Http.Headers;

namespace VisionProject
{
    public partial class MainForm : Form
    {
        Logic _logic;
        Vision _vision;
        Overlay _overlay;
        Overlay[] _overlaySub;
        DataManager _data;

        public enum FormType { eForm_Main = 0, eForm_System };

        public int nImageIndex;

        FormFileControl _formFileControl;
        Form_System _formSystem;

        private bool bLButtonFlag;
        Point m_pointClick;
        Point m_pointStart;

        private Panel[] panel_Sub;
        private Panel panel_Select;
        private Panel panel_FileControl;
        private Panel panel_SubDialog;

        public MainForm(Logic logic)
        {
            InitializeComponent();

            _logic = logic;
            _vision = logic.vision;
            _overlay = logic.overlay;
            _data = logic._data;
            _formFileControl = logic.fileForm;
            _formSystem = logic.systemForm;

            bLButtonFlag = false;

            InitPanelControl();         // Main Display 용 Panel 생성..
            InitSubPanelControl();      // Sub Display 용 Panel 생성..

            InitControl();

            SelectSubForm(FormType.eForm_Main);
            Select_SubImage(0);
        }

        private void InitPanelControl()
        {
            panel_Image_0.Location = new Point(0, 0);
            panel_Image_0.ClientSize = new Size(Def.imgDispSizeX, Def.imgDispSizeY);

            panel_Image_0.MouseWheel += Panel_Image_0_MouseWheel;

            _overlay.Init(_vision.MilImageMainDisp, panel_Image_0);
        }

        private void InitSubPanelControl()
        {
            panel_Sub = new Panel[Def.subImageCnt];
            _overlaySub = new Overlay[Def.subImageCnt];

            int nStartPosX = Def.imgDispSizeX + Def.subImageGap;
            int nStartPosY = 0;

            for (int i = 0; i < Def.subImageCnt; i++)
            {
                panel_Sub[i] = new Panel();

                nStartPosY = i * (Def.subImageSizeY + Def.subImageGap);

                panel_Sub[i].BackColor = System.Drawing.Color.LightGray;
                panel_Sub[i].Dock = DockStyle.None;
                panel_Sub[i].Location = new System.Drawing.Point(nStartPosX, nStartPosY);
                panel_Sub[i].ClientSize = new System.Drawing.Size(Def.subImageSizeX, Def.subImageSizeY);
                Controls.Add(panel_Sub[i]);

                panel_Sub[i].MouseClick += Panel_Sub_MouseDown;

                _overlaySub[i] = new Overlay();
                _overlaySub[i].Init(_vision.MilImageSubDisp[i], panel_Sub[i], true);
            }
        }

        private void InitControl()
        {
            int nGap = 8;
            int nButtonSizeX = 100;
            int nButtonSizeY = 70;

            this.Location = new Point(0, 0);
            this.ClientSize = new Size(Def.mainFormSizeX, Def.mainFormSizeY);

            int nStartPosX = Def.imgDispSizeX + Def.subImageSizeX + nGap;
            int nSubFormSizeX = Def.mainFormSizeX - nStartPosX;
            int nFileFormSizeY = _formFileControl.ClientSize.Height;
            int nStartPosY = nFileFormSizeY + nGap;

            panel_Select = new Panel();
            panel_Select.Location = new Point(0, 0);
            panel_Select.ClientSize = new Size(0, 0);
            panel_Select.BackColor = Color.OrangeRed;
            this.Controls.Add(panel_Select);


            panel_FileControl = new Panel();
            panel_FileControl.Location = new Point(nStartPosX, 0);
            panel_FileControl.ClientSize = new Size(nSubFormSizeX, nFileFormSizeY);

            _formFileControl.TopLevel = false;
            _formFileControl.FormBorderStyle = FormBorderStyle.None; // 테두리 표시
            _formFileControl.Dock = DockStyle.Fill;

            panel_FileControl.Controls.Add(_formFileControl);
            _formFileControl.Show();
            Controls.Add(panel_FileControl);


            int nSubFormSizeY = Def.mainFormSizeY - nButtonSizeY * 3 - nGap - nFileFormSizeY;

            panel_SubDialog = new Panel();
            panel_SubDialog.Location = new Point(nStartPosX, nFileFormSizeY + nGap);
            panel_SubDialog.ClientSize = new Size(nSubFormSizeX, nSubFormSizeY);

            _formSystem.TopLevel = false;
            _formSystem.FormBorderStyle = FormBorderStyle.None; // 테두리 표시
            _formSystem.Dock = DockStyle.Fill;


            Controls.Add(panel_SubDialog);


            nStartPosX += nGap * 2;
            button_Exit.Location = new Point(nStartPosX, Def.mainFormSizeY - nButtonSizeY * 2);
            button_Exit.ClientSize = new Size(Def.mainFormSizeX - nStartPosX - nGap, nButtonSizeY * 1);

            nButtonSizeX = (Def.mainFormSizeX -  nStartPosX - nGap*2) / 3;

            nStartPosY = Def.mainFormSizeY - nButtonSizeY * 3 - nGap;
            button_Main.Location = new Point(nStartPosX, nStartPosY);
            button_Main.ClientSize = new Size(nButtonSizeX, nButtonSizeY);

            button_System.Location = new Point(nStartPosX + nButtonSizeX + nGap, nStartPosY);
            button_System.ClientSize = new Size(nButtonSizeX, nButtonSizeY);
        }

        public void SelectSubForm(FormType type)
        {
            if (type == FormType.eForm_Main)
            {
                panel_SubDialog.Controls.Clear(); // 기존 컨트롤 제거
            }
            else if (type == FormType.eForm_System)
            {
                panel_SubDialog.Controls.Clear(); // 기존 컨트롤 제거
                panel_SubDialog.Controls.Add(_formSystem);

                _formSystem.Show();
            }
        }

        private void button_Exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Panel_Sub_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Panel clickedPanel = sender as Panel; // sender를 Panel 형식으로 캐스팅

                if (clickedPanel == null)
                    return;

                // 클릭된 패널이 배열의 몇 번째 요소인지 확인
                int nIndex = Array.IndexOf(panel_Sub, clickedPanel);

                Select_SubImage(nIndex);
            }
        }
        private void Select_SubImage(int nIndex)
        {
            nImageIndex = nIndex;
            if (nImageIndex < 0)
                nImageIndex = 0;
            if (nImageIndex >= Def.subImageCnt)
                nImageIndex = Def.subImageCnt - 1;

            Point location = new Point(panel_Sub[nImageIndex].Location.X - 3, panel_Sub[nImageIndex].Location.Y - 3);
            Size size = new Size(panel_Sub[nImageIndex].ClientSize.Width + 6, panel_Sub[nImageIndex].ClientSize.Height + 6);

            panel_Select.Location = location;
            panel_Select.ClientSize = size;

            _vision.ImageCopy(nImageIndex, 0);
            _vision.SetZoomImage(_vision.m_dZoom, _vision.offsetX, _vision.offsetY);
        }

        private void panel_Image_0_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                bLButtonFlag = true;

                m_pointClick.X = e.X;
                m_pointClick.Y = e.Y;

                m_pointStart.X = _vision.offsetX;
                m_pointStart.Y = _vision.offsetY;


                double dZoomRate = _vision.GetZoomRate();

                int x = (int)(_vision.offsetX + e.X / dZoomRate + 0.5);
                int y = (int)(_vision.offsetY + e.Y / dZoomRate + 0.5);



                int valR, valG, valB;
                string tmpStr;
                int nWidth = Def.imgSizeX;

                MIL.MbufGet(_vision.MilImage[0], _vision.m_ImageProc);
                unsafe
                {
                    valR = _vision.m_ImageProc[(y * nWidth + x) + 0];
                    valG = _vision.m_ImageProc[(y * nWidth + x) + 1 * nWidth * Def.imgSizeY];
                    valB = _vision.m_ImageProc[(y * nWidth + x) + 2 * nWidth * Def.imgSizeY];
                }
                tmpStr = $"({x}, {y}) {valR}, {valG}, {valB}";

                _overlay.drawOverlay(false);
                _overlay.AddTextList(x, y, tmpStr, MIL.M_COLOR_GREEN);

                _overlay.AddCrossList(x, y, 5, MIL.M_COLOR_RED);
                _overlay.drawOverlay(true);
            }
        }

        private void Panel_Image_0_MouseWheel(object sender, MouseEventArgs e)
        {
            int x = e.X;
            int y = e.Y;

            _vision.ChangeZoomRate(e.Delta, x, y);
            _vision.SetZoomImage(_vision.m_dZoom, _vision.offsetX, _vision.offsetY);


            _overlay.SetZoomRate(_vision.GetZoomRate(), _vision.GetOffset());

            _overlay.drawOverlay(true);
        }

        private void panel_Image_0_MouseUp(object sender, MouseEventArgs e)
        {
            bLButtonFlag = false;
        }

        private void panel_Image_0_MouseMove(object sender, MouseEventArgs e)
        {
            if (bLButtonFlag == true)
            {
                double dZoom = _vision.GetZoomRate();
                int nDistX = (int)((e.X - m_pointClick.X) / dZoom + 0.5);
                int nDistY = (int)((e.Y - m_pointClick.Y) / dZoom + 0.5);

                int nOffsetX = m_pointStart.X - nDistX;
                int nOffsetY = m_pointStart.Y - nDistY;

                _vision.SetZoomImage(dZoom, nOffsetX, nOffsetY);

                _overlay.SetZoomRate(_vision.GetZoomRate(), _vision.GetOffset());
                _overlay.drawOverlay(true);

            }
        }

        public void LoadImage(string fileName)
        {
            _vision.LoadImage(fileName, _vision.MilImage[(int)ImageIndex.Img_Org]);
            _vision.LoadImage(fileName, _vision.MilImageSubDisp[nImageIndex]);
        }

        private void button_System_Click(object sender, EventArgs e)
        {
            SelectSubForm(FormType.eForm_System);

            return;
            double StartTime = 0;

            if (nImageIndex == 0)
                nImageIndex = 1;

            MIL.MbufCopy(_vision.MilImage[0], _vision.MilImage[1]);
            MIL.MappTimer(MIL.M_DEFAULT, MIL.M_TIMER_RESET, MIL.M_NULL);


            var value = new byte[1, 3];

            for (int y = 0; y < Def.imgSizeY; y++)
            {
                for (int x = 0; x < Def.imgSizeX; x++)
                {
                    value[0, 0] = (byte)((x % 512) / 2);
                    value[0, 1] = (byte)(x * 196 / Def.imgSizeX);
                    value[0, 2] = (byte)(x * 256 / Def.imgSizeX);

                    MIL.MbufPut2d(_vision.MilImage[1], x, y, 1, 1, value);
                }
            }

            MIL.MappTimer(MIL.M_DEFAULT, MIL.M_TIMER_READ, ref StartTime);

            MIL.MbufCopy(_vision.MilImage[1], _vision.MilImageSubDisp[nImageIndex]);

            _overlay.AddTextList(10, 10, $"{StartTime} msec", MIL.M_COLOR_RED);
            _overlay.drawOverlay(true);
        }

        private void button_Main_Click(object sender, EventArgs e)
        {
            SelectSubForm(FormType.eForm_Main);

            return;

            double StartTime = 0;

            MIL.MappTimer(MIL.M_DEFAULT, MIL.M_TIMER_RESET, MIL.M_NULL);

            int nOffset = Def.imgSizeX * Def.imgSizeY;

            for (int y = 0; y < Def.imgSizeY; y++)
            {
                for (int x = 0; x < Def.imgSizeX; x++)
                {
                    _vision.m_ImageProc[(y * Def.imgSizeX + x) + 0 * nOffset] = (byte)((x % 512) / 2);
                    _vision.m_ImageProc[(y * Def.imgSizeX + x) + 1 * nOffset] = (byte)(x * 196 / Def.imgSizeX);
                    _vision.m_ImageProc[(y * Def.imgSizeX + x) + 2 * nOffset] = (byte)(x * 256 / Def.imgSizeX);
                }
            }

            MIL.MbufPut(_vision.MilImageMainDisp, _vision.m_ImageProc);
            MIL.MappTimer(MIL.M_DEFAULT, MIL.M_TIMER_READ, ref StartTime);

            _overlay.AddTextList(10, 10, $"{StartTime} msec", MIL.M_COLOR_RED);
            _overlay.drawOverlay(true);
        }
    }
}
