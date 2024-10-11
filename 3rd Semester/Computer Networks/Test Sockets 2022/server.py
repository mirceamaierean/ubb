import socket, struct, threading, time, random

def tcp_send_int(sock, x):
    print('Sending: {data}'.format(data=x))
    sock.send(struct.pack('!i', x))

def tcp_recv_int(sock):
    x = struct.unpack('!i', sock.recv(4))[0]
    return x

def tcp_send_string(sock, string):
    sock.send(string.encode('ascii'))

def tcp_recv_string(sock, size=1024):
    string = sock.recv(size).decode('ascii')
    return string

def tcp_server_init(ip_address, port):
    server_socket = socket.create_server((ip_address, port), family = socket.AF_INET, backlog = 10, reuse_port = True)
    print('TCP Server RUNNING...')
    return server_socket

matrix = []
my_lock = threading.Lock()
my_event = threading.Event()
my_event.clear()
total = 0
cnt_found = 0
threads = []
clients_connected = 0

def worker(cs):
    global matrix, my_lock, my_event, total, cnt_found, clients_connected, winning_thread

    guess_cnt = 0

    clients_connected += 1
    message = "Welcome to the server! You are client number {num}".format(num=clients_connected)
    tcp_send_string(cs, message)

    print("Total treasures:", total)

    while cnt_found < total:
        try:
            x = tcp_recv_int(cs)
            y = tcp_recv_int(cs)
        except socket.error as e:
            print(e)
            break

        print("Received:", x, y)

        if matrix[x][y] == 1:
            my_lock.acquire()
            guess_cnt += 1
            matrix[x][y] = -1
            cnt_found += 1
            my_lock.release()
        
        message = "Number of treasures found: " + str(cnt_found)

        tcp_send_string(cs, message)

        time.sleep(0.5)

    if cnt_found == total:
       tcp_send_string(cs, "You have guessed {guess_cnt} treasuresY".format(guess_cnt=guess_cnt))

    my_event.set()
    cs.close()

def game_master():
    global matrix, my_lock, my_event, total, cnt_found, threads, clients_connected

    while True:
        my_event.wait()
        my_event.clear()
        for t in threads:
            t.join()

        my_lock.acquire()

        matrix = [[0 for _ in range(5)] for _ in range(5)]
        
        total = random.randint(1, 25)
        
        for _ in range(total):
            x = random.randint(0, 4)
            y = random.randint(0, 4)
            
            while matrix[x][y] == 1:
                x = random.randint(0, 4)
                y = random.randint(0, 4)
            
            matrix[x][y] = 1

        print("Total treasures:", total)

        for i in range(5):
            print(matrix[i])
        
        
        threads = []
        cnt_found = 0
        my_lock.release()

def server_program():
    global matrix, total

    matrix = [[0 for _ in range(5)] for _ in range(5)]
    total = random.randint(1, 25)
    for _ in range(total):
        x = random.randint(0, 4)
        y = random.randint(0, 4)
        
        while matrix[x][y] == 1:
            x = random.randint(0, 4)
            y = random.randint(0, 4)
        
        matrix[x][y] = 1
        
    print("Total treasures:", total)

    for i in range(5):
        print(matrix[i])

    host = socket.gethostname()
    port = 1234

    try:
        rs = tcp_server_init(host, port)
    except socket.error as e:
        print(e)
        exit(-1)

    t = threading.Thread(target = game_master, daemon = True)
    t.start()

    while True:
        client_server, client_address = rs.accept()

        print('Connected to: {addr}'.format(addr=client_address))

        t = threading.Thread(target = worker, args = (client_server,), daemon = True)
        threads.append(t)
        t.start()

if __name__ == '__main__':
    server_program()