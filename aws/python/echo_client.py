import socket

#host = '141.212.136.222'
#host = 'localhost'
host = '141.212.136.222' #IP Address Test

port = 50000
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))
packet = bytes("Im Karun!", "utf-8")
s.send(packet)
data = s.recv(size)
s.close()
print('Received:', data)
