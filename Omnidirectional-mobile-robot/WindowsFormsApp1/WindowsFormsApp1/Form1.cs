using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            notifyIcon1.ShowBalloonTip(10, "123", "123", ToolTipIcon.Info);
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
        }

        bool isClosing = false;
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            if(!isClosing) 
                e.Cancel = true;
        }
        private void eXITToolStripMenuItem_Click(object sender, EventArgs e)
        {
            isClosing = true;
            Application.Exit();
        }
    }
}
