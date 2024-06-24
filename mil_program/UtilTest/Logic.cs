using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;


using UtilTest;
namespace UtilTest
{
    public class Logic
    {
        public MainForm mainForm;
        public Form_Serial _form_Serial;

        public Logic()
        {
            _form_Serial = new Form_Serial();

            mainForm = new MainForm(this);
        }
    }
}
