using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Serial_Comm;
using System.IO.Ports;


namespace UtilTest
{
    public partial class Form_Serial : Form
    {
        static SerialPort serialPort;

        private SerialComm serialComm;

        public Form_Serial()
        {
            InitializeComponent();
            GetComPortInfo();
            
            serialComm = new SerialComm();
        }

        public void PutListData(string strData)
        {
            int nCnt = listBox_Data.Items.Count;
            if (nCnt > 1000)
            {
                listBox_Data.Items.Clear();
                nCnt = 0;
            }

            listBox_Data.Items.Add(strData);
            listBox_Data.SelectedIndex = nCnt;
        }

        public int GetComPortInfo()
        {
            string[] ports = SerialPort.GetPortNames();

            comboBox_Port.Items.Clear();

            for (int i = 0; i < ports.Length; i++)
            {
                comboBox_Port.Items.Add(ports[i]);
            }

            if (ports.Length > 0)
                comboBox_Port.SelectedIndex = 0;

            return ports.Length;
        }

        private void Form_Serial_Shown(object sender, EventArgs e)
        {
            GetComPortInfo();
        }

        private void button_Open_Click(object sender, EventArgs e)
        {
            int nIndex = comboBox_Port.SelectedIndex;

            if (nIndex < 0)
                return;
            string portName = comboBox_Port.SelectedItem.ToString();

            serialComm = new SerialComm(portName, 9600);

            serialComm.Open();
            serialComm.DataReceived += SerialComm_DataReceived;
        }

        private void button_Send_Click(object sender, EventArgs e)
        {
            if ((serialComm != null) && (serialComm.IsOpen()))
            {
                string sendStr = textBox_Send_Data.Text;
                serialComm.Send(sendStr);

                PutListData("[ SND ] " + sendStr);
            }
        }

        private void button_Exit_Click(object sender, EventArgs e)
        {
            serialComm.Close();

            this.Hide();
        }


        private void button_Close_Click(object sender, EventArgs e)
        {
            serialComm.Close();
        }

        private void SerialComm_DataReceived(Object sender, string data)
        {
            PutListData("{-[RCV] " + data);
        }

    }
}
