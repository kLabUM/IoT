#!/usr/bin/env python 

""" 
A simple node simulator 
""" 
import struct
import socket 
import time

host = '' 
port = 50000 
backlog = 5 
size = 1024 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect((host,port)) 
s.sendall(b'0,MEID12345')#header request
resp = s.recv(1024)
print(resp)
for line in range(int(resp.split(b'\n')[0]))[1:]:
    time.sleep(.1)
    s.sendall(bytes(str(line), encoding='ASCII'))#line request
    resp = s.recv(1024)
    print(resp)
