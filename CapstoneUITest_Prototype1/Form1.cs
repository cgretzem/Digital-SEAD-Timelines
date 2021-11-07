using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CapstoneUITest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            fireType.Items.Add("Continuous");
            fireType.Items.Add("Interrupted");
            fireType.Items.Add("Non-standard");

            markingType.Items.Add("Negative");
            markingType.Items.Add("Illum");
            markingType.Items.Add("WP");

            FiringRangesList.Items.Add("Firing Ranges:");

            totIn.Hide();
            tofIn.Hide();
            TOTL.Hide();
            TOFL.Hide();
            markingType.Hide();
            markingTOF.Hide();
            MarkingTOFL.Hide();
            markingTypeL.Hide();
            FireFreqIn.Hide();
            FireFreqL.Hide();
            FiringRangesIn.Hide();
            FiringRangesL.Hide();
            FiringRangesList.Hide();
            addFiringRanges.Hide();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (fireType.SelectedItem.ToString().Equals("Continuous"))
            {
                TimelineList.Items.Clear();
                totIn.Show();
                TOTL.Show();
                tofIn.Show();
                TOFL.Show();
                markingType.Show();
                markingTypeL.Show();
                markingTOF.Show();
                MarkingTOFL.Show();
                FireFreqIn.Hide();
                FireFreqL.Hide();
                FiringRangesIn.Hide();
                FiringRangesL.Hide();
                FiringRangesList.Hide();
                addFiringRanges.Hide();
            }
            else if (fireType.SelectedItem.ToString().Equals("Interrupted"))
            {
                TimelineList.Items.Clear();
                totIn.Show();
                TOTL.Show();
                tofIn.Show();
                TOFL.Show();
                markingType.Show();
                markingTypeL.Show();
                markingTOF.Show();
                MarkingTOFL.Show();
                FireFreqIn.Hide();
                FireFreqL.Hide();
                FiringRangesIn.Hide();
                FiringRangesL.Hide();
                FiringRangesList.Hide();
                addFiringRanges.Hide();
            }
            else if (fireType.SelectedItem.ToString().Equals("Non-standard")) 
            {
                TimelineList.Items.Clear();
                totIn.Show();
                TOTL.Show();
                tofIn.Show();
                TOFL.Show();
                markingType.Hide();
                markingTypeL.Hide();
                markingTOF.Hide();
                MarkingTOFL.Hide();
                FireFreqIn.Show();
                FireFreqL.Show();
                FiringRangesIn.Show();
                FiringRangesL.Show();
                FiringRangesList.Show();
                addFiringRanges.Show();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            FiringRangesList.Items.Add("- " + FiringRangesIn.Text);
        }

        private void CalculateButton_Click(object sender, EventArgs e)
        {
            TimelineList.Items.Clear();
            TimelineList.Items.Add("Shell 1: x min x sec");
            TimelineList.Items.Add("Shell 2: x min x sec");
            TimelineList.Items.Add("Shell 3: x min x sec");
            TimelineList.Items.Add("Shell 4: x min x sec");
            TimelineList.Items.Add("Shell 5: x min x sec");
            TimelineList.Items.Add("Shell 6: x min x sec");
            TimelineList.Items.Add("Shell 7: x min x sec");
        }
    }
}
