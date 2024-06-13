using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class Networker
    {

        public Networker() { }
        public JObject sendAndRecive(JObject packet, NetworkStream stream, byte code)
        {
            string jsonString = packet.ToString();
            
            byte[] data_len_bytes = BitConverter.GetBytes(jsonString.Length);
            //reverse to reverse the endian orientation 
            data_len_bytes = data_len_bytes.Reverse().ToArray();

            var messageBytes = Encoding.UTF8.GetBytes(jsonString);

            byte[] message_and_len = data_len_bytes.Concat(messageBytes).ToArray();

            var full_msg_byte = Enumerable.Prepend(message_and_len, code).ToArray();

            stream.Write(full_msg_byte, 0, full_msg_byte.Length);

            // Receive response from the server
            byte[] len_buffer = new byte[5];
            int len_bytesRead = stream.Read(len_buffer, 0, len_buffer.Length);

            int data_len = (len_buffer[1] << 24) | (len_buffer[2] << 16) | (len_buffer[3] << 8) | len_buffer[4];

            byte[] buffer = new byte[data_len];

            //read from stream 
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            //get the string 
            string utf8String = Encoding.UTF8.GetString(buffer, 0, bytesRead);
            //turn string into json 
            JObject jsonObject = JObject.Parse(utf8String);

            return jsonObject;
        }
    }
}
