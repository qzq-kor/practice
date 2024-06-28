using Microsoft.VisualBasic.Devices;
using Newtonsoft.Json;
using System;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace StudyProgram
{
    public class TcpCommunicationManager
    {
        private TcpClient? _client; 
        private NetworkStream? _stream; 
        private string[] lastValues = new string[6];
        public bool IsConnected => _client != null && _client.Connected;
        // 연결 여부 확인 -> UI에 적용 위해
        private string? _receivedData;  // 마지막으로 수신된 데이터를 저장하는 변수
        private string? _lastReceivedData;  // 마지막으로 수신된 데이터를 저장하는 변수
        private readonly SemaphoreSlim _semaphore = new SemaphoreSlim(1, 1);



        public bool Connect(string ipAddress, int port)
        {
            _client = new TcpClient();  // 새 클라이언트 인스턴스 생성. disconnect하고 해당 인스턴스가 없으면 예외 발생

            try
            {
                _client.Connect(ipAddress, port);
                _stream = _client.GetStream();

                return true;
            }
            catch (Exception ex)
            {
                // 연결 실패 처리
                Console.WriteLine("Connection failed: " + ex.Message);
                return false;
            }
        }



        public bool WriteDataAsync(int offset, string value, string retryCount)
        {
            try
            {
                _semaphore.Wait();
                if (_stream != null)
                {
                    int newValue = int.Parse(value);
                    int newRetryCount = int.Parse(retryCount);

                    for (int i = 0; i < newRetryCount; i++)
                    {
                        string sendMessage = $"[SET:REG, {offset}, {newValue}]";
                        byte[] message = Encoding.UTF8.GetBytes(sendMessage);
                        _stream.Write(message, 0, message.Length);

                        // Wait for the response
                        byte[] buffer = new byte[256];
                        int bytesRead = _stream.Read(buffer, 0, buffer.Length);
                        string response = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                        if (response == "[COMPLIETE]")
                            return true;
                    }

                }
                _semaphore.Release();
                return false;
            }
            catch (FormatException)
            {
                MessageBox.Show("올바르지 않은 값입니다.");
                return false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Disconnect();
                return false;
            }
            finally
            {
                if (_semaphore.CurrentCount == 0)
                    _semaphore.Release();
            }
        }

        public async Task<int?> ReadDataAsync(int offset, string retryCount)
        {
            await _semaphore.WaitAsync();
            try
            {
                if (_stream != null)
                {
                    int newRetryCount = int.Parse(retryCount);

                    for (int i = 0; i < newRetryCount; i++)
                    {
                        string sendMessage = $"[GET:REG, {offset}]";
                        byte[] message = Encoding.UTF8.GetBytes(sendMessage);
                        await _stream.WriteAsync(message, 0, message.Length);

                        // Wait for the response
                        byte[] buffer = new byte[256];
                        int bytesRead = await _stream.ReadAsync(buffer, 0, buffer.Length);
                        string response = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                        if (response == "[INCOMPLIETE]")
                            continue;

                        int[]? value = JsonConvert.DeserializeObject<int[]>(response);

                        if (value != null && offset >= 0 && offset < value.Length)
                            return value[offset];
                        else
                            return null;
                    }
                }
                return null;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                Disconnect();
                return null;
            }
            finally
            {
                if (_semaphore.CurrentCount == 0)
                    _semaphore.Release();
            }
        }
        class ConnectionStatusEventArgs : EventArgs
        {
            public bool IsConnected;
            public ConnectionStatusEventArgs(bool isConnected)
            {
                IsConnected = isConnected;
            }
        }

        class VariationDataChangeEventArgs : EventArgs
        {
            public int Offset;
            public int Value;
            public VariationDataChangeEventArgs(int offset, int value)
            {
                Offset = offset;
                Value = value;
            }
        }


        public void Disconnect()
        {
            if (_client != null)
            {
                if (_stream != null)
                {
                 //   _stream.Dispose();
                    _stream = null;
                }

                _client.Close();

            }
        }

        //         public string SendAndReceive(string message) // TCP 네트워크를 통해 문자열 메시지를 보내고, 응답을 받는 기능을 수행, _stream(네트워크 스트림) 사용하여 데이터 송 수신
        //         {
        //             if (_disposed)
        //                 throw new ObjectDisposedException("TcpCommunicationManager is already disposed.");
        // 
        //             byte[] data = Encoding.ASCII.GetBytes(message); // 입력받은 string message를 바이트 배열로 변환, 문자열을 ASCII 형식의 바이트로 인코딩
        //             _stream.Write(data, 0, data.Length); //메소드는 데이터 배열, 시작 인덱스(0), 그리고 데이터의 길이를 매개변수로 받아 네트워크를 통해 데이터를 전송
        // 
        //             byte[] response = new byte[256]; // 버로부터의 응답을 받기 위해 크기가 256 바이트인 배열 response를 준비
        //             int bytes = _stream.Read(response, 0, response.Length); // _stream.Read 메소드는 이 배열에 데이터를 읽어 저장하며, 실제로 읽은 바이트 수를 반환
        //             return Encoding.ASCII.GetString(response, 0, bytes); // 수신된 바이트를 다시 문자열로 변환합니다
        //         }


    }

}