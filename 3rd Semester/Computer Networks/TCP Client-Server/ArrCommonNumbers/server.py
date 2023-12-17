import socket
import struct

def tcp_send_int(sock, x):
    print("Sending ", x)
    sock.send(struct.pack("!I", x))

def tcp_recv_int(sock):
    x = struct.unpack("!I", sock.recv(4))[0]
    print("Received ", x)
    return x

def tcp_send_string(sock, str):
    print("Sending: ", str)
    sock.send(str.encode("ascii"))
    pass

def tcp_recv_string(sock):
    str = sock.recv(1024).decode("ascii")
    print("received ", str)
    return str

def tcp_server_init(ip_address, port):
    return socket.create_server((ip_address, port), family = socket.AF_INET, backlog = 10, reuse_port = True)

def common(l1, l2):
    l1 = set(l1)
    l2 = set(l2)

    l = []
    for a in l1:
        if a in l2:
            l.append(a)

    return l

def server_program():
    
    host = socket.gethostname()

    port = 1234

    server_socket = tcp_server_init(host, port)

    server_socket.listen(7)

    client_socket, address  = server_socket.accept()

    print("Connected client: " + str(address))

    while True:
        arr_len_1 = tcp_recv_int(client_socket)
        l1 = []
        print("arr_len_1 ", arr_len_1)

        for _ in range(arr_len_1):
            x = tcp_recv_int(client_socket)
            l1.append(x)

        arr_len_2 = tcp_recv_int(client_socket)
        l2 = []
        print("arr_len_2 ", arr_len_2)

        for _ in range(arr_len_2):
            x = tcp_recv_int(client_socket)
            l2.append(x)

        if arr_len_1 == 0 and arr_len_2 == 0:
            break

        cmn = common(l1, l2)

        tcp_send_int(client_socket, len(cmn))

        for x in cmn:
            tcp_send_int(client_socket, x)

    client_socket.close()
    print("disconnected socket " + str(address))


server_program()