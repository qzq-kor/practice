namespace StudyProgram
{
    partial class ConnectingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label_Connecting = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label_Connecting
            // 
            this.label_Connecting.AutoSize = true;
            this.label_Connecting.Location = new System.Drawing.Point(59, 63); // 위치 조정
            this.label_Connecting.Name = "label_Connecting";
            this.label_Connecting.Size = new System.Drawing.Size(223, 15);
            this.label_Connecting.TabIndex = 0;
            this.label_Connecting.Text = "연결 중입니다... 잠시만 기다려주십시오.";
            // 
            // ConnectingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(341, 145); // 폼 크기
            this.Controls.Add(this.label_Connecting);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog; // 크기 조절 불가능하게 설정
            this.Name = "ConnectingForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen; // 폼 시작 위치를 화면 중앙으로 설정
            this.Text = "ConnectingForm"; // 폼의 타이틀
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private Label label_Connecting;
    }
}