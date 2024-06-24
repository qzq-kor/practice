namespace UtilTest
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            button_Exit = new Button();
            button_Serial = new Button();
            SuspendLayout();
            // 
            // button_Exit
            // 
            button_Exit.Location = new Point(637, 364);
            button_Exit.Name = "button_Exit";
            button_Exit.Size = new Size(124, 74);
            button_Exit.TabIndex = 0;
            button_Exit.Text = "종료";
            button_Exit.UseVisualStyleBackColor = true;
            button_Exit.Click += button_Exit_Click;
            // 
            // button_Serial
            // 
            button_Serial.Location = new Point(12, 12);
            button_Serial.Name = "button_Serial";
            button_Serial.Size = new Size(124, 74);
            button_Serial.TabIndex = 0;
            button_Serial.Text = "시리얼 통신";
            button_Serial.UseVisualStyleBackColor = true;
            button_Serial.Click += button_Serial_Click;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(button_Serial);
            Controls.Add(button_Exit);
            Name = "MainForm";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion

        private Button button_Exit;
        private Button button_Serial;
    }
}
