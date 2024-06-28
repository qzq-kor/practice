using Newtonsoft.Json;
using StudyProgram;
using System;
using System.IO;
using System.Windows.Forms;

namespace StudyProgram
{
    public class Options
    {
        public string IPAddress { get; set; } = "127.0.0.1";  // 기본값으로 "127.0.0.1" 설정
        public int Port { get; set; }
        public int RetryCount { get; set; }
        public int Value1Min { get; set; }
        public int Value1Max { get; set; }
        public int Value2Min { get; set; }
        public int Value2Max { get; set; }
        public int Value3Min { get; set; }
        public int Value3Max { get; set; }
    }

    public static class OptionsManager
    {
        private static string optionsFilePath = Path.Combine(Application.StartupPath, "options.json"); //Application.StartupPath : 실행 중인 애플리케이션의 실행 파일(.exe)이 위치한 디렉토리 경로를 반환, Path.Combine = 운영 체제의 파일 시스템 규칙에 따라 올바르게 디렉토리 경로와 파일명을 결합

        public static Options? LoadOptions()
        {
            if (File.Exists(optionsFilePath)) // File.Exists(optionsFilePath)를 사용하는 이유는 options.json 파일이 실제로 존재하는지를 확인하기 위함
            {
                try
                {
                    string json = File.ReadAllText(optionsFilePath);
                    return JsonConvert.DeserializeObject<Options>(json); // Json 데이터의 역직렬화
                }
                catch (Exception ex)
                {
                    MessageBox.Show("오류 발생: " + ex.Message, "불러오기 실패", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            return new Options(); // 파일이 없거나 예외 발생 시 기본 옵션 반환
        }

        public static bool SaveOptions(Options options)
        {
            try
            {
                string json = JsonConvert.SerializeObject(options, Formatting.Indented); // Json 데이터의 직렬화
                File.WriteAllText(optionsFilePath, json); // 파일에 JSON 문자열 쓰기
                return true; // 성공적으로 저장되었음을 나타냅니다.
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Save failed: {ex.Message}");
                return false; // 오류 발생시 false 반환
            }

        }
    }
}