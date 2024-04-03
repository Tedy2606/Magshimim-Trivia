import socket
from time import sleep

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56812  # The port used by the server
EXIT = 'EXIT'


def main():
    # connect to server
    tries_left = 5  # tries until terminating program
    print('Connecting to server')

    while tries_left:  # when connection doesn't work try again
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_sock:
                server_sock.connect((HOST, PORT))  # connect to the server
                print('Connection has been made with the server')

                message = ''
                while true:
                    # send message to the server
                    message = input('Enter message: ')
                    server_sock.sendall(message.encode())
                    
                    if message == EXIT:
                        break
                    
                    # get response from the server
                    response = server_sock.recv(1024)
                    print(response.decode())
            return  # end program
        except socket.error:
            print('Connection with server has Failed\nTrying again ' + str(tries_left), end='')
            tries_left -= 1

            # cool waiting animation
            for i in range(3):
                sleep(1)
                print('.', end='')
            print()  # go down a line

    print('Terminating program')


if __name__ == '__main__':
    main()
