namespace StudyProgram
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
            dataGridView_report = new DataGridView();
            Column1 = new DataGridViewTextBoxColumn();
            Column2 = new DataGridViewTextBoxColumn();
            Column3 = new DataGridViewTextBoxColumn();
            Column4 = new DataGridViewTextBoxColumn();
            Column5 = new DataGridViewTextBoxColumn();
            Column6 = new DataGridViewTextBoxColumn();
            button_delete_selected_reports = new Button();
            button_export_csv_selected_reports = new Button();
            button_inspection = new Button();
            groupBox1 = new GroupBox();
            textBox_address = new TextBox();
            textBox_port = new TextBox();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            textBox_value_min_1 = new TextBox();
            label4 = new Label();
            textBox_value_max_1 = new TextBox();
            label5 = new Label();
            textBox_value_max_2 = new TextBox();
            label6 = new Label();
            textBox_value_min_2 = new TextBox();
            label7 = new Label();
            textBox_value_max_3 = new TextBox();
            label8 = new Label();
            textBox_value_min_3 = new TextBox();
            button_apply_and_save = new Button();
            groupBox2 = new GroupBox();
            textBox_retry_count = new TextBox();
            label24 = new Label();
            groupBox3 = new GroupBox();
            label17 = new Label();
            button_disconnect = new Button();
            textBox_connection_status = new TextBox();
            button_connect = new Button();
            label9 = new Label();
            textBox_applied_address = new TextBox();
            label10 = new Label();
            textBox_applied_port = new TextBox();
            groupBox4 = new GroupBox();
            label11 = new Label();
            label13 = new Label();
            textBox_realtime_data_5 = new TextBox();
            textBox_realtime_data_2 = new TextBox();
            label12 = new Label();
            label16 = new Label();
            textBox_realtime_data_0 = new TextBox();
            label15 = new Label();
            textBox_realtime_data_4 = new TextBox();
            textBox_realtime_data_3 = new TextBox();
            textBox_realtime_data_1 = new TextBox();
            label14 = new Label();
            groupBox5 = new GroupBox();
            button_read_reg_5 = new Button();
            button_write_reg_5 = new Button();
            button_read_reg_4 = new Button();
            button_write_reg_4 = new Button();
            button_read_reg_3 = new Button();
            button_write_reg_3 = new Button();
            button_read_reg_2 = new Button();
            button_write_reg_2 = new Button();
            button_read_reg_1 = new Button();
            button_write_reg_1 = new Button();
            button_read_reg_0 = new Button();
            button_write_reg_0 = new Button();
            label18 = new Label();
            label19 = new Label();
            label23 = new Label();
            textBox_reg_5 = new TextBox();
            textBox_reg_1 = new TextBox();
            textBox_reg_2 = new TextBox();
            textBox_reg_3 = new TextBox();
            label20 = new Label();
            textBox_reg_4 = new TextBox();
            label21 = new Label();
            label22 = new Label();
            textBox_reg_0 = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dataGridView_report).BeginInit();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            groupBox4.SuspendLayout();
            groupBox5.SuspendLayout();
            SuspendLayout();
            // 
            // dataGridView_report
            // 
            dataGridView_report.AllowUserToAddRows = false;
            dataGridView_report.AllowUserToDeleteRows = false;
            dataGridView_report.AllowUserToResizeColumns = false;
            dataGridView_report.AllowUserToResizeRows = false;
            dataGridView_report.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView_report.Columns.AddRange(new DataGridViewColumn[] { Column1, Column2, Column3, Column4, Column5, Column6 });
            dataGridView_report.Location = new Point(6, 22);
            dataGridView_report.Name = "dataGridView_report";
            dataGridView_report.RowHeadersVisible = false;
            dataGridView_report.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView_report.Size = new Size(669, 282);
            dataGridView_report.TabIndex = 0;
            // 
            // Column1
            // 
            Column1.HeaderText = "GUID";
            Column1.Name = "Column1";
            Column1.ReadOnly = true;
            Column1.Resizable = DataGridViewTriState.False;
            Column1.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // Column2
            // 
            Column2.HeaderText = "Date";
            Column2.Name = "Column2";
            Column2.ReadOnly = true;
            Column2.Resizable = DataGridViewTriState.False;
            Column2.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // Column3
            // 
            Column3.HeaderText = "Value 1";
            Column3.Name = "Column3";
            Column3.ReadOnly = true;
            Column3.Resizable = DataGridViewTriState.False;
            Column3.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // Column4
            // 
            Column4.HeaderText = "Value 2";
            Column4.Name = "Column4";
            Column4.ReadOnly = true;
            Column4.Resizable = DataGridViewTriState.False;
            Column4.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // Column5
            // 
            Column5.HeaderText = "Value 3";
            Column5.Name = "Column5";
            Column5.ReadOnly = true;
            Column5.Resizable = DataGridViewTriState.False;
            Column5.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // Column6
            // 
            Column6.HeaderText = "Result";
            Column6.Name = "Column6";
            Column6.ReadOnly = true;
            Column6.Resizable = DataGridViewTriState.False;
            Column6.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // button_delete_selected_reports
            // 
            button_delete_selected_reports.Location = new Point(681, 90);
            button_delete_selected_reports.Name = "button_delete_selected_reports";
            button_delete_selected_reports.Size = new Size(178, 62);
            button_delete_selected_reports.TabIndex = 1;
            button_delete_selected_reports.Text = "선택된 항목 삭제";
            button_delete_selected_reports.UseVisualStyleBackColor = true;
            // 
            // button_export_csv_selected_reports
            // 
            button_export_csv_selected_reports.Location = new Point(681, 158);
            button_export_csv_selected_reports.Name = "button_export_csv_selected_reports";
            button_export_csv_selected_reports.Size = new Size(178, 62);
            button_export_csv_selected_reports.TabIndex = 2;
            button_export_csv_selected_reports.Text = "선택된 항목 CSV로 내보내기";
            button_export_csv_selected_reports.UseVisualStyleBackColor = true;
            // 
            // button_inspection
            // 
            button_inspection.Location = new Point(681, 22);
            button_inspection.Name = "button_inspection";
            button_inspection.Size = new Size(178, 62);
            button_inspection.TabIndex = 3;
            button_inspection.Text = "검사";
            button_inspection.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(dataGridView_report);
            groupBox1.Controls.Add(button_inspection);
            groupBox1.Controls.Add(button_delete_selected_reports);
            groupBox1.Controls.Add(button_export_csv_selected_reports);
            groupBox1.Location = new Point(12, 562);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(863, 310);
            groupBox1.TabIndex = 4;
            groupBox1.TabStop = false;
            groupBox1.Text = "검사";
            // 
            // textBox_address
            // 
            textBox_address.Location = new Point(112, 20);
            textBox_address.Name = "textBox_address";
            textBox_address.Size = new Size(154, 23);
            textBox_address.TabIndex = 5;
            // 
            // textBox_port
            // 
            textBox_port.Location = new Point(112, 49);
            textBox_port.Name = "textBox_port";
            textBox_port.Size = new Size(154, 23);
            textBox_port.TabIndex = 6;
            // 
            // label1
            // 
            label1.Location = new Point(6, 19);
            label1.Name = "label1";
            label1.Size = new Size(100, 23);
            label1.TabIndex = 7;
            label1.Text = "아이피 :";
            label1.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            label2.Location = new Point(6, 49);
            label2.Name = "label2";
            label2.Size = new Size(100, 23);
            label2.TabIndex = 8;
            label2.Text = "포트 :";
            label2.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label3
            // 
            label3.Location = new Point(6, 107);
            label3.Name = "label3";
            label3.Size = new Size(100, 23);
            label3.TabIndex = 10;
            label3.Text = "값1 최소 :";
            label3.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_value_min_1
            // 
            textBox_value_min_1.Location = new Point(112, 107);
            textBox_value_min_1.Name = "textBox_value_min_1";
            textBox_value_min_1.Size = new Size(154, 23);
            textBox_value_min_1.TabIndex = 9;
            // 
            // label4
            // 
            label4.Location = new Point(6, 136);
            label4.Name = "label4";
            label4.Size = new Size(100, 23);
            label4.TabIndex = 12;
            label4.Text = "값1 최대 :";
            label4.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_value_max_1
            // 
            textBox_value_max_1.Location = new Point(112, 136);
            textBox_value_max_1.Name = "textBox_value_max_1";
            textBox_value_max_1.Size = new Size(154, 23);
            textBox_value_max_1.TabIndex = 11;
            // 
            // label5
            // 
            label5.Location = new Point(6, 194);
            label5.Name = "label5";
            label5.Size = new Size(100, 23);
            label5.TabIndex = 16;
            label5.Text = "값2 최대 :";
            label5.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_value_max_2
            // 
            textBox_value_max_2.Location = new Point(112, 194);
            textBox_value_max_2.Name = "textBox_value_max_2";
            textBox_value_max_2.Size = new Size(154, 23);
            textBox_value_max_2.TabIndex = 15;
            // 
            // label6
            // 
            label6.Location = new Point(6, 165);
            label6.Name = "label6";
            label6.Size = new Size(100, 23);
            label6.TabIndex = 14;
            label6.Text = "값2 최소 :";
            label6.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_value_min_2
            // 
            textBox_value_min_2.Location = new Point(112, 165);
            textBox_value_min_2.Name = "textBox_value_min_2";
            textBox_value_min_2.Size = new Size(154, 23);
            textBox_value_min_2.TabIndex = 13;
            // 
            // label7
            // 
            label7.Location = new Point(6, 252);
            label7.Name = "label7";
            label7.Size = new Size(100, 23);
            label7.TabIndex = 20;
            label7.Text = "값3 최대 :";
            label7.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_value_max_3
            // 
            textBox_value_max_3.Location = new Point(112, 252);
            textBox_value_max_3.Name = "textBox_value_max_3";
            textBox_value_max_3.Size = new Size(154, 23);
            textBox_value_max_3.TabIndex = 19;
            // 
            // label8
            // 
            label8.Location = new Point(6, 223);
            label8.Name = "label8";
            label8.Size = new Size(100, 23);
            label8.TabIndex = 18;
            label8.Text = "값3 최소 :";
            label8.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_value_min_3
            // 
            textBox_value_min_3.Location = new Point(112, 223);
            textBox_value_min_3.Name = "textBox_value_min_3";
            textBox_value_min_3.Size = new Size(154, 23);
            textBox_value_min_3.TabIndex = 17;
            // 
            // button_apply_and_save
            // 
            button_apply_and_save.Location = new Point(272, 213);
            button_apply_and_save.Name = "button_apply_and_save";
            button_apply_and_save.Size = new Size(110, 62);
            button_apply_and_save.TabIndex = 21;
            button_apply_and_save.Text = "적용 및 저장";
            button_apply_and_save.UseVisualStyleBackColor = true;
            button_apply_and_save.Click += button_apply_and_save_Click;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(textBox_retry_count);
            groupBox2.Controls.Add(label24);
            groupBox2.Controls.Add(label1);
            groupBox2.Controls.Add(button_apply_and_save);
            groupBox2.Controls.Add(textBox_address);
            groupBox2.Controls.Add(label7);
            groupBox2.Controls.Add(textBox_port);
            groupBox2.Controls.Add(textBox_value_max_3);
            groupBox2.Controls.Add(label2);
            groupBox2.Controls.Add(label8);
            groupBox2.Controls.Add(textBox_value_min_1);
            groupBox2.Controls.Add(textBox_value_min_3);
            groupBox2.Controls.Add(label3);
            groupBox2.Controls.Add(label5);
            groupBox2.Controls.Add(textBox_value_max_1);
            groupBox2.Controls.Add(textBox_value_max_2);
            groupBox2.Controls.Add(label4);
            groupBox2.Controls.Add(label6);
            groupBox2.Controls.Add(textBox_value_min_2);
            groupBox2.Location = new Point(12, 12);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(391, 284);
            groupBox2.TabIndex = 22;
            groupBox2.TabStop = false;
            groupBox2.Text = "옵션";
            // 
            // textBox_retry_count
            // 
            textBox_retry_count.Location = new Point(112, 78);
            textBox_retry_count.Name = "textBox_retry_count";
            textBox_retry_count.Size = new Size(154, 23);
            textBox_retry_count.TabIndex = 22;
            // 
            // label24
            // 
            label24.Location = new Point(6, 78);
            label24.Name = "label24";
            label24.Size = new Size(100, 23);
            label24.TabIndex = 23;
            label24.Text = "재시도 횟수 :";
            label24.TextAlign = ContentAlignment.MiddleRight;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(label17);
            groupBox3.Controls.Add(button_disconnect);
            groupBox3.Controls.Add(textBox_connection_status);
            groupBox3.Controls.Add(button_connect);
            groupBox3.Controls.Add(label9);
            groupBox3.Controls.Add(textBox_applied_address);
            groupBox3.Controls.Add(label10);
            groupBox3.Controls.Add(textBox_applied_port);
            groupBox3.Location = new Point(409, 42);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(278, 254);
            groupBox3.TabIndex = 23;
            groupBox3.TabStop = false;
            groupBox3.Text = "연결";
            // 
            // label17
            // 
            label17.Location = new Point(6, 79);
            label17.Name = "label17";
            label17.Size = new Size(100, 23);
            label17.TabIndex = 29;
            label17.Text = "연결 상태 :";
            label17.TextAlign = ContentAlignment.MiddleRight;
            // 
            // button_disconnect
            // 
            button_disconnect.Enabled = false;
            button_disconnect.Location = new Point(40, 108);
            button_disconnect.Name = "button_disconnect";
            button_disconnect.Size = new Size(110, 62);
            button_disconnect.TabIndex = 28;
            button_disconnect.Text = "연결 해제";
            button_disconnect.UseVisualStyleBackColor = true;
            button_disconnect.Click += button_disconnect_Click;
            // 
            // textBox_connection_status
            // 
            textBox_connection_status.Location = new Point(112, 79);
            textBox_connection_status.Name = "textBox_connection_status";
            textBox_connection_status.ReadOnly = true;
            textBox_connection_status.Size = new Size(154, 23);
            textBox_connection_status.TabIndex = 28;
            // 
            // button_connect
            // 
            button_connect.Location = new Point(156, 108);
            button_connect.Name = "button_connect";
            button_connect.Size = new Size(110, 62);
            button_connect.TabIndex = 24;
            button_connect.Text = "연결";
            button_connect.UseVisualStyleBackColor = true;
            button_connect.Click += button_connect_Click;
            // 
            // label9
            // 
            label9.Location = new Point(6, 20);
            label9.Name = "label9";
            label9.Size = new Size(100, 23);
            label9.TabIndex = 26;
            label9.Text = "아이피 :";
            label9.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_applied_address
            // 
            textBox_applied_address.Location = new Point(112, 21);
            textBox_applied_address.Name = "textBox_applied_address";
            textBox_applied_address.ReadOnly = true;
            textBox_applied_address.Size = new Size(154, 23);
            textBox_applied_address.TabIndex = 24;
            // 
            // label10
            // 
            label10.Location = new Point(6, 50);
            label10.Name = "label10";
            label10.Size = new Size(100, 23);
            label10.TabIndex = 27;
            label10.Text = "포트 :";
            label10.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_applied_port
            // 
            textBox_applied_port.Location = new Point(112, 50);
            textBox_applied_port.Name = "textBox_applied_port";
            textBox_applied_port.ReadOnly = true;
            textBox_applied_port.Size = new Size(154, 23);
            textBox_applied_port.TabIndex = 25;
            // 
            // groupBox4
            // 
            groupBox4.Controls.Add(label11);
            groupBox4.Controls.Add(label13);
            groupBox4.Controls.Add(textBox_realtime_data_5);
            groupBox4.Controls.Add(textBox_realtime_data_2);
            groupBox4.Controls.Add(label12);
            groupBox4.Controls.Add(label16);
            groupBox4.Controls.Add(textBox_realtime_data_0);
            groupBox4.Controls.Add(label15);
            groupBox4.Controls.Add(textBox_realtime_data_4);
            groupBox4.Controls.Add(textBox_realtime_data_3);
            groupBox4.Controls.Add(textBox_realtime_data_1);
            groupBox4.Controls.Add(label14);
            groupBox4.Location = new Point(12, 302);
            groupBox4.Name = "groupBox4";
            groupBox4.Size = new Size(226, 254);
            groupBox4.TabIndex = 24;
            groupBox4.TabStop = false;
            groupBox4.Text = "실시간 데이터";
            // 
            // label11
            // 
            label11.Location = new Point(6, 164);
            label11.Name = "label11";
            label11.Size = new Size(48, 23);
            label11.TabIndex = 36;
            label11.Text = "값 5 :";
            label11.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label13
            // 
            label13.Location = new Point(6, 19);
            label13.Name = "label13";
            label13.Size = new Size(48, 23);
            label13.TabIndex = 26;
            label13.Text = "값 0 :";
            label13.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_realtime_data_5
            // 
            textBox_realtime_data_5.Location = new Point(60, 164);
            textBox_realtime_data_5.Name = "textBox_realtime_data_5";
            textBox_realtime_data_5.ReadOnly = true;
            textBox_realtime_data_5.Size = new Size(154, 23);
            textBox_realtime_data_5.TabIndex = 35;
            // 
            // textBox_realtime_data_2
            // 
            textBox_realtime_data_2.Location = new Point(60, 77);
            textBox_realtime_data_2.Name = "textBox_realtime_data_2";
            textBox_realtime_data_2.ReadOnly = true;
            textBox_realtime_data_2.Size = new Size(154, 23);
            textBox_realtime_data_2.TabIndex = 29;
            // 
            // label12
            // 
            label12.Location = new Point(6, 135);
            label12.Name = "label12";
            label12.Size = new Size(48, 23);
            label12.TabIndex = 34;
            label12.Text = "값 4 :";
            label12.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label16
            // 
            label16.Location = new Point(6, 77);
            label16.Name = "label16";
            label16.Size = new Size(48, 23);
            label16.TabIndex = 30;
            label16.Text = "값 2 :";
            label16.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_realtime_data_0
            // 
            textBox_realtime_data_0.Location = new Point(60, 19);
            textBox_realtime_data_0.Name = "textBox_realtime_data_0";
            textBox_realtime_data_0.ReadOnly = true;
            textBox_realtime_data_0.Size = new Size(154, 23);
            textBox_realtime_data_0.TabIndex = 25;
            // 
            // label15
            // 
            label15.Location = new Point(6, 48);
            label15.Name = "label15";
            label15.Size = new Size(48, 23);
            label15.TabIndex = 28;
            label15.Text = "값 1 :";
            label15.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_realtime_data_4
            // 
            textBox_realtime_data_4.Location = new Point(60, 135);
            textBox_realtime_data_4.Name = "textBox_realtime_data_4";
            textBox_realtime_data_4.ReadOnly = true;
            textBox_realtime_data_4.Size = new Size(154, 23);
            textBox_realtime_data_4.TabIndex = 33;
            // 
            // textBox_realtime_data_3
            // 
            textBox_realtime_data_3.Location = new Point(60, 106);
            textBox_realtime_data_3.Name = "textBox_realtime_data_3";
            textBox_realtime_data_3.ReadOnly = true;
            textBox_realtime_data_3.Size = new Size(154, 23);
            textBox_realtime_data_3.TabIndex = 31;
            // 
            // textBox_realtime_data_1
            // 
            textBox_realtime_data_1.Location = new Point(60, 48);
            textBox_realtime_data_1.Name = "textBox_realtime_data_1";
            textBox_realtime_data_1.ReadOnly = true;
            textBox_realtime_data_1.Size = new Size(154, 23);
            textBox_realtime_data_1.TabIndex = 27;
            // 
            // label14
            // 
            label14.Location = new Point(6, 106);
            label14.Name = "label14";
            label14.Size = new Size(48, 23);
            label14.TabIndex = 32;
            label14.Text = "값 3 :";
            label14.TextAlign = ContentAlignment.MiddleRight;
            // 
            // groupBox5
            // 
            groupBox5.Controls.Add(button_read_reg_5);
            groupBox5.Controls.Add(button_write_reg_5);
            groupBox5.Controls.Add(button_read_reg_4);
            groupBox5.Controls.Add(button_write_reg_4);
            groupBox5.Controls.Add(button_read_reg_3);
            groupBox5.Controls.Add(button_write_reg_3);
            groupBox5.Controls.Add(button_read_reg_2);
            groupBox5.Controls.Add(button_write_reg_2);
            groupBox5.Controls.Add(button_read_reg_1);
            groupBox5.Controls.Add(button_write_reg_1);
            groupBox5.Controls.Add(button_read_reg_0);
            groupBox5.Controls.Add(button_write_reg_0);
            groupBox5.Controls.Add(label18);
            groupBox5.Controls.Add(label19);
            groupBox5.Controls.Add(label23);
            groupBox5.Controls.Add(textBox_reg_5);
            groupBox5.Controls.Add(textBox_reg_1);
            groupBox5.Controls.Add(textBox_reg_2);
            groupBox5.Controls.Add(textBox_reg_3);
            groupBox5.Controls.Add(label20);
            groupBox5.Controls.Add(textBox_reg_4);
            groupBox5.Controls.Add(label21);
            groupBox5.Controls.Add(label22);
            groupBox5.Controls.Add(textBox_reg_0);
            groupBox5.Location = new Point(244, 302);
            groupBox5.Name = "groupBox5";
            groupBox5.Size = new Size(443, 254);
            groupBox5.TabIndex = 25;
            groupBox5.TabStop = false;
            groupBox5.Text = "값 읽기/쓰기";
            // 
            // button_read_reg_5
            // 
            button_read_reg_5.Location = new Point(367, 161);
            button_read_reg_5.Name = "button_read_reg_5";
            button_read_reg_5.Size = new Size(64, 26);
            button_read_reg_5.TabIndex = 60;
            button_read_reg_5.Text = "읽기";
            button_read_reg_5.UseVisualStyleBackColor = true;
            // 
            // button_write_reg_5
            // 
            button_write_reg_5.Location = new Point(297, 161);
            button_write_reg_5.Name = "button_write_reg_5";
            button_write_reg_5.Size = new Size(64, 26);
            button_write_reg_5.TabIndex = 59;
            button_write_reg_5.Text = "쓰기";
            button_write_reg_5.UseVisualStyleBackColor = true;
            // 
            // button_read_reg_4
            // 
            button_read_reg_4.Location = new Point(367, 132);
            button_read_reg_4.Name = "button_read_reg_4";
            button_read_reg_4.Size = new Size(64, 26);
            button_read_reg_4.TabIndex = 58;
            button_read_reg_4.Text = "읽기";
            button_read_reg_4.UseVisualStyleBackColor = true;
            // 
            // button_write_reg_4
            // 
            button_write_reg_4.Location = new Point(297, 132);
            button_write_reg_4.Name = "button_write_reg_4";
            button_write_reg_4.Size = new Size(64, 26);
            button_write_reg_4.TabIndex = 57;
            button_write_reg_4.Text = "쓰기";
            button_write_reg_4.UseVisualStyleBackColor = true;
            // 
            // button_read_reg_3
            // 
            button_read_reg_3.Location = new Point(367, 103);
            button_read_reg_3.Name = "button_read_reg_3";
            button_read_reg_3.Size = new Size(64, 26);
            button_read_reg_3.TabIndex = 56;
            button_read_reg_3.Text = "읽기";
            button_read_reg_3.UseVisualStyleBackColor = true;
            // 
            // button_write_reg_3
            // 
            button_write_reg_3.Location = new Point(297, 103);
            button_write_reg_3.Name = "button_write_reg_3";
            button_write_reg_3.Size = new Size(64, 26);
            button_write_reg_3.TabIndex = 55;
            button_write_reg_3.Text = "쓰기";
            button_write_reg_3.UseVisualStyleBackColor = true;
            // 
            // button_read_reg_2
            // 
            button_read_reg_2.Location = new Point(367, 74);
            button_read_reg_2.Name = "button_read_reg_2";
            button_read_reg_2.Size = new Size(64, 26);
            button_read_reg_2.TabIndex = 54;
            button_read_reg_2.Text = "읽기";
            button_read_reg_2.UseVisualStyleBackColor = true;
            // 
            // button_write_reg_2
            // 
            button_write_reg_2.Location = new Point(297, 74);
            button_write_reg_2.Name = "button_write_reg_2";
            button_write_reg_2.Size = new Size(64, 26);
            button_write_reg_2.TabIndex = 53;
            button_write_reg_2.Text = "쓰기";
            button_write_reg_2.UseVisualStyleBackColor = true;
            // 
            // button_read_reg_1
            // 
            button_read_reg_1.Location = new Point(367, 45);
            button_read_reg_1.Name = "button_read_reg_1";
            button_read_reg_1.Size = new Size(64, 26);
            button_read_reg_1.TabIndex = 52;
            button_read_reg_1.Text = "읽기";
            button_read_reg_1.UseVisualStyleBackColor = true;
            // 
            // button_write_reg_1
            // 
            button_write_reg_1.Location = new Point(297, 45);
            button_write_reg_1.Name = "button_write_reg_1";
            button_write_reg_1.Size = new Size(64, 26);
            button_write_reg_1.TabIndex = 51;
            button_write_reg_1.Text = "쓰기";
            button_write_reg_1.UseVisualStyleBackColor = true;
            // 
            // button_read_reg_0
            // 
            button_read_reg_0.Location = new Point(367, 16);
            button_read_reg_0.Name = "button_read_reg_0";
            button_read_reg_0.Size = new Size(64, 26);
            button_read_reg_0.TabIndex = 50;
            button_read_reg_0.Text = "읽기";
            button_read_reg_0.UseVisualStyleBackColor = true;
            button_read_reg_0.Click += button_read_reg_0_Click;
            // 
            // button_write_reg_0
            // 
            button_write_reg_0.Location = new Point(297, 16);
            button_write_reg_0.Name = "button_write_reg_0";
            button_write_reg_0.Size = new Size(64, 26);
            button_write_reg_0.TabIndex = 49;
            button_write_reg_0.Text = "쓰기";
            button_write_reg_0.UseVisualStyleBackColor = true;
            button_write_reg_0.Click += button_write_reg_0_Click;
            // 
            // label18
            // 
            label18.Location = new Point(6, 164);
            label18.Name = "label18";
            label18.Size = new Size(48, 23);
            label18.TabIndex = 48;
            label18.Text = "값 5 :";
            label18.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label19
            // 
            label19.Location = new Point(6, 19);
            label19.Name = "label19";
            label19.Size = new Size(48, 23);
            label19.TabIndex = 38;
            label19.Text = "값 0 :";
            label19.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label23
            // 
            label23.Location = new Point(6, 106);
            label23.Name = "label23";
            label23.Size = new Size(48, 23);
            label23.TabIndex = 44;
            label23.Text = "값 3 :";
            label23.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_reg_5
            // 
            textBox_reg_5.Location = new Point(60, 164);
            textBox_reg_5.Name = "textBox_reg_5";
            textBox_reg_5.Size = new Size(211, 23);
            textBox_reg_5.TabIndex = 47;
            // 
            // textBox_reg_1
            // 
            textBox_reg_1.Location = new Point(60, 48);
            textBox_reg_1.Name = "textBox_reg_1";
            textBox_reg_1.Size = new Size(211, 23);
            textBox_reg_1.TabIndex = 39;
            // 
            // textBox_reg_2
            // 
            textBox_reg_2.Location = new Point(60, 77);
            textBox_reg_2.Name = "textBox_reg_2";
            textBox_reg_2.Size = new Size(211, 23);
            textBox_reg_2.TabIndex = 41;
            // 
            // textBox_reg_3
            // 
            textBox_reg_3.Location = new Point(60, 106);
            textBox_reg_3.Name = "textBox_reg_3";
            textBox_reg_3.Size = new Size(211, 23);
            textBox_reg_3.TabIndex = 43;
            // 
            // label20
            // 
            label20.Location = new Point(6, 135);
            label20.Name = "label20";
            label20.Size = new Size(48, 23);
            label20.TabIndex = 46;
            label20.Text = "값 4 :";
            label20.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_reg_4
            // 
            textBox_reg_4.Location = new Point(60, 135);
            textBox_reg_4.Name = "textBox_reg_4";
            textBox_reg_4.Size = new Size(211, 23);
            textBox_reg_4.TabIndex = 45;
            // 
            // label21
            // 
            label21.Location = new Point(6, 77);
            label21.Name = "label21";
            label21.Size = new Size(48, 23);
            label21.TabIndex = 42;
            label21.Text = "값 2 :";
            label21.TextAlign = ContentAlignment.MiddleRight;
            // 
            // label22
            // 
            label22.Location = new Point(6, 48);
            label22.Name = "label22";
            label22.Size = new Size(48, 23);
            label22.TabIndex = 40;
            label22.Text = "값 1 :";
            label22.TextAlign = ContentAlignment.MiddleRight;
            // 
            // textBox_reg_0
            // 
            textBox_reg_0.Location = new Point(60, 19);
            textBox_reg_0.Name = "textBox_reg_0";
            textBox_reg_0.Size = new Size(211, 23);
            textBox_reg_0.TabIndex = 37;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(885, 878);
            Controls.Add(groupBox5);
            Controls.Add(groupBox4);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Name = "MainForm";
            Text = "메인화면";
            Load += MainForm_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView_report).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            groupBox4.ResumeLayout(false);
            groupBox4.PerformLayout();
            groupBox5.ResumeLayout(false);
            groupBox5.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dataGridView_report;
        private DataGridViewTextBoxColumn Column1;
        private DataGridViewTextBoxColumn Column2;
        private DataGridViewTextBoxColumn Column3;
        private DataGridViewTextBoxColumn Column4;
        private DataGridViewTextBoxColumn Column5;
        private DataGridViewTextBoxColumn Column6;
        private Button button_delete_selected_reports;
        private Button button_export_csv_selected_reports;
        private Button button_inspection;
        private GroupBox groupBox1;
        private TextBox textBox_address;
        private TextBox textBox_port;
        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox textBox_value_min_1;
        private Label label4;
        private TextBox textBox_value_max_1;
        private Label label5;
        private TextBox textBox_value_max_2;
        private Label label6;
        private TextBox textBox_value_min_2;
        private Label label7;
        private TextBox textBox_value_max_3;
        private Label label8;
        private TextBox textBox_value_min_3;
        private Button button_apply_and_save;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private Label label17;
        private Button button_disconnect;
        private TextBox textBox_connection_status;
        private Button button_connect;
        private Label label9;
        private TextBox textBox_applied_address;
        private Label label10;
        private TextBox textBox_applied_port;
        private GroupBox groupBox4;
        private Label label11;
        private Label label13;
        private TextBox textBox_realtime_data_5;
        private TextBox textBox_realtime_data_2;
        private Label label12;
        private Label label16;
        private TextBox textBox_realtime_data_0;
        private Label label15;
        private TextBox textBox_realtime_data_4;
        private TextBox textBox_realtime_data_3;
        private TextBox textBox_realtime_data_1;
        private Label label14;
        private GroupBox groupBox5;
        private Label label18;
        private Label label19;
        private TextBox textBox_reg_5;
        private TextBox textBox_reg_2;
        private Label label20;
        private Label label21;
        private TextBox textBox_reg_0;
        private Label label22;
        private TextBox textBox_reg_4;
        private TextBox textBox_reg_3;
        private TextBox textBox_reg_1;
        private Label label23;
        private Button button_write_reg_0;
        private TextBox textBox_retry_count;
        private Label label24;
        private Button button_read_reg_5;
        private Button button_write_reg_5;
        private Button button_read_reg_4;
        private Button button_write_reg_4;
        private Button button_read_reg_3;
        private Button button_write_reg_3;
        private Button button_read_reg_2;
        private Button button_write_reg_2;
        private Button button_read_reg_1;
        private Button button_write_reg_1;
        private Button button_read_reg_0;
    }
}
