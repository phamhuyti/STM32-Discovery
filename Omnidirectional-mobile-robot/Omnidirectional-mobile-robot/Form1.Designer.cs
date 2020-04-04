namespace Omnidirectional_mobile_robot
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.Status = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.refresh = new System.Windows.Forms.Button();
            this.Connect = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button17 = new System.Windows.Forms.Button();
            this.button16 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button27 = new System.Windows.Forms.Button();
            this.button26 = new System.Windows.Forms.Button();
            this.button25 = new System.Windows.Forms.Button();
            this.button24 = new System.Windows.Forms.Button();
            this.button19 = new System.Windows.Forms.Button();
            this.button23 = new System.Windows.Forms.Button();
            this.button22 = new System.Windows.Forms.Button();
            this.button21 = new System.Windows.Forms.Button();
            this.button20 = new System.Windows.Forms.Button();
            this.button18 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Data = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.flowLayoutPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button28 = new System.Windows.Forms.Button();
            this.button29 = new System.Windows.Forms.Button();
            this.button30 = new System.Windows.Forms.Button();
            this.button31 = new System.Windows.Forms.Button();
            this.button32 = new System.Windows.Forms.Button();
            this.button33 = new System.Windows.Forms.Button();
            this.button34 = new System.Windows.Forms.Button();
            this.button35 = new System.Windows.Forms.Button();
            this.button36 = new System.Windows.Forms.Button();
            this.groupBox = new System.Windows.Forms.GroupBox();
            this.Reset = new System.Windows.Forms.Button();
            this.flowLayoutPanel.SuspendLayout();
            this.groupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // Status
            // 
            this.Status.AutoSize = true;
            this.Status.Location = new System.Drawing.Point(12, 124);
            this.Status.Name = "Status";
            this.Status.Size = new System.Drawing.Size(37, 13);
            this.Status.TabIndex = 0;
            this.Status.Text = "Status";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(12, 39);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(157, 21);
            this.comboBox2.TabIndex = 3;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(12, 12);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(157, 21);
            this.comboBox1.TabIndex = 4;
            // 
            // refresh
            // 
            this.refresh.Location = new System.Drawing.Point(93, 66);
            this.refresh.Name = "refresh";
            this.refresh.Size = new System.Drawing.Size(76, 24);
            this.refresh.TabIndex = 26;
            this.refresh.Text = "Làm Mới";
            this.refresh.UseVisualStyleBackColor = true;
            this.refresh.Click += new System.EventHandler(this.refresh_Click);
            // 
            // Connect
            // 
            this.Connect.Location = new System.Drawing.Point(12, 66);
            this.Connect.Name = "Connect";
            this.Connect.Size = new System.Drawing.Size(76, 24);
            this.Connect.TabIndex = 24;
            this.Connect.Text = "Kết nối";
            this.Connect.UseVisualStyleBackColor = true;
            this.Connect.Click += new System.EventHandler(this.Connect_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(147, 3);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(30, 30);
            this.button7.TabIndex = 0;
            this.button7.Text = "0:4";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(75, 3);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(30, 30);
            this.button5.TabIndex = 0;
            this.button5.Text = "0:2";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(111, 3);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(30, 30);
            this.button6.TabIndex = 0;
            this.button6.Text = "0:3";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(39, 3);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(30, 30);
            this.button4.TabIndex = 0;
            this.button4.Text = "0:1";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(147, 39);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(30, 30);
            this.button12.TabIndex = 0;
            this.button12.Text = "1:4";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(111, 39);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(30, 30);
            this.button11.TabIndex = 0;
            this.button11.Text = "1:3";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(39, 39);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(30, 30);
            this.button9.TabIndex = 0;
            this.button9.Text = "1:1";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(75, 39);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(30, 30);
            this.button10.TabIndex = 0;
            this.button10.Text = "1:2";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // button17
            // 
            this.button17.Location = new System.Drawing.Point(147, 75);
            this.button17.Name = "button17";
            this.button17.Size = new System.Drawing.Size(30, 30);
            this.button17.TabIndex = 0;
            this.button17.Text = "2:4";
            this.button17.UseVisualStyleBackColor = true;
            this.button17.Click += new System.EventHandler(this.button17_Click);
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(111, 75);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(30, 30);
            this.button16.TabIndex = 0;
            this.button16.Text = "2:3";
            this.button16.UseVisualStyleBackColor = true;
            this.button16.Click += new System.EventHandler(this.button16_Click);
            // 
            // button15
            // 
            this.button15.Location = new System.Drawing.Point(75, 75);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(30, 30);
            this.button15.TabIndex = 0;
            this.button15.Text = "2:2";
            this.button15.UseVisualStyleBackColor = true;
            this.button15.Click += new System.EventHandler(this.button15_Click);
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(39, 75);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(30, 30);
            this.button14.TabIndex = 0;
            this.button14.Text = "2:1";
            this.button14.UseVisualStyleBackColor = true;
            this.button14.Click += new System.EventHandler(this.button14_Click);
            // 
            // button27
            // 
            this.button27.Location = new System.Drawing.Point(147, 147);
            this.button27.Name = "button27";
            this.button27.Size = new System.Drawing.Size(30, 30);
            this.button27.TabIndex = 0;
            this.button27.Text = "4:4";
            this.button27.UseVisualStyleBackColor = true;
            this.button27.Click += new System.EventHandler(this.button27_Click);
            // 
            // button26
            // 
            this.button26.Location = new System.Drawing.Point(111, 147);
            this.button26.Name = "button26";
            this.button26.Size = new System.Drawing.Size(30, 30);
            this.button26.TabIndex = 0;
            this.button26.Text = "4:3";
            this.button26.UseVisualStyleBackColor = true;
            this.button26.Click += new System.EventHandler(this.button26_Click);
            // 
            // button25
            // 
            this.button25.Location = new System.Drawing.Point(75, 147);
            this.button25.Name = "button25";
            this.button25.Size = new System.Drawing.Size(30, 30);
            this.button25.TabIndex = 0;
            this.button25.Text = "4:2";
            this.button25.UseVisualStyleBackColor = true;
            this.button25.Click += new System.EventHandler(this.button25_Click);
            // 
            // button24
            // 
            this.button24.Location = new System.Drawing.Point(39, 147);
            this.button24.Name = "button24";
            this.button24.Size = new System.Drawing.Size(30, 30);
            this.button24.TabIndex = 0;
            this.button24.Text = "4:1";
            this.button24.UseVisualStyleBackColor = true;
            this.button24.Click += new System.EventHandler(this.button24_Click);
            // 
            // button19
            // 
            this.button19.Location = new System.Drawing.Point(3, 147);
            this.button19.Name = "button19";
            this.button19.Size = new System.Drawing.Size(30, 30);
            this.button19.TabIndex = 0;
            this.button19.Text = "4:0";
            this.button19.UseVisualStyleBackColor = true;
            this.button19.Click += new System.EventHandler(this.button19_Click);
            // 
            // button23
            // 
            this.button23.Location = new System.Drawing.Point(147, 111);
            this.button23.Name = "button23";
            this.button23.Size = new System.Drawing.Size(30, 30);
            this.button23.TabIndex = 0;
            this.button23.Text = "3:4";
            this.button23.UseVisualStyleBackColor = true;
            this.button23.Click += new System.EventHandler(this.button23_Click);
            // 
            // button22
            // 
            this.button22.Location = new System.Drawing.Point(111, 111);
            this.button22.Name = "button22";
            this.button22.Size = new System.Drawing.Size(30, 30);
            this.button22.TabIndex = 0;
            this.button22.Text = "3:3";
            this.button22.UseVisualStyleBackColor = true;
            this.button22.Click += new System.EventHandler(this.button22_Click);
            // 
            // button21
            // 
            this.button21.Location = new System.Drawing.Point(75, 111);
            this.button21.Name = "button21";
            this.button21.Size = new System.Drawing.Size(30, 30);
            this.button21.TabIndex = 0;
            this.button21.Text = "3:2";
            this.button21.UseVisualStyleBackColor = true;
            this.button21.Click += new System.EventHandler(this.button21_Click);
            // 
            // button20
            // 
            this.button20.Location = new System.Drawing.Point(39, 111);
            this.button20.Name = "button20";
            this.button20.Size = new System.Drawing.Size(30, 30);
            this.button20.TabIndex = 0;
            this.button20.Text = "3:1";
            this.button20.UseVisualStyleBackColor = true;
            this.button20.Click += new System.EventHandler(this.button20_Click);
            // 
            // button18
            // 
            this.button18.Location = new System.Drawing.Point(3, 111);
            this.button18.Name = "button18";
            this.button18.Size = new System.Drawing.Size(30, 30);
            this.button18.TabIndex = 0;
            this.button18.Text = "3:0";
            this.button18.UseVisualStyleBackColor = true;
            this.button18.Click += new System.EventHandler(this.button18_Click);
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(3, 75);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(30, 30);
            this.button13.TabIndex = 0;
            this.button13.Text = "2:0";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(3, 39);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(30, 30);
            this.button8.TabIndex = 0;
            this.button8.Text = "1:0";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(3, 3);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(30, 30);
            this.button3.TabIndex = 0;
            this.button3.Text = "0:0";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Data
            // 
            this.Data.AutoSize = true;
            this.Data.Location = new System.Drawing.Point(91, 143);
            this.Data.Name = "Data";
            this.Data.Size = new System.Drawing.Size(0, 13);
            this.Data.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 143);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(62, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Data Nhận:";
            // 
            // flowLayoutPanel
            // 
            this.flowLayoutPanel.Controls.Add(this.button3);
            this.flowLayoutPanel.Controls.Add(this.button4);
            this.flowLayoutPanel.Controls.Add(this.button5);
            this.flowLayoutPanel.Controls.Add(this.button6);
            this.flowLayoutPanel.Controls.Add(this.button7);
            this.flowLayoutPanel.Controls.Add(this.button8);
            this.flowLayoutPanel.Controls.Add(this.button9);
            this.flowLayoutPanel.Controls.Add(this.button10);
            this.flowLayoutPanel.Controls.Add(this.button11);
            this.flowLayoutPanel.Controls.Add(this.button12);
            this.flowLayoutPanel.Controls.Add(this.button13);
            this.flowLayoutPanel.Controls.Add(this.button14);
            this.flowLayoutPanel.Controls.Add(this.button15);
            this.flowLayoutPanel.Controls.Add(this.button16);
            this.flowLayoutPanel.Controls.Add(this.button17);
            this.flowLayoutPanel.Controls.Add(this.button18);
            this.flowLayoutPanel.Controls.Add(this.button20);
            this.flowLayoutPanel.Controls.Add(this.button21);
            this.flowLayoutPanel.Controls.Add(this.button22);
            this.flowLayoutPanel.Controls.Add(this.button23);
            this.flowLayoutPanel.Controls.Add(this.button19);
            this.flowLayoutPanel.Controls.Add(this.button24);
            this.flowLayoutPanel.Controls.Add(this.button25);
            this.flowLayoutPanel.Controls.Add(this.button26);
            this.flowLayoutPanel.Controls.Add(this.button27);
            this.flowLayoutPanel.Location = new System.Drawing.Point(175, 12);
            this.flowLayoutPanel.Name = "flowLayoutPanel";
            this.flowLayoutPanel.Size = new System.Drawing.Size(180, 181);
            this.flowLayoutPanel.TabIndex = 28;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(76, 39);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(30, 30);
            this.button1.TabIndex = 29;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(76, 75);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(30, 30);
            this.button2.TabIndex = 30;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button28
            // 
            this.button28.Location = new System.Drawing.Point(112, 75);
            this.button28.Name = "button28";
            this.button28.Size = new System.Drawing.Size(30, 30);
            this.button28.TabIndex = 31;
            this.button28.Text = "button28";
            this.button28.UseVisualStyleBackColor = true;
            this.button28.Click += new System.EventHandler(this.button28_Click);
            // 
            // button29
            // 
            this.button29.Location = new System.Drawing.Point(40, 75);
            this.button29.Name = "button29";
            this.button29.Size = new System.Drawing.Size(30, 30);
            this.button29.TabIndex = 32;
            this.button29.Text = "button29";
            this.button29.UseVisualStyleBackColor = true;
            this.button29.Click += new System.EventHandler(this.button29_Click);
            // 
            // button30
            // 
            this.button30.Location = new System.Drawing.Point(76, 112);
            this.button30.Name = "button30";
            this.button30.Size = new System.Drawing.Size(30, 30);
            this.button30.TabIndex = 33;
            this.button30.Text = "button30";
            this.button30.UseVisualStyleBackColor = true;
            this.button30.Click += new System.EventHandler(this.button30_Click);
            // 
            // button31
            // 
            this.button31.Location = new System.Drawing.Point(40, 39);
            this.button31.Name = "button31";
            this.button31.Size = new System.Drawing.Size(30, 30);
            this.button31.TabIndex = 34;
            this.button31.Text = "button31";
            this.button31.UseVisualStyleBackColor = true;
            this.button31.Click += new System.EventHandler(this.button31_Click);
            // 
            // button32
            // 
            this.button32.Location = new System.Drawing.Point(112, 39);
            this.button32.Name = "button32";
            this.button32.Size = new System.Drawing.Size(30, 30);
            this.button32.TabIndex = 35;
            this.button32.Text = "button32";
            this.button32.UseVisualStyleBackColor = true;
            this.button32.Click += new System.EventHandler(this.button32_Click);
            // 
            // button33
            // 
            this.button33.Location = new System.Drawing.Point(40, 111);
            this.button33.Name = "button33";
            this.button33.Size = new System.Drawing.Size(30, 30);
            this.button33.TabIndex = 36;
            this.button33.Text = "button33";
            this.button33.UseVisualStyleBackColor = true;
            this.button33.Click += new System.EventHandler(this.button33_Click);
            // 
            // button34
            // 
            this.button34.Location = new System.Drawing.Point(112, 111);
            this.button34.Name = "button34";
            this.button34.Size = new System.Drawing.Size(30, 30);
            this.button34.TabIndex = 37;
            this.button34.Text = "button34";
            this.button34.UseVisualStyleBackColor = true;
            this.button34.Click += new System.EventHandler(this.button34_Click);
            // 
            // button35
            // 
            this.button35.Location = new System.Drawing.Point(148, 75);
            this.button35.Name = "button35";
            this.button35.Size = new System.Drawing.Size(30, 30);
            this.button35.TabIndex = 38;
            this.button35.Text = "button35";
            this.button35.UseVisualStyleBackColor = true;
            this.button35.Click += new System.EventHandler(this.button35_Click);
            // 
            // button36
            // 
            this.button36.Location = new System.Drawing.Point(4, 75);
            this.button36.Name = "button36";
            this.button36.Size = new System.Drawing.Size(30, 30);
            this.button36.TabIndex = 39;
            this.button36.Text = "button36";
            this.button36.UseVisualStyleBackColor = true;
            this.button36.Click += new System.EventHandler(this.button36_Click);
            // 
            // groupBox
            // 
            this.groupBox.Controls.Add(this.button34);
            this.groupBox.Controls.Add(this.button36);
            this.groupBox.Controls.Add(this.button1);
            this.groupBox.Controls.Add(this.button35);
            this.groupBox.Controls.Add(this.button2);
            this.groupBox.Controls.Add(this.button28);
            this.groupBox.Controls.Add(this.button33);
            this.groupBox.Controls.Add(this.button29);
            this.groupBox.Controls.Add(this.button32);
            this.groupBox.Controls.Add(this.button30);
            this.groupBox.Controls.Add(this.button31);
            this.groupBox.Location = new System.Drawing.Point(361, 12);
            this.groupBox.Name = "groupBox";
            this.groupBox.Size = new System.Drawing.Size(201, 153);
            this.groupBox.TabIndex = 40;
            this.groupBox.TabStop = false;
            // 
            // Reset
            // 
            this.Reset.Location = new System.Drawing.Point(12, 96);
            this.Reset.Name = "Reset";
            this.Reset.Size = new System.Drawing.Size(76, 24);
            this.Reset.TabIndex = 41;
            this.Reset.Text = "Reset";
            this.Reset.UseVisualStyleBackColor = true;
            this.Reset.Click += new System.EventHandler(this.Reset_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(568, 251);
            this.Controls.Add(this.Reset);
            this.Controls.Add(this.groupBox);
            this.Controls.Add(this.flowLayoutPanel);
            this.Controls.Add(this.refresh);
            this.Controls.Add(this.Connect);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.Data);
            this.Controls.Add(this.Status);
            this.Name = "Form1";
            this.Text = "Omnidirectional Mobile Robot";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.flowLayoutPanel.ResumeLayout(false);
            this.groupBox.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label Status;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button refresh;
        private System.Windows.Forms.Button Connect;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button17;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button19;
        private System.Windows.Forms.Button button23;
        private System.Windows.Forms.Button button22;
        private System.Windows.Forms.Button button21;
        private System.Windows.Forms.Button button20;
        private System.Windows.Forms.Button button18;
        private System.Windows.Forms.Button button27;
        private System.Windows.Forms.Button button26;
        private System.Windows.Forms.Button button25;
        private System.Windows.Forms.Button button24;
        private System.Windows.Forms.Label Data;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button28;
        private System.Windows.Forms.Button button29;
        private System.Windows.Forms.Button button30;
        private System.Windows.Forms.Button button31;
        private System.Windows.Forms.Button button32;
        private System.Windows.Forms.Button button33;
        private System.Windows.Forms.Button button34;
        private System.Windows.Forms.Button button35;
        private System.Windows.Forms.Button button36;
        private System.Windows.Forms.GroupBox groupBox;
        private System.Windows.Forms.Button Reset;
    }
}

