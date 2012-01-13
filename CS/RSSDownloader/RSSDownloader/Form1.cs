using System;
using System.Configuration;
using System.IO;
using System.Net;
using System.Windows.Forms;
using System.Xml;
using ThunderAgentLib;

namespace RSSDownloader
{
    public partial class Form1 : Form
    {
        //RSS网址
        private readonly string _url;
        //保存路径
        private readonly string _savePath;

        public Form1()
        {
            InitializeComponent();

            AppSettingsReader appReader = new AppSettingsReader();
            _url = appReader.GetValue("URL", typeof(string)).ToString();
            _savePath = appReader.GetValue("SavePath", typeof(string)).ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void btnDownload_Click(object sender, EventArgs e)
        {
            HttpWebRequest request      = (HttpWebRequest)WebRequest.Create(_url);
            HttpWebResponse response    = null;
            Stream receiveStream        = null; 
            try
            {
#if DEBUG
                FileStream fs = new FileStream(@"./test.xml", FileMode.Open);
                receiveStream = fs;
#else
                request.MaximumAutomaticRedirections = 4;
                request.MaximumResponseHeadersLength = 4;
                request.Credentials = CredentialCache.DefaultCredentials;
                response = (HttpWebResponse)request.GetResponse();
                receiveStream = response.GetResponseStream();
#endif

                XmlDocument xml = new XmlDocument();
                XmlNodeList xmllist = null;
                xml.Load(receiveStream);
                xmllist = xml.SelectNodes("//channel/item");
                AgentClass ac = new AgentClass();
                foreach (XmlNode node in xmllist)
                {
                    string url = node.SelectSingleNode("link").InnerText;
                    string[] temp = url.Split('/');
                    string fileName = temp[temp.Length - 1].Replace("m4v", "mp4");
                    if (File.Exists(_savePath + fileName))
                        continue;
                    ac.AddTask(url, fileName, @"F:\ENGLISH\StudentNews\", string.Empty, string.Empty, 0, 0, 0);
                }
                ac.CommitTasks();
                
            }
            finally
            {
                if (response != null)
                    response.Close();
                if (receiveStream != null)
                    receiveStream.Close();
            }

        }

        private void btnRename_Click(object sender, EventArgs e)
        {
            try
            {
                string[] files = Directory.GetFiles(_savePath);
                foreach (string fileName in files)
                {
                    if (fileName.IndexOf("m4v") < 0)
                        continue;
                    File.Move(fileName, fileName.Replace("m4v", "mp4"));
                }
            }
            finally
            { 
            }
        }
    }
}
