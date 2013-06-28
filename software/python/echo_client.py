import socket

host = 'localhost'
port = 54321
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((host,port))
s.send(bytes('Hello, world', 'ascii'))
data = s.recv(size)
s.close()

print('Received:', data)
