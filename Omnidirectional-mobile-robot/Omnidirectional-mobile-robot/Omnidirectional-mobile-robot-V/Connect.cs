using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Omnidirectional_mobile_robot_V2
{
    public partial class Connect : Form
    {
        public Connect()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] BaudRate = { "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };
            comboBox2.Items.AddRange(BaudRate);
            comboBox2.SelectedIndex = 3;
            comboBox1.DataSource = SerialPort.GetPortNames();
        }
        private void label1_Click(object sender, EventArgs e)
        {
            Close();
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
                    serialPort1.Write("RE!");
                    timer1.Enabled = true;
                }
                else
                {
                    serialPort1.Close();
                }
            }
            catch
            {
                MessageBox.Show("Kết Nối Bị Lỗi !\n Có Thể Cổng Đã Được Kết Nối Hoặc Không Có Cổng !!!", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void refresh_Click(object sender, EventArgs e)
        {
            comboBox1.DataSource = SerialPort.GetPortNames();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (this.Width>10) this.Width = this.Width - 10;
            if (this.Height > 10) this.Height = this.Height - 10;
            if(this.Width <= 10 && this.Height <= 10)
            {
                this.TopMost = false;
                this.Hide();
                //control.TopMost = true;
                //control.StartPosition = FormStartPosition.CenterScreen;
                //control.Show();
                timer1.Stop();
            }
        }
    }
}
