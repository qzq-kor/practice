using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using define_List;
using namespace_Overlay;
using namespace_Vision;
using VisionProject;

namespace VisionProject
{
    public class Logic
    {
        public Vision vision;
        public Overlay overlay;

        public Data.DataManager _data;

        public MainForm mainForm;
        public FormFileControl fileForm;
        public Form_System systemForm;

        public Logic()
        {
            vision = new Vision(this, Def.imgSizeX, Def.imgSizeY);
            vision.Init(0);

            overlay = new Overlay();

            _data = new Data.DataManager();
            _data.Load();


            fileForm = new FormFileControl(this);
            systemForm = new Form_System(this);

            mainForm = new MainForm(this);
            fileForm.SetMainForm(mainForm);
        }
    }
}
