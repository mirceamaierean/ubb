import struct
import socket

s = socket.create_server(("192.168.64.1", 1234))
s.listen(5)

while True:
    c, addr = s.accept()
    a = c.recv(2)
    a = struct.unpack('!H', a)
    b = c.recv(2)
    b = struct.unpack('!H', b)
    print("Received from address: ", addr)
    print("Received data: ", a[0], b[0])
    sum = a[0] + b[0]
    c.send(struct.pack('!H', sum))
