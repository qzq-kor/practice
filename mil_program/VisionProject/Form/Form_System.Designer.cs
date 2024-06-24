namespace VisionProject
{
    partial class Form_System
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
            listBox_System = new ListBox();
            button_Apply = new Button();
            button_Add_Digitizer = new Button();
            button_Del_Digitizer = new Button();
            comboBox_System = new ComboBox();
            richText_Digizer_Y = new RichTextBox();
            button_Change_System = new Button();
            richTextBox_X = new RichTextBox();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            SuspendLayout();
            // 
            // listBox_System
            // 
            listBox_System.Font = new Font("맑은 고딕", 11.25F, FontStyle.Regular, GraphicsUnit.Point, 129);
            listBox_System.FormattingEnabled = true;
            listBox_System.ItemHeight = 20;
            listBox_System.Location = new Point(15, 25);
            listBox_System.Name = "listBox_System";
            listBox_System.Size = new Size(227, 144);
            listBox_System.TabIndex = 0;
            // 
            // button_Apply
            // 
            button_Apply.Location = new Point(267, 25);
            button_Apply.Name = "button_Apply";
            button_Apply.Size = new Size(163, 63);
            button_Apply.TabIndex = 1;
            button_Apply.Text = "설정값 적용";
            button_Apply.UseVisualStyleBackColor = true;
            // 
            // button_Add_Digitizer
            // 
            button_Add_Digitizer.Location = new Point(267, 305);
            button_Add_Digitizer.Name = "button_Add_Digitizer";
            button_Add_Digitizer.Size = new Size(163, 63);
            button_Add_Digitizer.TabIndex = 1;
            button_Add_Digitizer.Text = " Digizer 추가";
            button_Add_Digitizer.UseVisualStyleBackColor = true;
            button_Add_Digitizer.Click += button_Add_Digitizer_Click;
            // 
            // button_Del_Digitizer
            // 
            button_Del_Digitizer.Location = new Point(267, 125);
            button_Del_Digitizer.Name = "button_Del_Digitizer";
            button_Del_Digitizer.Size = new Size(163, 63);
            button_Del_Digitizer.TabIndex = 1;
            button_Del_Digitizer.Text = "Digitizer 삭제";
            button_Del_Digitizer.UseVisualStyleBackColor = true;
            button_Del_Digitizer.Click += button_Del_Digitizer_Click;
            // 
            // comboBox_System
            // 
            comboBox_System.Font = new Font("맑은 고딕", 11F);
            comboBox_System.FormattingEnabled = true;
            comboBox_System.Location = new Point(15, 239);
            comboBox_System.Name = "comboBox_System";
            comboBox_System.Size = new Size(227, 28);
            comboBox_System.TabIndex = 2;
            // 
            // richText_Digizer_Y
            // 
            richText_Digizer_Y.Font = new Font("맑은 고딕", 11F);
            richText_Digizer_Y.Location = new Point(166, 322);
            richText_Digizer_Y.Name = "richText_Digizer_Y";
            richText_Digizer_Y.Size = new Size(76, 36);
            richText_Digizer_Y.TabIndex = 4;
            richText_Digizer_Y.Text = "";
            // 
            // button_Change_System
            // 
            button_Change_System.Location = new Point(267, 223);
            button_Change_System.Name = "button_Change_System";
            button_Change_System.Size = new Size(163, 63);
            button_Change_System.TabIndex = 1;
            button_Change_System.Text = " 비젼보드 변경";
            button_Change_System.UseVisualStyleBackColor = true;
            button_Change_System.Click += button_Add_Digitizer_Click;
            // 
            // richTextBox_X
            // 
            richTextBox_X.Font = new Font("맑은 고딕", 11F);
            richTextBox_X.Location = new Point(81, 323);
            richTextBox_X.Name = "richTextBox_X";
            richTextBox_X.Size = new Size(76, 36);
            richTextBox_X.TabIndex = 4;
            richTextBox_X.Text = "";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(20, 331);
            label1.Name = "label1";
            label1.Size = new Size(51, 19);
            label1.TabIndex = 5;
            label1.Text = "해상도";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(115, 301);
            label2.Name = "label2";
            label2.Size = new Size(17, 19);
            label2.TabIndex = 5;
            label2.Text = "X";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(192, 301);
            label3.Name = "label3";
            label3.Size = new Size(17, 19);
            label3.TabIndex = 5;
            label3.Text = "Y";
            // 
            // Form_System
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(449, 811);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(richTextBox_X);
            Controls.Add(richText_Digizer_Y);
            Controls.Add(comboBox_System);
            Controls.Add(button_Del_Digitizer);
            Controls.Add(button_Change_System);
            Controls.Add(button_Add_Digitizer);
            Controls.Add(button_Apply);
            Controls.Add(listBox_System);
            Font = new Font("맑은 고딕", 10F);
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Name = "Form_System";
            ShowInTaskbar = false;
            Text = "시스템 설정";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ListBox listBox_System;
        private Button button_Apply;
        private Button button_Add_Digitizer;
        private Button button_Del_Digitizer;
        private ComboBox comboBox_System;
        private RichTextBox richText_Digizer_Y;
        private Button button_Change_System;
        private RichTextBox richTextBox_X;
        private Label label1;
        private Label label2;
        private Label label3;
    }
}