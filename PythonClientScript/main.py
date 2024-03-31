import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56812  # The port used by the server
EXIT = 'EXIT'


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_sock:
        server_sock.connect((HOST, PORT))  # connect to the server

        while message != EXIT:
            # send message to the server
            message = input('Enter message: ')
            server_sock.sendall(message.encode())

            # get response from the serv er
            response = server_sock.recv(1024)
            print(response.decode())
            

if __name__ == '__main__':
    main()
