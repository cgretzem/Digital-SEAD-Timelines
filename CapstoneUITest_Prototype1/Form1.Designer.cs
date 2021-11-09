namespace CapstoneUITest
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
            this.fireType = new System.Windows.Forms.ComboBox();
            this.totIn = new System.Windows.Forms.TextBox();
            this.TOTL = new System.Windows.Forms.Label();
            this.TOFL = new System.Windows.Forms.Label();
            this.tofIn = new System.Windows.Forms.TextBox();
            this.markingTypeL = new System.Windows.Forms.Label();
            this.markingType = new System.Windows.Forms.ComboBox();
            this.MarkingTOFL = new System.Windows.Forms.Label();
            this.markingTOF = new System.Windows.Forms.TextBox();
            this.FireFreqL = new System.Windows.Forms.Label();
            this.FireFreqIn = new System.Windows.Forms.TextBox();
            this.FiringRangesL = new System.Windows.Forms.Label();
            this.FiringRangesIn = new System.Windows.Forms.TextBox();
            this.addFiringRanges = new System.Windows.Forms.Button();
            this.FiringRangesList = new System.Windows.Forms.ListBox();
            this.CalculateButton = new System.Windows.Forms.Button();
            this.TimelineList = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // fireType
            // 
            this.fireType.AllowDrop = true;
            this.fireType.DropDownWidth = 178;
            this.fireType.FormattingEnabled = true;
            this.fireType.Location = new System.Drawing.Point(97, 12);
            this.fireType.MaxDropDownItems = 3;
            this.fireType.Name = "fireType";
            this.fireType.Size = new System.Drawing.Size(199, 21);
            this.fireType.TabIndex = 0;
            this.fireType.Text = "Select Fire Type";
            this.fireType.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // totIn
            // 
            this.totIn.Location = new System.Drawing.Point(97, 61);
            this.totIn.Name = "totIn";
            this.totIn.Size = new System.Drawing.Size(199, 20);
            this.totIn.TabIndex = 1;
            // 
            // TOTL
            // 
            this.TOTL.AutoSize = true;
            this.TOTL.Location = new System.Drawing.Point(13, 64);
            this.TOTL.Name = "TOTL";
            this.TOTL.Size = new System.Drawing.Size(35, 13);
            this.TOTL.TabIndex = 2;
            this.TOTL.Text = "TOT: ";
            // 
            // TOFL
            // 
            this.TOFL.AutoSize = true;
            this.TOFL.Location = new System.Drawing.Point(13, 91);
            this.TOFL.Name = "TOFL";
            this.TOFL.Size = new System.Drawing.Size(34, 13);
            this.TOFL.TabIndex = 4;
            this.TOFL.Text = "TOF: ";
            // 
            // tofIn
            // 
            this.tofIn.Location = new System.Drawing.Point(97, 88);
            this.tofIn.Name = "tofIn";
            this.tofIn.Size = new System.Drawing.Size(199, 20);
            this.tofIn.TabIndex = 3;
            // 
            // markingTypeL
            // 
            this.markingTypeL.AutoSize = true;
            this.markingTypeL.Location = new System.Drawing.Point(13, 116);
            this.markingTypeL.Name = "markingTypeL";
            this.markingTypeL.Size = new System.Drawing.Size(78, 13);
            this.markingTypeL.TabIndex = 6;
            this.markingTypeL.Text = "Marking Type: ";
            // 
            // markingType
            // 
            this.markingType.FormattingEnabled = true;
            this.markingType.Location = new System.Drawing.Point(98, 114);
            this.markingType.Name = "markingType";
            this.markingType.Size = new System.Drawing.Size(198, 21);
            this.markingType.TabIndex = 7;
            // 
            // MarkingTOFL
            // 
            this.MarkingTOFL.AutoSize = true;
            this.MarkingTOFL.Location = new System.Drawing.Point(13, 144);
            this.MarkingTOFL.Name = "MarkingTOFL";
            this.MarkingTOFL.Size = new System.Drawing.Size(75, 13);
            this.MarkingTOFL.TabIndex = 9;
            this.MarkingTOFL.Text = "Marking TOF: ";
            // 
            // markingTOF
            // 
            this.markingTOF.Location = new System.Drawing.Point(97, 141);
            this.markingTOF.Name = "markingTOF";
            this.markingTOF.Size = new System.Drawing.Size(199, 20);
            this.markingTOF.TabIndex = 8;
            // 
            // FireFreqL
            // 
            this.FireFreqL.AutoSize = true;
            this.FireFreqL.Location = new System.Drawing.Point(13, 117);
            this.FireFreqL.Name = "FireFreqL";
            this.FireFreqL.Size = new System.Drawing.Size(51, 13);
            this.FireFreqL.TabIndex = 11;
            this.FireFreqL.Text = "Fire Freq:";
            // 
            // FireFreqIn
            // 
            this.FireFreqIn.Location = new System.Drawing.Point(97, 114);
            this.FireFreqIn.Name = "FireFreqIn";
            this.FireFreqIn.Size = new System.Drawing.Size(199, 20);
            this.FireFreqIn.TabIndex = 10;
            this.FireFreqIn.TextChanged += new System.EventHandler(this.FireFreqIn_TextChanged);
            // 
            // FiringRangesL
            // 
            this.FiringRangesL.AutoSize = true;
            this.FiringRangesL.Location = new System.Drawing.Point(13, 143);
            this.FiringRangesL.Name = "FiringRangesL";
            this.FiringRangesL.Size = new System.Drawing.Size(75, 13);
            this.FiringRangesL.TabIndex = 13;
            this.FiringRangesL.Text = "Firing Ranges:";
            // 
            // FiringRangesIn
            // 
            this.FiringRangesIn.Location = new System.Drawing.Point(97, 140);
            this.FiringRangesIn.Name = "FiringRangesIn";
            this.FiringRangesIn.Size = new System.Drawing.Size(118, 20);
            this.FiringRangesIn.TabIndex = 12;
            // 
            // addFiringRanges
            // 
            this.addFiringRanges.Location = new System.Drawing.Point(221, 139);
            this.addFiringRanges.Name = "addFiringRanges";
            this.addFiringRanges.Size = new System.Drawing.Size(75, 23);
            this.addFiringRanges.TabIndex = 14;
            this.addFiringRanges.Text = "ADD";
            this.addFiringRanges.UseVisualStyleBackColor = true;
            this.addFiringRanges.Click += new System.EventHandler(this.button1_Click);
            // 
            // FiringRangesList
            // 
            this.FiringRangesList.FormattingEnabled = true;
            this.FiringRangesList.Location = new System.Drawing.Point(302, 61);
            this.FiringRangesList.Name = "FiringRangesList";
            this.FiringRangesList.Size = new System.Drawing.Size(147, 160);
            this.FiringRangesList.TabIndex = 16;
            // 
            // CalculateButton
            // 
            this.CalculateButton.Location = new System.Drawing.Point(97, 168);
            this.CalculateButton.Name = "CalculateButton";
            this.CalculateButton.Size = new System.Drawing.Size(199, 53);
            this.CalculateButton.TabIndex = 17;
            this.CalculateButton.Text = "Calculate Timeline";
            this.CalculateButton.UseVisualStyleBackColor = true;
            this.CalculateButton.Click += new System.EventHandler(this.CalculateButton_Click);
            // 
            // TimelineList
            // 
            this.TimelineList.FormattingEnabled = true;
            this.TimelineList.Location = new System.Drawing.Point(16, 227);
            this.TimelineList.Name = "TimelineList";
            this.TimelineList.Size = new System.Drawing.Size(433, 238);
            this.TimelineList.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(461, 473);
            this.Controls.Add(this.TimelineList);
            this.Controls.Add(this.CalculateButton);
            this.Controls.Add(this.FiringRangesList);
            this.Controls.Add(this.addFiringRanges);
            this.Controls.Add(this.FiringRangesL);
            this.Controls.Add(this.FiringRangesIn);
            this.Controls.Add(this.FireFreqL);
            this.Controls.Add(this.FireFreqIn);
            this.Controls.Add(this.MarkingTOFL);
            this.Controls.Add(this.markingTOF);
            this.Controls.Add(this.markingType);
            this.Controls.Add(this.markingTypeL);
            this.Controls.Add(this.TOFL);
            this.Controls.Add(this.tofIn);
            this.Controls.Add(this.TOTL);
            this.Controls.Add(this.totIn);
            this.Controls.Add(this.fireType);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox fireType;
        private System.Windows.Forms.TextBox totIn;
        private System.Windows.Forms.Label TOTL;
        private System.Windows.Forms.Label TOFL;
        private System.Windows.Forms.TextBox tofIn;
        private System.Windows.Forms.Label markingTypeL;
        private System.Windows.Forms.ComboBox markingType;
        private System.Windows.Forms.Label MarkingTOFL;
        private System.Windows.Forms.TextBox markingTOF;
        private System.Windows.Forms.Label FireFreqL;
        private System.Windows.Forms.TextBox FireFreqIn;
        private System.Windows.Forms.Label FiringRangesL;
        private System.Windows.Forms.TextBox FiringRangesIn;
        private System.Windows.Forms.Button addFiringRanges;
        private System.Windows.Forms.ListBox FiringRangesList;
        private System.Windows.Forms.Button CalculateButton;
        private System.Windows.Forms.ListBox TimelineList;
    }
}

