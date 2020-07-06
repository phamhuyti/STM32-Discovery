using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace Omnidirectional_mobile_robot_V2
{
    public partial class DashBoard : Form
    {
        string InputData = String.Empty; // Khai báo string buff dùng cho hiển thị dữ liệu sau này.
        public DashBoard(String a, int b)
        {
            InitializeComponent();
            serialPort1.PortName = a;
            serialPort1.BaudRate = b;
        }
        private void DashBoard_Load(object sender, EventArgs e)
        {
            serialPort1.Open();
            serialPort1.Write("RE!");
        }
        private void Close_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        public void DataReceive(object obj, SerialDataReceivedEventArgs e)
        {
            Thread.Sleep(5);
            InputData = serialPort1.ReadExisting();
            return;
        }
        private void Minimize_Click(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;
        }

        private void MenuSidebar_Click(object sender, EventArgs e)
        {
            if (Sidebar.Width == 130)
            {
                Sidebar.Visible = false;
                Sidebar.Width = 32;
                SidebarWrapper.Width = 52;
                AnimacionSidebar.Show(Sidebar);
            }
            else
            {
                Sidebar.Visible = false;
                Sidebar.Width = 130;
                SidebarWrapper.Width = 150;
                AnimacionSidebarBack.Show(Sidebar);
            }
        }

        private void AutoRun_Click(object sender, EventArgs e)
        {
            AutoControl.Visible = true;
            ManualControl.Visible = false;
            SettingControl.Visible = false;

            AutoControl.Enabled = true;
            ManualControl.Enabled = false;
            SettingControl.Enabled = false;
        }

        private void Manual_Click(object sender, EventArgs e)
        {
            AutoControl.Visible = false;
            ManualControl.Visible = true;
            SettingControl.Visible = false;

            AutoControl.Enabled = false;
            ManualControl.Enabled = true;
            SettingControl.Enabled = false;
        }

        private void Setting_Click(object sender, EventArgs e)
        {
            AutoControl.Visible = false;
            ManualControl.Visible = false;
            SettingControl.Visible = true;

            AutoControl.Enabled = false;
            ManualControl.Enabled = false;
            SettingControl.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                switch (InputData)
                {
                    case "Start":
                        AutoControl.Enabled = false;
                        break;
                    case "OK!":
                        serialPort1.Write("OK!");
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
                InputData = string.Empty;
            }
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
        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("01!");
        }

        private void button30_Click(object sender, EventArgs e)
        {
            serialPort1.Write("02!");
        }

        private void button29_Click(object sender, EventArgs e)
        {
            serialPort1.Write("03!");
        }

        private void button28_Click(object sender, EventArgs e)
        {
            serialPort1.Write("04!");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("00!");
        }

        private void button31_Click(object sender, EventArgs e)
        {
            serialPort1.Write("05!");
        }

        private void button32_Click(object sender, EventArgs e)
        {
            serialPort1.Write("07!");
        }

        private void button33_Click(object sender, EventArgs e)
        {
            serialPort1.Write("06!");
        }

        private void button34_Click(object sender, EventArgs e)
        {
            serialPort1.Write("08!");
        }

        private void button35_Click(object sender, EventArgs e)
        {
            serialPort1.Write("10!");
        }

        private void button36_Click(object sender, EventArgs e)
        {
            serialPort1.Write("09!");
        }
        bool SttMouse;
        int movX, movY;
        private void MenuTop_MouseDown(object sender, MouseEventArgs e)
        {
            SttMouse = true;
            movX = e.X;
            movY = e.Y;
        }

        private void MenuTop_MouseUp(object sender, MouseEventArgs e)
        {
            SttMouse = false;
        }

        private void MenuTop_MouseMove(object sender, MouseEventArgs e)
        {
            if (SttMouse) this.SetDesktopLocation(MousePosition.X - movX, MousePosition.Y - movY);
        }
    }
}
