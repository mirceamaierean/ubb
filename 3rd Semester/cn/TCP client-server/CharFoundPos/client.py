# The client sends to the server a string and a character.
# The server returns to the client a list of all positions in the string where specified character is found.

import socket
import struct

def tcp_send_int(sock, x):
    sock.send(struct.pack("!i", x))

def tcp_recv_int(sock):
    x = struct.unpack("!i", sock.recv(4))[0]
    return x

def tcp_send_string(sock, str):
    sock.send(str.encode("ascii"))

def tcp_received_string(sock):
    str = sock.recv(1024).decode("ascii")
    return str

def tcp_recv_char(sock):
    char = sock.recv(8).decode("ascii")
    return char

def tcp_client_init(ip_address, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip_address, port))
    return s

def client_program():
    host = socket.gethostname()
    port = 1234

    client_socket = tcp_client_init(host, port)

    print("Connected")

    while True:
        str = input("String: ")
        tcp_send_string(client_socket, str)

        if str == "":
            break

        char = input("Character: ")

        tcp_send_string(client_socket, char)

        arr_len = tcp_recv_int(client_socket)
        l = []
        for _ in range(arr_len):
            x = tcp_recv_int(client_socket)
            l.append(x)
        
        print(l)

    client_socket.close()

client_program()
            