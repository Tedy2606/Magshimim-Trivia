import socket
from time import sleep
import json
import struct
HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56812  # The port used by the server
EXIT = 'EXIT'
HEADERS = 5

LOGIN_INPUT = '1'
SIGNUP_INPUT = '2'

LOGIN_REQ = 101
SIGNUP_REQ = 102


def make_login_and_signup_packet(data: dict, code: bin):
    """
        makes the login and signup packet to send
        to the server
        Parameters
        ----------
        :param code: the code of the packet (weather it is a signup or a login packet
        :param data: the data to be sent to server
        ------------
        :return the packet to send to server
        """

    # serialize the json and encode it then get its len
    # get the len after the encoding for the format to also be included
    user_encode_data = json.dumps(data).encode('utf-8')
    data_len = len(user_encode_data)
    # Pack the length into 4 bytes
    data_len_bytes = struct.pack('>I', data_len)  # Pack the length into 4 bytes
    packet_encoded = code + data_len_bytes + user_encode_data
    return packet_encoded


def get_input(message: str):
    """
            asks the user for input and waits until he chooses one of the
            given ones
            Parameters
            ----------
            :param message the message that asks the user for input
            ------------
            :return the user input
            """
    while True:
        user_input = input(message)
        if user_input in {LOGIN_INPUT, SIGNUP_INPUT, EXIT}:
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
                        return  # exit program

                    name = input("please enter username: ")
                    password = input("please enter password: ")

                    if message == LOGIN_INPUT:
                        packet = make_login_and_signup_packet({'username': name, 'password': password}, (LOGIN_REQ).to_bytes())
                    elif message == SIGNUP_INPUT:
                        packet = make_login_and_signup_packet({'username': name, 'password': password, 'mail': input("enter mail please: ")}, (SIGNUP_REQ).to_bytes())

                    server_sock.sendall(packet)

                    # get response from the server
                    response = server_sock.recv(1024)
                    print(response[HEADERS:].decode())
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
