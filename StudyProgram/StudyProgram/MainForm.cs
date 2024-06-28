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

            currentOptions = OptionsManager.LoadOptions() ?? new Options(); // null이면 새 인스턴스 생성

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

            bool isSaved = OptionsManager.SaveOptions(currentOptions); // 옵션 저장 시도
            if (isSaved == true)
            {
                UpdateOptionsFromUI(); // 옵션 업데이트
                MessageBox.Show("설정이 저장되었습니다.", "저장 성공", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("옵션 저장에 실패했습니다. 다시 시도해주세요.", "오류", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void UpdateOptionsFromUI() // 옵션 UI 업데이트
        {

            currentOptions.IPAddress = textBox_address.Text;
            currentOptions.Port = int.TryParse(textBox_port.Text, out int port) ? port : 0;
            currentOptions.RetryCount = int.TryParse(textBox_retry_count.Text, out int retryCount) ? retryCount : 0; // 어떻게 바꾸는게 좋을까요
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

                // 비동기 연결 로직을 실행하여 UI 차단 방지
                bool isCon = false;
                await Task.Run(() => // await Task.Run()을 사용하여 연결 로직을 별도의 스레드에서 비동기적으로 실행 연결 로직이 백그라운드에서 처리!!
                {
                    if (currentOptions.IPAddress != null && currentOptions.Port != 0)
                    {
                        isCon = tcpManager.Connect(currentOptions.IPAddress, currentOptions.Port);
                    }
                });

                // 연결 후 폼을 닫음
                connectingForm.Close();

                // 연결 결과에 따라 메시지 처리
                if (currentOptions.IPAddress != null && currentOptions.Port != 0)
                {
                    if (isCon)
                    {
                        MessageBox.Show("연결이 성공적으로 완료되었습니다.", "TCP Client", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox_applied_address.Text = currentOptions.IPAddress;
                        textBox_applied_port.Text = currentOptions.Port.ToString();
                        button_disconnect.Enabled = true;
                    }
                    else
                    {
                        MessageBox.Show("연결에 실패했습니다. 커뮤니케이터 서버를 확인하세요.", "TCP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("IP 주소 또는 포트 정보가 유효하지 않습니다. 설정을 확인하세요.", "연결 실패", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }

                UpdateConnectionStatus();
            }
        }


        private void button_disconnect_Click(object sender, EventArgs e) // 연결 해제 버튼.
        {
            MessageBox.Show("연결이 해제되었습니다.", "TCP Client", MessageBoxButtons.OK, MessageBoxIcon.Information);
            tcpManager.Disconnect();
            UpdateConnectionStatus();
            button_disconnect.Enabled = false; // 연결 해제 버튼 비활성화
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
                    MessageBox.Show("읽기에 실패하였습니다.", "실패", MessageBoxButtons.OK, MessageBoxIcon.Warning);

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