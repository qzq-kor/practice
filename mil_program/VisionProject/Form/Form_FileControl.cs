
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using define_List;
using namespace_Overlay;
using namespace_Vision;
using VisionProject.Data;


namespace VisionProject
{
    public partial class FormFileControl : Form
    {
        Logic _logic;
        Overlay _overlay;
        Vision _vision;
        MainForm _mainForm;

        public DataManager _data;
        int nFileIndex;
        int nFileCnt;

        public FormFileControl(Logic logic)
        {
            InitializeComponent();

            _logic = logic;
            _data = logic._data;
            _overlay = logic.overlay;
            _vision = logic.vision;

            richText_File_Index.SelectionAlignment = HorizontalAlignment.Center;
            richText_File_Name.SelectionAlignment = HorizontalAlignment.Center;
        }

        public void SetMainForm(MainForm mainForm)
        {
            _mainForm = mainForm;

            SetPath(_data.currentPath);
        }


        public void SetPath(string path)
        {
            nFileIndex = 0;
            richText_File_Path.Text = path;

            string[] files = Directory.GetFiles(path);
            nFileCnt = files.Length;

            if (nFileCnt < 1)
                richText_File_Index.Text = "0";
            else
            {
                LoadFileIndex(nFileIndex);
            }
        }

        public void LoadFileIndex(int nIndex)
        {
            string?[] files = Directory.GetFiles(richText_File_Path.Text)
                                     .Where(s => s.EndsWith(".bmp") || s.EndsWith(".jpg") || s.EndsWith(".png"))
                                     .Select(Path.GetFileName)
                                     .ToArray();

            nFileCnt = files.Length;

            nFileIndex = nIndex;

            if (nFileIndex < 0)
                nFileIndex = 0;
            else if (nFileIndex >= nFileCnt)
                nFileIndex = nFileIndex - 1;

            richText_File_Index.Text = $"{nFileIndex + 1} / {nFileCnt}";
            richText_File_Name.Text = files[nFileIndex];


            string strFileName = $"{richText_File_Path.Text}\\{files[nFileIndex]}";
            _mainForm.LoadImage(strFileName);
        }

        private void button_Prev_Click(object sender, EventArgs e)
        {
            LoadFileIndex(nFileIndex - 1);
        }

        private void button_Next_Click(object sender, EventArgs e)
        {
            LoadFileIndex(nFileIndex + 1);
        }
        private void button_Save_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Title = "영상 파일 불러오기";
            saveFileDialog.Filter = "Image 파일|*.bmp;*.jpg;*.png|All Files|*.*;";
            saveFileDialog.InitialDirectory = richText_File_Path.Text; // 특정 폴더 경로 설정

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                string strFileName = saveFileDialog.FileName;
                _vision.SaveImage(strFileName, _vision.MilImageSubDisp[_mainForm.nImageIndex]);
            }
        }

        private void richText_File_Name_Click(object sender, EventArgs e)
        {

        }

        private void button_Clear_Click(object sender, EventArgs e)
        {
            _overlay.drawOverlay(false);
            _overlay.drawOverlay(true);
        }

        private void richText_File_Name_MouseClick(object sender, MouseEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = "영상 파일 불러오기";
            openFileDialog.Filter = "Image 파일|*.bmp;*.jpg;*.png|All Files|*.*;";
            openFileDialog.InitialDirectory = richText_File_Path.Text; // 특정 폴더 경로 설정


            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string strFileName = openFileDialog.FileName;
                _mainForm.LoadImage(strFileName);
            }
        }
    }
}
