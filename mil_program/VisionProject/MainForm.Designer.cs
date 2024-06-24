namespace VisionProject
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
            panel_Image_0 = new Panel();
            button_Save = new Button();
            button_Main = new Button();
            button_System = new Button();
            SuspendLayout();
            // 
            // button_Exit
            // 
            button_Exit.Location = new Point(600, 22);
            button_Exit.Name = "button_Exit";
            button_Exit.Size = new Size(188, 42);
            button_Exit.TabIndex = 0;
            button_Exit.Text = "종료";
            button_Exit.UseVisualStyleBackColor = true;
            button_Exit.Click += button_Exit_Click;
            // 
            // panel_Image_0
            // 
            panel_Image_0.Location = new Point(0, 1);
            panel_Image_0.Name = "panel_Image_0";
            panel_Image_0.Size = new Size(222, 192);
            panel_Image_0.TabIndex = 1;
            panel_Image_0.MouseDown += panel_Image_0_MouseDown;
            panel_Image_0.MouseMove += panel_Image_0_MouseMove;
            panel_Image_0.MouseUp += panel_Image_0_MouseUp;
            // 
            // button_Save
            // 
            button_Save.Location = new Point(0, 0);
            button_Save.Name = "button_Save";
            button_Save.Size = new Size(75, 23);
            button_Save.TabIndex = 2;
            // 
            // button_Main
            // 
            button_Main.Location = new Point(604, 199);
            button_Main.Name = "button_Main";
            button_Main.Size = new Size(91, 42);
            button_Main.TabIndex = 0;
            button_Main.Text = "메인 화면";
            button_Main.UseVisualStyleBackColor = true;
            button_Main.Click += button_Main_Click;
            // 
            // button_System
            // 
            button_System.Location = new Point(701, 199);
            button_System.Name = "button_System";
            button_System.Size = new Size(91, 42);
            button_System.TabIndex = 0;
            button_System.Text = "비젼 시스템 설정";
            button_System.UseVisualStyleBackColor = true;
            button_System.Click += button_System_Click;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(panel_Image_0);
            Controls.Add(button_Save);
            Controls.Add(button_System);
            Controls.Add(button_Main);
            Controls.Add(button_Exit);
            Name = "MainForm";
            Text = "MainDialog";
            ResumeLayout(false);
        }

        #endregion

        private Button button_Exit;
        private Panel panel_Image_0;
        private Button button_Save;
        private Panel panel_Sub_0;
        private Button button_System;
        private Button button_Main;
    }
}
