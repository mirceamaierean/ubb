import socket, struct, random, threading, time

random.seed()
start = 1
stop = 100000
my_num = random.randint(start, stop)
my_lock = threading.Lock()
client_guessed = False
winner_thread = 0
e = threading.Event()
e.clear()
threads = []
client_count = 0

def tcp_send_int(sock, x):
    sock.send(struct.pack("!i", x))

def tcp_recv_int(sock):
    x = struct.unpack("!i", sock.recv(4))[0]
    return x

def tcp_send_string(sock, string):
    sock.send(string.encode('ascii'))

def tcp_recv_string(sock, sz=1024):
    string = sock.recv(sz).decode('ascii')
    return string

def tcp_init_server(ip_addr, port):
    return socket.create_server((ip_addr, port), family = socket.AF_INET, backlog = 10, reuse_port = True)

def worker(cs):
    global my_lock, client_guessed, my_num, winner_thread, client_count, e

    my_id_count = client_count
    message = "Hello client #" + str(client_count) + "! You are entering the number guess competition"
    tcp_send_string(cs, message)

    while not client_guessed:
        try:
            guess = tcp_recv_int(cs)

            if (guess > my_num):
                tcp_send_string(cs, 'S')
            
            elif (guess < my_num):
                tcp_send_string(cs, 'H')
            
            else:
                my_lock.acquire()
                client_guessed = True
                winner_thread = threading.get_ident()
                my_lock.release()

        except socket.error as msg:
            print("Error: ", msg.strerror)
            break;

    if client_guessed:
        if threading.get_ident() == winner_thread:
            tcp_send_string(cs, 'G')
            print("Client #" + str(my_id_count) + " guessed the number!")
            e.set()
        else:
            tcp_send_string(cs, 'L')
            print("Client #" + str(my_id_count) + " lost the game!")

    time.sleep(1)
    cs.close()
    print("Client #" + str(my_id_count) + " disconnected")

def resetServer():
    global client_guessed, my_num, winner_thread, client_count, e, threads
    while True:
        e.wait()
        for t in threads:
            t.join()
        print("All the threads finished")
        e.clear()
        my_lock.acquire()
        client_guessed = False
        my_num = random.randint(start, stop)
        print("New number is: " + str(my_num))
        threads = []
        client_count = 0
        winner_thread = -1
        my_lock.release()

if __name__ == "__main__":
    print("Server is running, number is: " + str(my_num))
    try:
        host = socket.gethostname()
        port = 1234
        # init rendez vous socket
        rs = tcp_init_server(host, port)
        rs.listen(6)
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    t = threading.Thread(target = resetServer, daemon = True)
    t.start()

    while True:
        client_socket, client_addres = rs.accept()
        t = threading.Thread(target = worker, args = (client_socket,))
        threads.append(t)
        client_count += 1
        t.start()