﻿// Latite Client
// by Imrglop

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace Latite
{
    public partial class LatiteForm : Form
    {
        [DllImport("LatiteCore.dll")]
        static extern void consoleMain();
        [DllImport("LatiteCore.dll")]
        static extern ulong attach();
        // extern "C" LATITE_API bool connectedToMinecraft(int type = 2);
        [DllImport("LatiteCore.dll")]
        static extern bool connectedToMinecraft(int type = 2);
        [DllImport("LatiteCore.dll")]
        static extern void detach();
        [DllImport("LatiteCore.dll")]
        static extern void loop();
        /*
         * 
extern "C" LATITE_API void mod_zoom_setBind(char bind);
extern "C" LATITE_API void mod_zoom_setAmount(float amount);
         */
        [DllImport("LatiteCore.dll")]
        static extern void mod_zoom_setBind(char bind);
        [DllImport("LatiteCore.dll")]
        static extern void mod_zoom_setAmount(float amount);
        public LatiteForm()
        {
            InitializeComponent();
        }

        readonly string[] Commands = { "help", "info", "print <text>", "clear", "connect", "disconnect" };
        readonly string Info = "Latite Client\r\n\r\nLicense: GPLv3\r\n\r\nSource: github.com/Imrglop/Latite\r\n\r\nMade by Imrglop";
        private bool IsConsole = false;

        public void Cout(string OutputString)
        {
            consoleOutput.Text += OutputString;
        }
        public void Coutln(string OutputString)
        {
            consoleOutput.Text += (OutputString + "\r\n");
        }

        private void ConnectToMc()
        {
            try
            {
                if (!connectedToMinecraft())
                {
                    if (!IsConsole && settingsUseConsole.Checked)
                    {
                        consoleMain();
                        IsConsole = true;
                    }
                    var Status = attach();
                    if (Status == 0)
                    {
                        connectButton.Visible = false;
                        connectedToMinecraft(1); // true
                        connectedLabel.Visible = true;
                        // have to put 1 cuz C#
                        moduleWorker.RunWorkerAsync();
                        disconnectButton.Visible = true;
                        Coutln("Connected to Minecraft!");
                        MessageBox.Show("Connected to Minecraft!");
                    }
                    else
                    {
                        Coutln("Couldn't connect to Minecraft! Error code: " + Status.ToString());
                        var Result = MessageBox.Show("Could not connect to Minecraft! Error Code: " + Status.ToString(), "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Hand);
                        if (Result == DialogResult.Retry)
                        {
                            ConnectToMc();
                        }
                    }
                }
            } catch (DllNotFoundException)
            {
                var Result = MessageBox.Show("Could not connect! You may be missing LatiteCore.dll", "Error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Hand);
                Coutln("DllNotFoundException occured while attempting to import LatiteCore.dll");
                if (Result == DialogResult.Retry)
                {
                    ConnectToMc();
                }
            }
        }

        private void DisconnectFromMc()
        {
            if (connectedToMinecraft())
            {
                if (moduleWorker.IsBusy)
                {
                    moduleWorker.CancelAsync();
                }
                disconnectButton.Visible = false;
                connectButton.Visible = true;
                connectedToMinecraft(0); // false
                connectedLabel.Visible = false;
                detach();
            }
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            ConnectToMc();
        }

        private void onKeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\r')
            {
                DispatchCommand(consoleInput.Text);
            }
        }

        private char GetBind(string Str)
        {
            return Str.ToUpper()[0];
        }

        private void DispatchCommand(string Command)
        {
            Coutln("> " + Command);
            string[] Args = Command.Split(' ');
            if (Args.Length == 0) return;
            string Label = Args[0].ToLower();
            Args = Args.Skip(1).ToArray();
            switch(Label)
            {
                case "help":
                    Cout("Commands: ");
                    Coutln(string.Join(", ", Commands));
                    break;
                case "print":
                    Coutln(string.Join(" ", Args));
                    break;
                case "clear":
                    consoleOutput.Clear();
                    break;
                case "connect":
                    ConnectToMc();
                    break;
                case "info":
                    Coutln(Info);
                    break;
                case "disconnect":
                    DisconnectFromMc();
                    Coutln("Disconnected!");
                    break;
                default:
                    Coutln("Error: unknown command \"" + Label + "\"");
                    break;
            }
        }

        private void cinGo_Click(object sender, EventArgs e)
        {
            DispatchCommand(consoleInput.Text);
        }

        private void DRPButton_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://discord.gg/DfYUSJspcn");
        }

        private void optionsButton_Click(object sender, EventArgs e)
        {
            modsControl.SelectedTab = optionsTabControl;
        }

        private void modsButton_Click(object sender, EventArgs e)
        {
            modsControl.SelectedTab = modsTabPage;
        }

        private void consoleButton_Click(object sender, EventArgs e)
        {
            modsControl.SelectedTab = consoleTab;
        }

        private void zaSlider_Scroll(object sender, EventArgs e)
        {
            var FOVAmount = (zaSlider.Value + 2) * 5;
            zaSliderLabel.Text = $"Amount ({FOVAmount})";
            mod_zoom_setAmount(FOVAmount);
            Coutln("try set amt to " + FOVAmount);
        }

        private void moduleWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                loop();
                if (moduleWorker.CancellationPending) break;
                Thread.Sleep(50);
            }
        }

        private void OnClosing(object sender, FormClosingEventArgs e)
        {
            DisconnectFromMc();
        }

        private void disconnectButton_Click(object sender, EventArgs e)
        {
            DisconnectFromMc();
        }

        private void zoomBindBox_TextChanged(object sender, EventArgs e)
        {
            string SetStr = zoomBindBox.Text.ToUpper();
            if (SetStr.Length > 0)
                mod_zoom_setBind(SetStr[0]);
        }

        private void LatiteForm_Load(object sender, EventArgs e)
        {
            Overlay OverlayForm = new Overlay();
            OverlayForm.Show();
        }
    }
}