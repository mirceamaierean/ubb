import socket

import struct

def tcp_send_int(sock, x):
    sock.send(struct.pack("!I", x))

def tcp_recv_int(sock):
    x = struct.unpack("!I", sock.recv(4))[0]
    print("received ", x)
    return x

def tcp_send_string(sock, string):
    sock.send(string.encode('ascii'))

def tcp_recv_string(sock):
    str = sock.recv(1024).decode('ascii')
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

    while True:
        arr_len = int(input("Length of array: "))

        tcp_send_int(client_socket, arr_len)

        if arr_len == 0:
            break

        for _ in range(arr_len):
            x = int(input())
            tcp_send_int(client_socket, x)
        
        arr_sum = tcp_recv_int(client_socket)
        print("Sum: ", arr_sum)

    client_socket.close()
    print("disc")

client_program()