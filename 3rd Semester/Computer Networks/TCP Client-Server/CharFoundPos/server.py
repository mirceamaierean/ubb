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

def tcp_recv_string(sock):
    str = sock.recv(1024).decode("ascii")
    return str

def tcp_recv_char(sock):
    char = sock.recv(8).decode("ascii")
    return char

def tcp_server_init(ip_address, port):
    return socket.create_server((ip_address, port), family = socket.AF_INET, backlog = 10, reuse_port = True)

def server_program():
    host = socket.gethostname()

    port = 1234

    server_socket = tcp_server_init(host, port)

    server_socket.listen(7)

    client_socket, address = server_socket.accept()

    print("Connected client: " + str(address))

    while True:
        string = tcp_recv_string(client_socket)

        if string == "":
            break

        char = tcp_recv_char(client_socket)

        l = []

        for i in range(len(string)):
            if string[i] == char:
                l.append(i)

        tcp_send_int(client_socket, len(l))
        
        for i in l:
            tcp_send_int(client_socket, i)

server_program()