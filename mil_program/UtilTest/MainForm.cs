namespace UtilTest
{
    public partial class MainForm : Form
    {
        public Form_Serial _form_Serial;
        public MainForm(Logic logic)
        {
            InitializeComponent();
        
            _form_Serial = logic._form_Serial;


            _form_Serial.Show();
        }

    private void button_Exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button_Serial_Click(object sender, EventArgs e)
        {        
            Form_Serial form_Serial_Modal = new Form_Serial();

            form_Serial_Modal.Show();
        }
    }
}
