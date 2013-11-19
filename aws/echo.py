#!/usr/bin/env python 

""" 
A simple echo server 
""" 

import socket 
from time import gmtime, strftime

host = '' 
port = 50050 
backlog = 5 
size = 1024 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.bind((host,port)) 
s.listen(backlog) 
while 1: 
    client, address = s.accept() 
    data = client.recv(size) 
    if data:
        fh = open("log.txt","a")

        tm = strftime("%Y-%m-%d %H:%M:%S", gmtime())
        print(tm + " " + str(data))
        fh.write("\r\n" + tm + " " + str(data))
        
        fh.close()
    client.close()
