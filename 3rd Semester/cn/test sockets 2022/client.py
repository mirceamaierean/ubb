import socket, struct, random, time

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

def tcp_init_client(host, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    return s;

def client_program():
    host = socket.gethostname()
    port = 1234

    try:
        cs = tcp_init_client(host, port)
    except socket.error as e:
        print(e)
        exit(1)

    message = tcp_recv_string(cs)
    print(message)
    
    # generate an array that has pairs of coordinates for the range [0, 4]
    all = []
    for i in range(5):
        for j in range(5):
            all.append((i, j))

    random.seed()

    while not len(all) == 0:
        # get a random pair of coordinates
        x, y = random.choice(all)
        all.remove((x, y))

        print("Sending: {x}, {y}".format(x=x, y=y))

        tcp_send_int(cs, x)
        tcp_send_int(cs, y)

        try:
            message = tcp_recv_string(cs)
        except socket.error as e:
            print("Over")
            break

        print(message)
        
        if message[-1] == "Y":
            break
        

        time.sleep(0.5)
    
    print("Game over!")
    cs.close()

if __name__ == "__main__":
    client_program()
    