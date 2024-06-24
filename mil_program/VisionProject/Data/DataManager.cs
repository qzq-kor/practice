using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VisionProject.Data
{
    public class DataManager
    {
        public string currentPath;
        int nDlgNo;

        public DataManager()
        {
            currentPath = "D:\\Image";
            nDlgNo = 0;
        }

        public string GetCurrentPath ()
        {
            return currentPath;
        }

        public void SetCurrentPath(string strPath)
        {
            currentPath = strPath; 
        }

        static string GetCurrentDirectory()
        {
            return System.IO.Directory.GetCurrentDirectory();
        }

        public void Save()
        {
            string filePath = "data.txt";

            try
            {
                // 파일에 데이터 쓰기
                using (StreamWriter sw = new StreamWriter(filePath))
                {
                    sw.WriteLine("[CURRENT_DIRECTORY] " + currentPath);
                    sw.WriteLine("[Dialog_No] " + nDlgNo);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("파일에 쓰는 도중 오류가 발생했습니다: " + e.Message);
            }
        }
    
        public void Load()
        {
            string fileName = "data.txt";

            // 파일이 존재하는지 확인
            if (File.Exists(fileName))
            {
                try
                {
                    // 파일에서 한 줄씩 읽어오기
                    using (StreamReader sr = new StreamReader(fileName))
                    {
                        string line;
                        while ((line = sr.ReadLine()) != null)
                        {
                            ParseLine(line);
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("파일을 읽는 도중 오류가 발생했습니다: " + e.Message);
                }
            }
            else
            {
                Save();
            }
        }

        private void ParseLine(string line)
        {
            if (line.StartsWith("[CURRENT_DIRECTORY]"))
            {
                currentPath = line.Substring("[CURRENT_DIRECTORY]".Length).Trim();
            }
            else if (line.StartsWith("[Dialog_No]"))
            {
                nDlgNo = int.Parse(line.Substring("[Dialog_No]".Length).Trim());
            }
        }
    }
}
