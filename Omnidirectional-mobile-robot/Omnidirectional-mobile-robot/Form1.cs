﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//  SerialPort
using System.IO;
using System.IO.Ports;
using System.Xml;
namespace Omnidirectional_mobile_robot
{
    public partial class Form1 : Form
    {
        public
        string InputData = String.Empty; // Khai báo string buff dùng cho hiển thị dữ liệu sau này.
        public Form1()
        {
            InitializeComponent();
            // Khai báo hàm delegate bằng phương thức DataReceived của Object SerialPort;
            // Cái này khi có sự kiện nhận dữ liệu sẽ nhảy đến phương thức DataReceive
            // Nếu ko hiểu đoạn này bạn có thể tìm hiểu về Delegate, còn ko cứ COPY . Ko cần quan tâm
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(DataReceive);
            string[] BaudRate = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };
            comboBox2.Items.AddRange(BaudRate);
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            switch (keyData)
            {
                case Keys.Enter:
                    Connect.PerformClick();
                    return true;
                case Keys.Escape:
                    this.Close();
                    return true;
                case Keys.Back:
                    refresh.PerformClick();
                    return true;
                case Keys.Down:
                    try {
                        comboBox1.SelectedIndex = ++comboBox1.SelectedIndex;   
                    }
                    catch { };
                    return true;
                case Keys.Up:
                        if (comboBox1.SelectedIndex > 0) comboBox1.SelectedIndex = --comboBox1.SelectedIndex;
                    return true;
                case Keys.Left:
                    try
                    {
                        if (comboBox2.SelectedIndex > 0) comboBox2.SelectedIndex = --comboBox2.SelectedIndex;
                    }
                    catch { };
                    return true;
                case Keys.Right:
                    try
                    {
                        if (comboBox2.SelectedIndex <8) comboBox2.SelectedIndex = ++comboBox2.SelectedIndex;
                    }
                    catch { };
                    return true;
                default:
                    return false;
            }
        }
        public void DataReceive(object obj, SerialDataReceivedEventArgs e)
        {
            InputData = serialPort1.ReadExisting();
            return;
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox2.SelectedIndex = 3;
            comboBox1.DataSource = SerialPort.GetPortNames();
            serialPort1.ReadTimeout = 500;
            serialPort1.WriteTimeout = 500;
            checkOpen();
        }

        private void Connect_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialPort1.IsOpen)
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.Open();
                    Connect.Text = "Ngắt Kết Nối";
                    checkOpen();
                }
                else
                {
                    serialPort1.Close();
                    Connect.Text = "Kết Nối";
                    checkOpen();
                }
            }
            catch
            {
                MessageBox.Show("Kết Nối Bị Lỗi !\n Có Thể Cổng Đã Được Kết Nối Hoặc Không Có Cổng !!!", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

            
        }
        private void checkOpen()
        {
            if (!serialPort1.IsOpen)
            {
                Status.Text = ("Chưa Kết Nối");
                Status.ForeColor = Color.Red;
                this.refresh.Enabled = true;
                this.flowLayoutPanel.Enabled = false;
                this.comboBox1.Enabled = true;
                this.comboBox2.Enabled = true;
                Connect.Text = "Kết Nối";
            }
            else if (serialPort1.IsOpen)
            {
                Status.Text = ("Xe Chưa Kết Nối");
                Connect.Text = "Ngắt Kết Nối";
                this.refresh.Enabled = false;
                this.comboBox1.Enabled = false;
                this.comboBox2.Enabled = false;
            }
        }
        private void refresh_Click(object sender, EventArgs e)
        {
            comboBox1.Text = null;
            comboBox1.DataSource = SerialPort.GetPortNames();
            checkOpen();
        }
        private void enabel_button()
        {
            flowLayoutPanel.Enabled = true;
            Connect.Enabled = true;
            button3.BackColor = SystemColors.Control;
            button4.BackColor = SystemColors.Control;
            button5.BackColor = SystemColors.Control;
            button6.BackColor = SystemColors.Control;
            button7.BackColor = SystemColors.Control;
            button8.BackColor = SystemColors.Control;
            button9.BackColor = SystemColors.Control;
            button10.BackColor = SystemColors.Control;
            button11.BackColor = SystemColors.Control;
            button12.BackColor = SystemColors.Control;
            button13.BackColor = SystemColors.Control;
            button14.BackColor = SystemColors.Control;
            button15.BackColor = SystemColors.Control;
            button16.BackColor = SystemColors.Control;
            button17.BackColor = SystemColors.Control;
            button18.BackColor = SystemColors.Control;
            button19.BackColor = SystemColors.Control;
            button20.BackColor = SystemColors.Control;
            button21.BackColor = SystemColors.Control;
            button22.BackColor = SystemColors.Control;
            button23.BackColor = SystemColors.Control;
            button24.BackColor = SystemColors.Control;
            button25.BackColor = SystemColors.Control;
            button26.BackColor = SystemColors.Control;
            button27.BackColor = SystemColors.Control;
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (InputData != string.Empty) Data.Text = InputData;
            if (serialPort1.IsOpen)
                switch (InputData)
                {
                    case "1":
                        flowLayoutPanel.Enabled = false;
                        Connect.Enabled = false;
                        break;
                    case "0":
                        enabel_button();
                        break;
                    case "HELLO!!!":
                        Status.Text = ("Xe Đã Kết Nối");
                        Status.ForeColor = Color.Green;
                        enabel_button();
                        try
                        {
                            serialPort1.Write("OK");
                        }
                        catch (Exception)
                        {
                            MessageBox.Show("Data Send Error !!!", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                        break;
                    case "0:0":
                        button3.BackColor = Color.Green;
                        break;
                    case "0:1":
                        button4.BackColor = Color.Green;
                        break;
                    case "0:2":
                        button5.BackColor = Color.Green;
                        break;
                    case "0:3":
                        button6.BackColor = Color.Green;
                        break;
                    case "0:4":
                        button7.BackColor = Color.Green;
                        break;
                    case "1:0":
                        button8.BackColor = Color.Green;
                        break;
                    case "1:1":
                        button9.BackColor = Color.Green;
                        break;
                    case "1:2":
                        button10.BackColor = Color.Green;
                        break;
                    case "1:3":
                        button11.BackColor = Color.Green;
                        break;
                    case "1:4":
                        button12.BackColor = Color.Green;
                        break;
                    case "2:0":
                        button13.BackColor = Color.Green;
                        break;
                    case "2:1":
                        button14.BackColor = Color.Green;
                        break;
                    case "2:2":
                        button15.BackColor = Color.Green;
                        break;
                    case "2:3":
                        button16.BackColor = Color.Green;
                        break;
                    case "2:4":
                        button17.BackColor = Color.Green;
                        break;
                    case "3:0":
                        button18.BackColor = Color.Green;
                        break;
                    case "3:1":
                        button20.BackColor = Color.Green;
                        break;
                    case "3:2":
                        button21.BackColor = Color.Green;
                        break;
                    case "3:3":
                        button22.BackColor = Color.Green;
                        break;
                    case "3:4":
                        button23.BackColor = Color.Green;
                        break;
                    case "4:0":
                        button19.BackColor = Color.Green;
                        break;
                    case "4:1":
                        button24.BackColor = Color.Green;
                        break;
                    case "4:2":
                        button25.BackColor = Color.Green;
                        break;
                    case "4:3":
                        button26.BackColor = Color.Green;
                        break;
                    case "4:4":
                        button27.BackColor = Color.Green;
                        break;
                    default:
                        break;
                }
            else checkOpen();
            InputData = string.Empty;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            serialPort1.Write("00.");
            button3.BackColor = Color.Red;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            serialPort1.Write("01.");
            button4.BackColor = Color.Red;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            serialPort1.Write("02.");
            button5.BackColor = Color.Red;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            serialPort1.Write("03.");
            button6.BackColor = Color.Red;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            serialPort1.Write("04.");
            button7.BackColor = Color.Red;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            serialPort1.Write("10.");
            button8.BackColor = Color.Red;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            serialPort1.Write("11.");
            button9.BackColor = Color.Red;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            serialPort1.Write("12.");
            button10.BackColor = Color.Red;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            serialPort1.Write("13.");
            button11.BackColor = Color.Red;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            serialPort1.Write("14.");
            button12.BackColor = Color.Red;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            serialPort1.Write("20.");
            button13.BackColor = Color.Red;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            serialPort1.Write("21.");
            button14.BackColor = Color.Red;
        }

        private void button15_Click(object sender, EventArgs e)
        {
            serialPort1.Write("22.");
            button15.BackColor = Color.Red;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            serialPort1.Write("23.");
            button16.BackColor = Color.Red;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            serialPort1.Write("24.");
            button17.BackColor = Color.Red;
        }

        private void button18_Click(object sender, EventArgs e)
        {
            serialPort1.Write("30.");
            button18.BackColor = Color.Red;
        }

        private void button20_Click(object sender, EventArgs e)
        {
            serialPort1.Write("31.");
            button20.BackColor = Color.Red;
        }

        private void button21_Click(object sender, EventArgs e)
        {
            serialPort1.Write("32.");
            button21.BackColor = Color.Red;
        }

        private void button22_Click(object sender, EventArgs e)
        {
            serialPort1.Write("33.");
            button22.BackColor = Color.Red;
        }

        private void button23_Click(object sender, EventArgs e)
        {
            serialPort1.Write("34.");
            button23.BackColor = Color.Red;
        }

        private void button19_Click(object sender, EventArgs e)
        {
            serialPort1.Write("40.");
            button19.BackColor = Color.Red;
        }

        private void button24_Click(object sender, EventArgs e)
        {
            serialPort1.Write("41.");
            button24.BackColor = Color.Red;
        }

        private void button25_Click(object sender, EventArgs e)
        {
            serialPort1.Write("42.");
            button25.BackColor = Color.Red;
        }

        private void button26_Click(object sender, EventArgs e)
        {
            serialPort1.Write("43.");
            button26.BackColor = Color.Red;
        }

        private void button27_Click(object sender, EventArgs e)
        {
            serialPort1.Write("44.");
            button27.BackColor = Color.Red;
        }
        
    }
}