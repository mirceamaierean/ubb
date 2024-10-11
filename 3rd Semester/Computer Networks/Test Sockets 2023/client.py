import socket
import struct
import threading
import time

def tcp_send_int(sock, x):
    print("Sending: {data}".format(data=x))
    sock.send(struct.pack("!i", x))


def tcp_recv_int(sock):
    x = struct.unpack("!i", sock.recv(4))[0]
    print("Received: {data}".format(data=x))
    return x


def tcp_send_string(sock, string):
    print("Sending: {data}".format(data=string))
    sock.send(string.encode('ascii'))


def tcp_recv_string(sock, size=1024):
    string = sock.recv(size).decode('ascii')
    print("Received: {data}".format(data=string))
    return string


def tcp_client_init(ip_address, port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip_address, port))
    print("You are CONNECTED")
    return client_socket

def udp_client_init():
    client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    print("You are CONNECTED")
    return client_socket

def udp_recv_string(sock):
    string, address = sock.recvfrom(1024)
    converted_string = string.decode('ascii')
    print("Received {data}".format(data=converted_string))
    return converted_string, address


def get_message(udp_socket):
    message, address = udp_recv_string(udp_socket)
    print(message)


def split_plus(str):
    str = str.split('+')

    ans = int(str[0]) + int(str[1])

    return ans;

def split_minus(str):
    str = str.split('-')

    ans = int(str[0]) - int(str[1])

    return ans;

def split_mult(str):
    str = str.split('-')

    ans = int(str[0]) * int(str[1])

    return ans;

def split_divide(str):
    str = str.split('/')

    ans = int(str[0]) // int(str[1])

    return ans;


def client_program():
    host = socket.gethostname()
    port = 1324

    try:
        s = tcp_client_init(host, port)
        # receive messages via UDP
        udp_socket = udp_client_init()
        udp_socket.bind(("0.0.0.0", 7181))

    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    print("Client connected")

    t = threading.Thread(target=get_message, args=(udp_socket,), daemon=True)
    t.start()

    msg = tcp_recv_string(s)

    msg = msg.split(";")
    print(msg)

    for req in msg:
        ans = 0
        if "+" in req:
            ans = split_plus(req)
            
        if "-" in req:
            ans = split_minus(req)

        if "*" in req:
            ans = split_mult(req)

        if "/" in req:
            ans = split_divide(req)

        print(req, ans)

        try:
            tcp_send_int(s, ans)
        except socket.error as m:
            print("Error: ", m.strerror)
            exit(-1) 
        time.sleep(4)

    try:
        _ = tcp_recv_string(s)
    except socket.error as m:
        print("Error: ", m.strerror)
        exit(-1)

    s.close()
    udp_socket.close()
        

if __name__ == '__main__':
    client_program()