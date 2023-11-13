import socket
import struct

def tcp_send_int(sock, x):
    print('Sending:', x)
    sock.send(struct.pack('!I', x))

def tcp_recv_int(sock):
    x = struct.unpack("!I", sock.recv(4))[0]
    print("received ", x)
    return x

def tcp_send_string(sock, str):
    print("Sending: ", str)
    sock.send(str.encode("ascii"))

def tcp_recv_string(sock):
    str = sock.recv(1024).decode('ascii')
    print("received ", str)
    return str

def tcp_server_init(ip_address, port):
    return socket.create_server((ip_address, port), family = socket.AF_INET, backlog = 10, reuse_port = True)

def server_program():
    # server and client are running on the same PC
    host = socket.gethostname()
    port = 1234
    
    server_socket = tcp_server_init(host, port)

    # number of maximum clients the server can listen simultaneously
    server_socket.listen(5)

    while True:
        client_socket, address = server_socket.accept()
        print("Connected client: " + str(address))

        array_length = tcp_recv_int(client_socket)

        print("arr len ", array_length)

        if array_length == 0:
            break

        array_sum = 0

        for _ in range(array_length):
            array_sum += tcp_recv_int(client_socket)

        tcp_send_int(client_socket, array_sum)

    client_socket.close()
    print("Disconnected clinet" + str(address))

server_program()
