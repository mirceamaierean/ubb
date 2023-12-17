__author__ = 'dadi'
# import socket for all socket related primitives
import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

a = int(input('a='))
b = int(input('b='))

# The obscure struct_addr is elegantly replaced by
# a simple pair - very convenient. Replace the IP Address with
# the one of your server
s.connect(("localhost", 1234))

res = s.send(struct.pack("!H", a))
res = s.send(struct.pack('!H', b))
c = s.recv(2)

c = struct.unpack('!H', c)
print('a+b=' + c[0].__format__('d'))

s.close()
