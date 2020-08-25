using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Omnidirectional_mobile_robot_V2
{
    public partial class ConnectCOM : Form
    {
        string InputData;
        public ConnectCOM()
        {
            InitializeComponent();
        }
        private void Connect_Load(object sender, EventArgs e)
        {

            string[] BaudRate = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };
            comboBox2.Items.AddRange(BaudRate);
            comboBox2.SelectedIndex = 3;
            comboBox1.DataSource = SerialPort.GetPortNames();
        }
        public void DataReceive(object obj, SerialDataReceivedEventArgs e)
        {
            Thread.Sleep(5);
            InputData = serialPort1.ReadExisting();
            return;
        }
        private void ConnectButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialPort1.IsOpen)
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.Open();
                    serialPort1.Write("OK! ");
                    int T = 0;
                    while (InputData != "OK!")
                    {
                        T++;
                        if (T > 2000)
                        {
                            serialPort1.Close();
                            MessageBox.Show("TimeOut!!!");
                            return;
                        }
                        Thread.Sleep(1);
                    }
                    InputData = null;
                    serialPort1.Close();
                    DashBoard control = new DashBoard(serialPort1.PortName, serialPort1.BaudRate);
                    this.TopMost = false;
                    this.Hide();
                    control.TopMost = true;
                    control.StartPosition = FormStartPosition.CenterScreen;
                    control.ShowDialog();
                    this.TopMost = true;
                    refresh_Click(null, null);
                    this.Show();
                }
                else
                {
                    serialPort1.Close();
                }
            }
            catch
            {
                MessageBox.Show("Kết Nối Bị Lỗi !\n Có Thể Cổng COM Đã Được Dùng Hoặc Chưa Kết Nối !!!", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void label1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void refresh_Click(object sender, EventArgs e)
        {
            comboBox1.DataSource = null;
            comboBox1.DataSource = SerialPort.GetPortNames();
        }

        bool SttMouse;
        int movX, movY;

        private void ConnectCOM_MouseDown(object sender, MouseEventArgs e)
        {
            SttMouse = true;
            movX = e.X;
            movY = e.Y;
        }

        private void ConnectCOM_MouseMove(object sender, MouseEventArgs e)
        {
            if (SttMouse) this.SetDesktopLocation(MousePosition.X - movX, MousePosition.Y - movY);
        }

        private void ConnectCOM_MouseUp(object sender, MouseEventArgs e)
        {
            SttMouse = false;
        }
    }
}
