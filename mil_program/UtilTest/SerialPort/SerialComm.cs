using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO.Ports;

namespace Serial_Comm
{
    public class SerialComm
    {
        private SerialPort serialPort;

        public event EventHandler<string> DataReceived;

        public SerialComm()
        {
            serialPort = null;
        }

        public SerialComm(string portName, int baudRate)
        {
            serialPort = new SerialPort(portName, baudRate);
            serialPort.DataReceived += SerialPort_DataReceived;
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadExisting();
            OnDataReceived(data);
        }

        protected virtual void OnDataReceived(string data)
        {
            DataReceived?.Invoke(this, data);
        }

        public bool Open()
        {
            bool bRtnFlag = false;

            if (serialPort.IsOpen)
            {
                MessageBox.Show("통신 포트가 이미 OPEN 상태입니다.");
                return true;
            }

            try
            {
                // 시리얼 포트 열기
                serialPort.Open();
                MessageBox.Show("시리얼 포트 열기 성공");

                bRtnFlag = true;
            }
            catch (UnauthorizedAccessException ex)
            {
                MessageBox.Show("시리얼 포트에 액세스할 권한이 없습니다.");
                MessageBox.Show(ex.Message);
            }
            catch (IOException ex)
            {
                MessageBox.Show("시리얼 포트를 열거나 닫는 중에 오류가 발생했습니다.");
                MessageBox.Show(ex.Message);
            }
            catch (Exception ex)
            {
                MessageBox.Show("오류가 발생했습니다.");
                MessageBox.Show(ex.Message);
            }

            return bRtnFlag;
        }

        public void Close()
        {
            if (serialPort == null)
                return;
            try
            {
                // 시리얼 포트 열기
                serialPort.Close();
                MessageBox.Show("시리얼 포트 닫기 성공");
            }
            catch (UnauthorizedAccessException ex)
            {
                MessageBox.Show("시리얼 포트에 액세스할 권한이 없습니다.");
                MessageBox.Show(ex.Message);
            }
            catch (IOException ex)
            {
                MessageBox.Show("시리얼 포트를 열거나 닫는 중에 오류가 발생했습니다.");
                MessageBox.Show(ex.Message);
            }
            catch (Exception ex)
            {
                MessageBox.Show("오류가 발생했습니다.");
                MessageBox.Show(ex.Message);
            }
        }

        public void Send(string data)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Write(data);
            }
        }

        public bool IsOpen()
        {
            if(serialPort == null)
                return false;

            else
                return serialPort.IsOpen;
        }
    }
}
