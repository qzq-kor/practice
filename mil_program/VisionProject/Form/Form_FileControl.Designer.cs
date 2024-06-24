namespace VisionProject
{
    partial class FormFileControl
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
            label1 = new Label();
            label2 = new Label();
            button_Prev = new Button();
            button_Next = new Button();
            richText_File_Path = new RichTextBox();
            richText_File_Name = new RichTextBox();
            richText_File_Index = new RichTextBox();
            button_Save = new Button();
            button_Clear = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("맑은 고딕", 10F);
            label1.Location = new Point(16, 12);
            label1.Name = "label1";
            label1.Size = new Size(70, 19);
            label1.TabIndex = 1;
            label1.Text = "파일 경로";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("맑은 고딕", 10F);
            label2.Location = new Point(16, 58);
            label2.Name = "label2";
            label2.Size = new Size(70, 19);
            label2.TabIndex = 1;
            label2.Text = "선택 파일";
            // 
            // button_Prev
            // 
            button_Prev.Location = new Point(258, 44);
            button_Prev.Name = "button_Prev";
            button_Prev.Size = new Size(49, 45);
            button_Prev.TabIndex = 2;
            button_Prev.Text = "◀";
            button_Prev.UseVisualStyleBackColor = true;
            button_Prev.Click += button_Prev_Click;
            // 
            // button_Next
            // 
            button_Next.Location = new Point(368, 43);
            button_Next.Name = "button_Next";
            button_Next.Size = new Size(53, 46);
            button_Next.TabIndex = 2;
            button_Next.Text = "▶";
            button_Next.UseVisualStyleBackColor = true;
            button_Next.Click += button_Next_Click;
            // 
            // richText_File_Path
            // 
            richText_File_Path.Font = new Font("맑은 고딕", 11F);
            richText_File_Path.Location = new Point(88, 7);
            richText_File_Path.Name = "richText_File_Path";
            richText_File_Path.Size = new Size(336, 32);
            richText_File_Path.TabIndex = 3;
            richText_File_Path.Text = "";
            // 
            // richText_File_Name
            // 
            richText_File_Name.Font = new Font("맑은 고딕", 11F);
            richText_File_Name.Location = new Point(88, 51);
            richText_File_Name.Name = "richText_File_Name";
            richText_File_Name.Size = new Size(155, 32);
            richText_File_Name.TabIndex = 3;
            richText_File_Name.Text = "";
            richText_File_Name.Click += richText_File_Name_Click;
            richText_File_Name.MouseClick += richText_File_Name_MouseClick;
            // 
            // richText_File_Index
            // 
            richText_File_Index.Font = new Font("맑은 고딕", 11F);
            richText_File_Index.Location = new Point(309, 52);
            richText_File_Index.Name = "richText_File_Index";
            richText_File_Index.Size = new Size(57, 32);
            richText_File_Index.TabIndex = 3;
            richText_File_Index.Text = "";
            // 
            // button_Save
            // 
            button_Save.Location = new Point(254, 104);
            button_Save.Name = "button_Save";
            button_Save.Size = new Size(169, 51);
            button_Save.TabIndex = 2;
            button_Save.Text = "영상 저장";
            button_Save.UseVisualStyleBackColor = true;
            button_Save.Click += button_Save_Click;
            // 
            // button_Clear
            // 
            button_Clear.Location = new Point(33, 104);
            button_Clear.Name = "button_Clear";
            button_Clear.Size = new Size(169, 51);
            button_Clear.TabIndex = 2;
            button_Clear.Text = "Overlay Clear";
            button_Clear.UseVisualStyleBackColor = true;
            button_Clear.Click += button_Clear_Click;
            // 
            // FormFileControl
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(450, 156);
            Controls.Add(richText_File_Index);
            Controls.Add(richText_File_Name);
            Controls.Add(richText_File_Path);
            Controls.Add(button_Next);
            Controls.Add(button_Clear);
            Controls.Add(button_Save);
            Controls.Add(button_Prev);
            Controls.Add(label2);
            Controls.Add(label1);
            FormBorderStyle = FormBorderStyle.None;
            Name = "FormFileControl";
            ShowInTaskbar = false;
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Button button_Prev;
        private Button button_Next;
        private RichTextBox richText_File_Path;
        private RichTextBox richText_File_Name;
        private RichTextBox richText_File_Index;
        private Button button_Save;
        private Button button_Clear;
    }
}