import socket, struct, random, sys, time


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


if __name__ == '__main__':
    try:
        host = socket.gethostname()
        port = 1234
        s = tcp_init_client(host, port)

    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    random.seed()
    start = 1
    end = 100000

    data = tcp_recv_string(s)

    finished = False
    step_count = 0

    while not finished:
        my_num = random.randint(start, end)

        try:
            tcp_send_int(s, my_num)
            print("my_num ", my_num)
            answer = tcp_recv_string(s)
            print("answer ", answer)
        except socket.error as msg:
            print("Error: ", msg.strerror)
            s.close()
            exit(-2)
        
        step_count += 1
        print("sent ", my_num, " received ", answer)

        if answer == "S":
            end = my_num - 1
        elif answer == "H":
            start = my_num + 1
            
        if answer == "G" or answer == "L":
            finished = True
        
        time.sleep(0.25)

    s.close()
    if answer == "G":
        print("I am the winner with ", my_num, " in ", step_count, " steps")
    else:
        print("I lost")