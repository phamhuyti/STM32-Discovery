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
        string[] StepMove = new string[25];
        int _StemMove = 0;
        public DashBoard(String a, int b)
        {
            InitializeComponent();
            serialPort1.PortName = a;
            serialPort1.BaudRate = b;
        }
        private void DashBoard_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            serialPort1.Open();
        }
        private void Close_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        public void DataReceive(object obj, SerialDataReceivedEventArgs e)
        {
            Thread.Sleep(10);
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
            RUN.Visible = true;
            Reset.Visible = true;
            ManualControl.Visible = false;
            SettingControl.Visible = false;

            AutoControl.Enabled = true;
            ManualControl.Enabled = false;
            SettingControl.Enabled = false;
        }

        private void Manual_Click(object sender, EventArgs e)
        {
            AutoControl.Visible = false;
            RUN.Visible = false;
            Reset.Visible = false;
            ManualControl.Visible = true;
            SettingControl.Visible = false;

            AutoControl.Enabled = false;
            ManualControl.Enabled = true;
            SettingControl.Enabled = false;
        }

        private void Setting_Click(object sender, EventArgs e)
        {
            AutoControl.Visible = false;
            RUN.Visible = false;
            Reset.Visible = false;
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
                        RUN.Enabled = false;
                        break;
                    case "OK!":
                        serialPort1.Write("OK! ");
                        break;
                    case "RE!":
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
                    case "Stop":
                        if (StepMove[++_StemMove]== null)
                        {
                            _StemMove = 0;
                            for (int i = 0; i < 25; i++)
                            {
                                StepMove[i] = null;
                            }
                            enabel_button();
                            AutoControl.Enabled = true;
                            RUN.Enabled = true;
                        }
                        else
                        {
                            serialPort1.Write(StepMove[_StemMove]+ " ");
                        }
                        
                        break;
                    default:
                        break;
                }
                    InputData = string.Empty;
            }else
            {
                this.TopMost = false;
                this.Close();
                timer1.Enabled = false;
            }
        }
        private void RUN_Click(object sender, EventArgs e)
        {
            _StemMove = 0;
            if (StepMove[_StemMove]!=null)
            {
                serialPort1.Write(StepMove[_StemMove] + " ");
            }
            else MessageBox.Show("Vui Lòng Chọn Đường Đi!!!", "Warning", MessageBoxButtons.OK,MessageBoxIcon.Warning);
        }
        private void Reset_Click(object sender, EventArgs e)
        {
            serialPort1.Write("RE! ");
            AutoRun_Click(null, null);
            enabel_button();
            AutoControl.Enabled = true;
            RUN.Enabled = true;
        }
        private void enabel_button()
        {
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
        private void button3_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("00.");
            StepMove[_StemMove++] = "00.";
            button3.BackColor = Color.Red;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("01.");
            StepMove[_StemMove++] = "01.";
            button4.BackColor = Color.Red;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("02.");
            StepMove[_StemMove++] = "02.";
            button5.BackColor = Color.Red;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("03.");
            StepMove[_StemMove++] = "03.";
            button6.BackColor = Color.Red;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("04.");
            StepMove[_StemMove++] = "04.";
            button7.BackColor = Color.Red;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("10.");
            StepMove[_StemMove++] = "10.";
            button8.BackColor = Color.Red;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("11.");
            StepMove[_StemMove++] = "11.";
            button9.BackColor = Color.Red;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("12.");
            StepMove[_StemMove++] = "12.";
            button10.BackColor = Color.Red;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("13.");
            StepMove[_StemMove++] = "13.";
            button11.BackColor = Color.Red;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("14.");
            StepMove[_StemMove++] = "14.";
            button12.BackColor = Color.Red;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("20.");
            StepMove[_StemMove++] = "20.";
            button13.BackColor = Color.Red;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("21.");
            StepMove[_StemMove++] = "21.";
            button14.BackColor = Color.Red;
        }

        private void button15_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("22.");
            StepMove[_StemMove++] = "22.";
            button15.BackColor = Color.Red;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("23.");
            StepMove[_StemMove++] = "23.";
            button16.BackColor = Color.Red;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("24.");
            StepMove[_StemMove++] = "24.";
            button17.BackColor = Color.Red;
        }

        private void button18_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("30.");
            StepMove[_StemMove++] = "30.";
            button18.BackColor = Color.Red;
        }

        private void button20_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("31.");
            StepMove[_StemMove++] = "31.";
            button20.BackColor = Color.Red;
        }

        private void button21_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("32.");
            StepMove[_StemMove++] = "32.";
            button21.BackColor = Color.Red;
        }

        private void button22_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("33.");
            StepMove[_StemMove++] = "33.";
            button22.BackColor = Color.Red;
        }

        private void button23_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("34.");
            StepMove[_StemMove++] = "34.";
            button23.BackColor = Color.Red;
        }

        private void button19_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("40.");
            StepMove[_StemMove++] = "40.";
            button19.BackColor = Color.Red;
        }

        private void button24_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("41.");
            StepMove[_StemMove++] = "41.";
            button24.BackColor = Color.Red;
        }

        private void button25_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("42.");
            StepMove[_StemMove++] = "42.";
            button25.BackColor = Color.Red;
        }

        private void button26_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("43.");
            StepMove[_StemMove++] = "43.";
            button26.BackColor = Color.Red;
        }

        private void button27_Click(object sender, EventArgs e)
        {
            //serialPort1.Write("44.");
            StepMove[_StemMove++] = "44.";
            button27.BackColor = Color.Red;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("01! ");
        }

        private void button30_Click(object sender, EventArgs e)
        {
            serialPort1.Write("02! ");
        }

        private void button29_Click(object sender, EventArgs e)
        {
            serialPort1.Write("03! ");
        }

        private void button28_Click(object sender, EventArgs e)
        {
            serialPort1.Write("04! ");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("00! ");
        }

        private void button31_Click(object sender, EventArgs e)
        {
            serialPort1.Write("05! ");
        }

        private void button32_Click(object sender, EventArgs e)
        {
            serialPort1.Write("07! ");
        }

        private void button33_Click(object sender, EventArgs e)
        {
            serialPort1.Write("06! ");
        }

        private void button34_Click(object sender, EventArgs e)
        {
            serialPort1.Write("08! ");
        }

        private void button35_Click(object sender, EventArgs e)
        {
            serialPort1.Write("10! ");
        }

        private void button36_Click(object sender, EventArgs e)
        {
            serialPort1.Write("09! ");
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

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("00S" + (checkBox00.Checked?1:0));
        }

        private void checkBox01_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("01S" + (checkBox01.Checked ? 1 : 0));
        }

        private void checkBox02_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("02S" + (checkBox02.Checked ? 1 : 0));
        }

        private void checkBox03_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("03S" + (checkBox03.Checked ? 1 : 0));
        }

        private void checkBox04_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("04S" + (checkBox04.Checked ? 1 : 0));
        }

        private void checkBox10_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("10S" + (checkBox10.Checked ? 1 : 0));
        }

        private void checkBox11_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("11S" + (checkBox11.Checked ? 1 : 0));
        }

        private void checkBox12_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("12S" + (checkBox12.Checked ? 1 : 0));
        }

        private void checkBox13_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("13S" + (checkBox13.Checked ? 1 : 0));
        }

        private void checkBox14_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("14S" + (checkBox14.Checked ? 1 : 0));
        }

        private void checkBox20_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("20S" + (checkBox20.Checked ? 1 : 0));
        }

        private void checkBox21_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("21S" + (checkBox21.Checked ? 1 : 0));
        }

        private void checkBox22_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("22S" + (checkBox22.Checked ? 1 : 0));
        }

        private void checkBox23_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("23S" + (checkBox23.Checked ? 1 : 0));
        }

        private void checkBox24_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("24S" + (checkBox24.Checked ? 1 : 0));
        }

        private void checkBox30_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("30S" + (checkBox30.Checked ? 1 : 0));
        }

        private void checkBox31_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("31S" + (checkBox31.Checked ? 1 : 0));
        }

        private void checkBox32_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("32S" + (checkBox32.Checked ? 1 : 0));
        }

        private void checkBox33_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("33S" + (checkBox33.Checked ? 1 : 0));
        }

        private void checkBox34_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("34S" + (checkBox34.Checked ? 1 : 0));
        }

        private void checkBox40_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("40S" + (checkBox40.Checked ? 1 : 0));
        }

        private void checkBox41_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("41S" + (checkBox41.Checked ? 1 : 0));
        }

        private void checkBox42_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("42S" + (checkBox42.Checked ? 1 : 0));
        }

        private void checkBox43_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("43S" + (checkBox43.Checked ? 1 : 0));
        }

        private void checkBox44_CheckedChanged(object sender, EventArgs e)
        {
            serialPort1.Write("44S" + (checkBox44.Checked ? 1 : 0));
        }

        private void MenuTop_MouseMove(object sender, MouseEventArgs e)
        {
            if (SttMouse) this.SetDesktopLocation(MousePosition.X - movX, MousePosition.Y - movY);
        }
    }
}
