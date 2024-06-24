namespace UtilTest
{
    partial class Form_Serial
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
            button_Exit = new Button();
            button_Open = new Button();
            button_Send = new Button();
            label = new Label();
            textBox_Send_Data = new TextBox();
            listBox_Data = new ListBox();
            comboBox_Port = new ComboBox();
            button_Close = new Button();
            SuspendLayout();
            // 
            // button_Exit
            // 
            button_Exit.Location = new Point(591, 475);
            button_Exit.Margin = new Padding(4);
            button_Exit.Name = "button_Exit";
            button_Exit.Size = new Size(152, 104);
            button_Exit.TabIndex = 0;
            button_Exit.Text = "창 닫기";
            button_Exit.UseVisualStyleBackColor = true;
            button_Exit.Click += button_Exit_Click;
            // 
            // button_Open
            // 
            button_Open.Location = new Point(292, 13);
            button_Open.Margin = new Padding(4);
            button_Open.Name = "button_Open";
            button_Open.Size = new Size(130, 69);
            button_Open.TabIndex = 1;
            button_Open.Text = "통신 연결";
            button_Open.UseVisualStyleBackColor = true;
            button_Open.Click += button_Open_Click;
            // 
            // button_Send
            // 
            button_Send.Location = new Point(591, 98);
            button_Send.Margin = new Padding(4);
            button_Send.Name = "button_Send";
            button_Send.Size = new Size(152, 85);
            button_Send.TabIndex = 1;
            button_Send.Text = "전송";
            button_Send.UseVisualStyleBackColor = true;
            button_Send.Click += button_Send_Click;
            // 
            // label
            // 
            label.AutoSize = true;
            label.Location = new Point(23, 40);
            label.Margin = new Padding(4, 0, 4, 0);
            label.Name = "label";
            label.Size = new Size(72, 20);
            label.TabIndex = 2;
            label.Text = "Port 번호";
            // 
            // textBox_Send_Data
            // 
            textBox_Send_Data.Location = new Point(23, 127);
            textBox_Send_Data.Margin = new Padding(4);
            textBox_Send_Data.Name = "textBox_Send_Data";
            textBox_Send_Data.Size = new Size(538, 27);
            textBox_Send_Data.TabIndex = 3;
            // 
            // listBox_Data
            // 
            listBox_Data.FormattingEnabled = true;
            listBox_Data.ItemHeight = 20;
            listBox_Data.Location = new Point(23, 175);
            listBox_Data.Margin = new Padding(4);
            listBox_Data.Name = "listBox_Data";
            listBox_Data.Size = new Size(538, 404);
            listBox_Data.TabIndex = 4;
            // 
            // comboBox_Port
            // 
            comboBox_Port.FormattingEnabled = true;
            comboBox_Port.Location = new Point(122, 37);
            comboBox_Port.Margin = new Padding(4);
            comboBox_Port.Name = "comboBox_Port";
            comboBox_Port.Size = new Size(162, 28);
            comboBox_Port.TabIndex = 5;
            // 
            // button_Close
            // 
            button_Close.Location = new Point(431, 13);
            button_Close.Margin = new Padding(4);
            button_Close.Name = "button_Close";
            button_Close.Size = new Size(130, 69);
            button_Close.TabIndex = 1;
            button_Close.Text = "통신 종료";
            button_Close.UseVisualStyleBackColor = true;
            button_Close.Click += button_Close_Click;
            // 
            // Form_Serial
            // 
            AutoScaleDimensions = new SizeF(9F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(761, 600);
            Controls.Add(comboBox_Port);
            Controls.Add(listBox_Data);
            Controls.Add(textBox_Send_Data);
            Controls.Add(label);
            Controls.Add(button_Send);
            Controls.Add(button_Close);
            Controls.Add(button_Open);
            Controls.Add(button_Exit);
            Font = new Font("맑은 고딕", 11F);
            Margin = new Padding(4);
            Name = "Form_Serial";
            Text = "Form_Serial";
            Shown += Form_Serial_Shown;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button_Open;
        private Button button_Close;
        private Button button_Send;
        private Button button_Exit;

        private Label label;
        private ComboBox comboBox_Port;
        private ListBox listBox_Data;
        private TextBox textBox_Send_Data;
    }
}