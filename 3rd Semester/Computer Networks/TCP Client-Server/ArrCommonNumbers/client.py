import socket

import struct

def tcp_send_int(sock, x):
    sock.send(struct.pack("!i", x));

def tcp_recv_int(sock):
    x = struct.unpack("!i", sock.recv(4))[0]
    print("received ", x)
    return x

def tcp_send_string(sock, str):
    sock.send(str.endcode("ascii"))

def tcp_recv_string(sock):
    str = sock.recv(1024).decode("ascii")
    print("received ", str)
    return str

def tcp_client_init(ip_address, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip_address, port))
    return s

def client_program():
    host = socket.gethostname()
    port = 1234

    client_socket = tcp_client_init(host, port)
    print("connected")

    while True:
        arr_len_1 = int(input("Length of the first array: "))

        tcp_send_int(client_socket, arr_len_1)

        for _ in range(arr_len_1):
            x = int(input())
            tcp_send_int(client_socket, x)
        
        arr_len_2 = int(input("Length of the second array: "))

        if arr_len_1 == 0 and arr_len_2 == 0:
            break;

        tcp_send_int(client_socket, arr_len_2)

        for _ in range(arr_len_2):
            x = int(input())
            tcp_send_int(client_socket, x)

        arr_len_common = tcp_recv_int(client_socket)

        l = []

        for _ in range(arr_len_common):
            x = tcp_recv_int(client_socket)
            l.append(x)

        print("Length of common array is ", arr_len_common)
        print(l)
        

client_program()