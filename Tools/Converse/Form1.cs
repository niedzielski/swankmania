using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

/*
    Use image handling libraries.
    Call get pixel for width and height.
    Divide by 32.  Round approp.
    Output file.
*/

namespace Converse
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog o = new OpenFileDialog();
            o.ShowDialog();
            int p = o.FileName.IndexOf('.');
            char[] OutputFilename = new char[o.FileName.Length + 1];
            o.FileName.CopyTo(0, OutputFilename, 0, o.FileName.Length - 1);
            OutputFilename[o.FileName.Length-3] = 'h';
            OutputFilename[o.FileName.Length-2] = 'e';
            OutputFilename[o.FileName.Length-1] = 'x';
            string strOutputFilename = new string(OutputFilename, 0, OutputFilename.Length - 1);
            System.IO.TextWriter f = new System.IO.StreamWriter(strOutputFilename);
            System.Drawing.Bitmap bmp = new Bitmap(o.FileName);

            int r = 0;
            int c = 0;
            while (r < bmp.Height)
            {
                c = 0;
                while (c < bmp.Width)
                {
                    Color rgb = bmp.GetPixel(c, r);
/*
    First character (:) = Start of a record 
    Next two characters = Record length (in this example, 10h) 
    Next four characters = Load address (in this example, 0080h) 
    Next two characters = Record type
    Remaining characters = Actual data 
    Last two characters = Checksum (i.e., sum of all bytes + checksum = 00)
 */
                    int RecordLength    = 2;
                    int RecordType = 0;
                    float   oatR = ((float)rgb.R )/ 32,
                            oatG = ((float)rgb.G )/ 32,
                            oatB = ((float)rgb.B )/ 32;
                    int     intR = (int)oatR + ((oatR - (int)oatR) >= .5 ? 1 : 0),
                            intG = (int)oatG + ((oatG - (int)oatG) >= .5 ? 1 : 0),
                            intB = (int)oatB + ((oatB - (int)oatB) >= .5 ? 1 : 0);
                    intR = intR > 7 ? 7 : intR;
                    intG = intG > 7 ? 7 : intG;
                    intB = intB > 7 ? 7 : intB;

                    int Data = ( (intR << 6) | ( (intG & 7) << 3) | (intB & 7));
                    int LoadAddress = c + bmp.Width * r;
                    int Checksum = (256 - (RecordLength + (LoadAddress >> 8) + (LoadAddress & 255) + RecordType + (Data >> 8) + Data & 255)) & 0xFF;
                    string  strRecordLength = String.Format("{0:X2}", RecordLength),
                            strLoadAddress  = String.Format("{0:X4}", LoadAddress),
                            strRecordType = String.Format("{0:X2}", RecordType),
                            strData = String.Format("{0:X4}", Data),
                            strChecksum = String.Format("{0:X2}", Checksum);
                    f.Write(":" + strRecordLength + strLoadAddress + strRecordType + strData + strChecksum + "\n");
                    ++c;
                }
                ++r;
            }
            f.Write(":00000001FF");
            f.Close();
        }
    }
}