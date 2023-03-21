using System.Net;
using System.Net.Sockets;

namespace cliente
{
    public partial class Form1 : Form
    {
        Socket serv;
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string reg = "2/" + textBox4.Text + "/" + textBox5.Text;
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(reg);

            byte[] res = new byte[150];
            serv.Receive(res);
            reg = System.Text.Encoding.ASCII.GetString(res).Split('\0')[0];
            if (reg == "SI")
            {
                MessageBox.Show("Inicio completado");
            }
            else
            {
                MessageBox.Show("No ta bien");
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            string cod = "0/";
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(cod);
            serv.Send(msg);
            serv.Shutdown(SocketShutdown.Both);
            serv.Close();

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            IPAddress ip = IPAddress.Parse("192.168.56.102");
            IPEndPoint port = new IPEndPoint(ip, 9080);
            serv = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                serv.Connect(port);
                MessageBox.Show("Bienvenido");
            }
            catch (SocketException)
            {
                MessageBox.Show("Error :(");
                Close();
                return;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string reg = "1/" + textBox1.Text + "/" + textBox2.Text + "/" + textBox3.Text;
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(reg);
            serv.Send(msg);
            byte[] res = new byte[150];
            serv.Receive(res);
            reg = System.Text.Encoding.ASCII.GetString(res).Split('\0')[0];
            if (reg == "SI")
            {
                MessageBox.Show("Registro completado");
            }
            else
            {
                MessageBox.Show("No ta bien");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            string reg = "3/";
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(reg);
            serv.Send(msg);
            byte[] res = new byte[150];
            serv.Receive(res);
            reg = System.Text.Encoding.ASCII.GetString(res).Split('\0')[0];
            MessageBox.Show("El jugador con más puntos es; {0}", reg);
        }
    }
}