# Solution for test_sockets
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
    print("Sending TCP: {data}".format(data=string))
    sock.send(string.encode('ascii'))


def tcp_recv_string(sock, size=1024):
    string = sock.recv(size).decode('ascii')
    print("Received: {data}".format(data=string))
    return string


def udp_send_string(sock, string, dest_address):
    print("Sending UDP {data}".format(data=string))
    print("To {data}".format(data=dest_address))
    sock.sendto(string.encode('ascii'), dest_address)


def udp_server_init(ip_address, port):
    udp_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    # udp_socket.bind((ip_address, port))
    print("UDP Server RUNNING...")
    return udp_socket


def worker(cs):
    global message
    ident =  threading.get_ident()

    print("Id of the thread is", ident)

    correct_answer = [12, 2, 4]
    tcp_send_string(cs, message)

    correct_count = 0

    for correct in correct_answer:
        try:
            ans = tcp_recv_int(cs)

            if ans == correct:
                correct_count += 1
        except socket.error as msg:
            print("Error: ", msg.strerror)
            break;

        time.sleep(0.5)

    score = "You have answered correctly to " + str(correct_count) + " questions"

    tcp_send_string(cs, score)
    cs.close()
    print("Client #" + str(ident) + " disconnected")

my_lock = threading.Lock()
stop = False;
message = "10+2;4/2;3+1"
sockets = []

def udp_worker(udp_socket):
    global my_lock, stop, message, sockets

    while not stop:
        udp_send_string(udp_socket, "Solve these exercises: " + message, ("255.255.255.255", 7181))
        time.sleep(2)

def stop_exec():
    global stop
    time.sleep(12)
    print("12 seconds have passed")
    my_lock.acquire()
    stop = True
    my_lock.release()

            
def tcp_server_init(ip_address, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((ip_address, port))
    server_socket.listen(7)
    print("TCP Server RUNNING...")
    return server_socket


def udp_client_init():
    client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    print("You are CONNECTED")
    return client_socket

def server_program():
    global stop, sockets
    host = socket.gethostname()

    port = 1324

    try:
        rs = tcp_server_init(host, port)
        rs.settimeout(12)
        # send message to client via udp on port 7181
        udp_socket = udp_server_init(host, 7181)
    except socket.error:
        exit(-1)

    # udp_socket.sendto(b'D', ("255.255.255.255", 7181))

    t = threading.Thread(target = stop_exec, daemon = True)
    t.start()

    t1 = threading.Thread(target=udp_worker, args=(udp_socket, ), daemon = True)
    t1.start()

    while not stop:
        try:
            client_socket, client_addres = rs.accept()
        except socket.timeout:
            break

        if stop:
            break

        my_lock.acquire()
        sockets.append(client_addres)
        my_lock.release()

        t = threading.Thread(target = worker, args = (client_socket,), daemon = True)
        t.start()
        
        if stop == True:
            break

    rs.close()
    udp_socket.close()

if __name__ == '__main__':
    server_program()