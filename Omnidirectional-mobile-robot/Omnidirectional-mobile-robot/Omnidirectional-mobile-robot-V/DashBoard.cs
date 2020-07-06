using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Omnidirectional_mobile_robot_V2
{
    public partial class Control : Form
    {
        public Control()
        {
            InitializeComponent();
        }
        private void Control_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }
    }
}
