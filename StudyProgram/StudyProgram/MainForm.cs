using System;
using System.Net.Http;
using System.Net.Sockets;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.Security.Cryptography.X509Certificates;
using Newtonsoft.Json.Linq;

namespace StudyProgram
{
    public partial class MainForm : Form
    {
        private Options currentOptions;
        private TcpCommunicationManager tcpManager = new TcpCommunicationManager();
    
        private bool _isMethodRunning = false;
        private TextBox[]? _realTimeDataTextBox, _valueReadWriteTextBox;

        public MainForm()
        {
            InitializeComponent();
            InitializeRealTimeDataTextBox();

            currentOptions = OptionsManager.LoadOptions() ?? new Options(); // null�̸� �� �ν��Ͻ� ����

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            DisplayOptions();
        }

        private void InitializeRealTimeDataTextBox()
        {
            _realTimeDataTextBox = new TextBox[6];
            _valueReadWriteTextBox = new TextBox[6];

            _realTimeDataTextBox[0] = textBox_realtime_data_0;
            _realTimeDataTextBox[1] = textBox_realtime_data_1;
            _realTimeDataTextBox[2] = textBox_realtime_data_2;
            _realTimeDataTextBox[3] = textBox_realtime_data_3;
            _realTimeDataTextBox[4] = textBox_realtime_data_4;
            _realTimeDataTextBox[5] = textBox_realtime_data_5;

            _valueReadWriteTextBox[0] = textBox_reg_0;
            _valueReadWriteTextBox[1] = textBox_reg_1;
            _valueReadWriteTextBox[2] = textBox_reg_2;
            _valueReadWriteTextBox[3] = textBox_reg_3;
            _valueReadWriteTextBox[4] = textBox_reg_4;
            _valueReadWriteTextBox[5] = textBox_reg_5;
        }


        private void DisplayOptions()
        {
            textBox_address.Text = currentOptions.IPAddress;
            textBox_port.Text = currentOptions.Port.ToString();
            textBox_retry_count.Text = currentOptions.RetryCount.ToString();
            textBox_value_min_1.Text = currentOptions.Value1Min.ToString();
            textBox_value_max_1.Text = currentOptions.Value1Max.ToString();
            textBox_value_min_2.Text = currentOptions.Value2Min.ToString();
            textBox_value_max_2.Text = currentOptions.Value2Max.ToString();
            textBox_value_min_3.Text = currentOptions.Value3Min.ToString();
            textBox_value_max_3.Text = currentOptions.Value3Max.ToString();
        }

        private void button_apply_and_save_Click(object sender, EventArgs e)
        {

            bool isSaved = OptionsManager.SaveOptions(currentOptions); // �ɼ� ���� �õ�
            if (isSaved == true)
            {
                UpdateOptionsFromUI(); // �ɼ� ������Ʈ
                MessageBox.Show("������ ����Ǿ����ϴ�.", "���� ����", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("�ɼ� ���忡 �����߽��ϴ�. �ٽ� �õ����ּ���.", "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void UpdateOptionsFromUI() // �ɼ� UI ������Ʈ
        {

            currentOptions.IPAddress = textBox_address.Text;
            currentOptions.Port = int.TryParse(textBox_port.Text, out int port) ? port : 0;
            currentOptions.RetryCount = int.TryParse(textBox_retry_count.Text, out int retryCount) ? retryCount : 0; // ��� �ٲٴ°� �������
            currentOptions.Value1Min = int.TryParse(textBox_value_min_1.Text, out int value1Min) ? value1Min : 0;
            currentOptions.Value1Max = int.TryParse(textBox_value_max_1.Text, out int value1Max) ? value1Max : 0;
            currentOptions.Value2Min = int.TryParse(textBox_value_min_2.Text, out int value2Min) ? value2Min : 0;
            currentOptions.Value2Max = int.TryParse(textBox_value_max_2.Text, out int value2Max) ? value2Max : 0;
            currentOptions.Value3Min = int.TryParse(textBox_value_min_3.Text, out int value3Min) ? value3Min : 0;
            currentOptions.Value3Max = int.TryParse(textBox_value_max_3.Text, out int value3Max) ? value3Max : 0;

        }


        private void UpdateConnectionStatus()
        {
            textBox_connection_status.Text = tcpManager.IsConnected ? "Connected" : "Disconnected";
        }

        private async void button_connect_Click(object sender, EventArgs e)
        {
            using (var connectingForm = new ConnectingForm())
            {
                connectingForm.Show();

                // �񵿱� ���� ������ �����Ͽ� UI ���� ����
                bool isCon = false;
                await Task.Run(() => // await Task.Run()�� ����Ͽ� ���� ������ ������ �����忡�� �񵿱������� ���� ���� ������ ��׶��忡�� ó��!!
                {
                    if (currentOptions.IPAddress != null && currentOptions.Port != 0)
                    {
                        isCon = tcpManager.Connect(currentOptions.IPAddress, currentOptions.Port);
                    }
                });

                // ���� �� ���� ����
                connectingForm.Close();

                // ���� ����� ���� �޽��� ó��
                if (currentOptions.IPAddress != null && currentOptions.Port != 0)
                {
                    if (isCon)
                    {
                        MessageBox.Show("������ ���������� �Ϸ�Ǿ����ϴ�.", "TCP Client", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox_applied_address.Text = currentOptions.IPAddress;
                        textBox_applied_port.Text = currentOptions.Port.ToString();
                        button_disconnect.Enabled = true;
                    }
                    else
                    {
                        MessageBox.Show("���ῡ �����߽��ϴ�. Ŀ�´������� ������ Ȯ���ϼ���.", "TCP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("IP �ּ� �Ǵ� ��Ʈ ������ ��ȿ���� �ʽ��ϴ�. ������ Ȯ���ϼ���.", "���� ����", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }

                UpdateConnectionStatus();
            }
        }


        private void button_disconnect_Click(object sender, EventArgs e) // ���� ���� ��ư.
        {
            MessageBox.Show("������ �����Ǿ����ϴ�.", "TCP Client", MessageBoxButtons.OK, MessageBoxIcon.Information);
            tcpManager.Disconnect();
            UpdateConnectionStatus();
            button_disconnect.Enabled = false; // ���� ���� ��ư ��Ȱ��ȭ
        }

        private void RequestWriteInfoToReg(int offset, string value)
        {
            _isMethodRunning = true;
            bool result = tcpManager.WriteDataAsync(offset, value, textBox_retry_count.Text);
            

        }

        private async Task RequestReadInfoFromReg(int offset)
        {
            int? value = await tcpManager.ReadDataAsync(offset, textBox_retry_count.Text);

            if (_valueReadWriteTextBox != null)
            {
                if (value != null)
                    _valueReadWriteTextBox[offset].Text = value.ToString();
                else
                    MessageBox.Show("�б⿡ �����Ͽ����ϴ�.", "����", MessageBoxButtons.OK, MessageBoxIcon.Warning);

            }
        }

        private async void button_write_reg_0_Click(object sender, EventArgs e)
        {
            RequestWriteInfoToReg(0, textBox_reg_0.Text);
        }

        private async void button_write_reg_1_Click(object sender, EventArgs e)
        {
            RequestWriteInfoToReg(1, textBox_reg_1.Text);
        }

        private async void button_write_reg_2_Click(object sender, EventArgs e)
        {
             RequestWriteInfoToReg(2, textBox_reg_2.Text);
        }

        private async void button_write_reg_3_Click(object sender, EventArgs e)
        {
            RequestWriteInfoToReg(3, textBox_reg_3.Text);
        }

        private async void button_write_reg_4_Click(object sender, EventArgs e)
        {
            RequestWriteInfoToReg(4, textBox_reg_4.Text);
        }

        private async void button_write_reg_5_Click(object sender, EventArgs e)
        {
            RequestWriteInfoToReg(5, textBox_reg_5.Text);
        }


        private async void button_read_reg_0_Click(object sender, EventArgs e)
        {
            RequestReadInfoFromReg(0);
        }
        private async void button_read_reg_1_Click(object sender, EventArgs e)
        {
            RequestReadInfoFromReg(1);
        }
        private async void button_read_reg_2_Click(object sender, EventArgs e)
        {
            RequestReadInfoFromReg(2);
        }
        private async void button_read_reg_3_Click(object sender, EventArgs e)
        {
            RequestReadInfoFromReg(3);
        }
        private async void button_read_reg_4_Click(object sender, EventArgs e)
        {
            RequestReadInfoFromReg(4);
        }
        private async void button_read_reg_5_Click(object sender, EventArgs e)
        {
            RequestReadInfoFromReg(5);
        }
    }
}