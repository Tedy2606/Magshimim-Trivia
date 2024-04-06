import socket
from time import sleep
import json
import struct
HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56812  # The port used by the server
EXIT = 'EXIT'


def make_login_and_signup_packet(data, code):
    # makes the login packet using the name, password

    # serialize the json and encode it then get its len
    # get the len after the encoding for the format to also be included
    user_encode_data = json.dumps(data).encode('utf-8')
    data_len = len(user_encode_data)
    # Pack the length into 4 bytes
    data_len_bytes = struct.pack('>I', data_len)  # Pack the length into 4 bytes
    packet_encoded = code + data_len_bytes + user_encode_data
    return packet_encoded


def get_input(message):
    # get the user input if he wants to log in or sign up
    while True:
        user_input = input(message)
        if user_input in {'1', '2', EXIT}:
            return user_input


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
                while True:
                    # send message to the server
                    message = get_input('please enter action:\n 1 log in\n 2 sign up\n EXIT exit the program\n')
                    if message == EXIT:
                        return

                    name = input("please enter username: ")
                    password = input("please enter password: ")

                    if message == "1":
                        packet = make_login_and_signup_packet({'username': name, 'password': password}, b'2')
                        break
                    if message == "2":
                        packet = make_login_and_signup_packet({'username': name, 'password': password, 'mail': input("enter mail please: ")}, b'3')
                        break

                server_sock.sendall(packet)

                # get response from the server
                response = server_sock.recv(1024)
                print(response[5:].decode())
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
