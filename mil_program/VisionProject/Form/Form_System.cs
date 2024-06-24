using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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
    public partial class Form_System : Form
    {
        Logic _logic;
        Overlay _overlay;
        Vision _vision;
        MainForm _mainForm;

        public DataManager _data;

        enum eSystem
        {
            eSystem_VGA = 0, eSystem_GIGE, eSystem_USB, eSystem_SOLIOUS, eSystem_RADIANT, eSystem_CXP, eSystem_Max
        };

        private string[] strSystem =
        {
            "VGA (Host)", "GigE", "USB", "SOLIOUS", "RADIANT", "CXP"
        };


        public Form_System(Logic logic)
        {
            _logic = logic;
            _data = logic._data;
            _overlay = logic.overlay;
            _vision = logic.vision;

            InitializeComponent();

            InitControl();
        }

        private void InitControl()
        {
            comboBox_System.Items.Clear();

            for (int i = 0; i < (int)eSystem.eSystem_Max; i++)
            {
                comboBox_System.Items.Add(strSystem[i]);
            }

            comboBox_System.SelectedIndex = (int)eSystem.eSystem_VGA;
        }

        private void button_Del_Digitizer_Click(object sender, EventArgs e)
        {

        }

        private void button_Add_Digitizer_Click(object sender, EventArgs e)
        {

        }

        public void SetSystemData()
        {

        }

    }
}
