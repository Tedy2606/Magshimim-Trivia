import socket
from time import sleep
import json
HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 56812  # The port used by the server
EXIT = 'EXIT'


def make_sign_up_packet(data):
    # makes the sign-up packet using the mail, name, password
    data_len = len(data['username']) + len(data['password']) + len(data['mail'])
    str_data_len = str(data_len)
    data_len_encode = str_data_len.encode()
    user_encode_data = json.dumps(data).encode('utf-8')
    packet_encoded = b'3' + data_len_encode + user_encode_data
    return packet_encoded


def make_login_packet(data):
    # makes the login packet using the name, password
    data_len = len(data['username']) + len(data['password'])
    str_data_len = str(data_len)
    data_len_encode = str_data_len.encode()
    user_encode_data = json.dumps(data).encode('utf-8')
    packet_encoded = b'2' + data_len_encode + user_encode_data
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
                        break

                    name = input("please enter username: ")
                    password = input("please enter password: ")

                    if message == "1":
                        packet = make_login_packet({'username': name, 'password': password})
                        break
                    if message == "2":
                        packet = make_sign_up_packet({'username': name, 'password': password, 'mail': input("enter mail please: ")})
                        break

                    server_sock.sendall(packet)


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
