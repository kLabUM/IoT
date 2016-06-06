#!/usr/bin/env python 

""" 
A simple bootload server 
waits for incoming command from sensor node
sends bootload file to node using simepl socket interface
""" 

import socket 
import struct

host = '' 
port = 50000 
backlog = 5 
size = 1024 #For best match with hardware and network realities, the value of bufsize should be a  power of 2, for example, 4096.
firmwareName = "./firmware.cyacd"#could add funtion to support different firmware versions for different nodes

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.bind((host,port)) 
s.listen(backlog)
firmWare = []

while 1: 
    
    #track requests by individual clients
    #for now, assume just one, but keep in mind that multiple nodes could ping us.
    client, address = s.accept() 
    
    #keep waiting as long as we receive data from the client
    while 1:
        command = client.recv(size) #may want to implement a timeout here
        nodeId = -1;
        if command: 
            #command is an integer string, corresponding with the line of the firmware file that is being requested
            #if command  == 0 - header, can also be followed by a second number corresponding with a unique node-ID
            #if command nonzero - the line in the file
            f = open(firmwareName, 'rb')
            firmWare = f.read().split(b'\n')
            f.close()
            try:
                rxCom = command.split(b',')
                if(rxCom[0] == b'0'):#header
                    nodeId = rxCom[1]
                    print('Header request. nodeID=',nodeId)
                    print(firmWare[0])
                    numLines = bytes(str(len(firmWare)), encoding='ASCII')
                    client.sendall(numLines + b"\n" + firmWare[0])
                else:
                    line = int(rxCom[0])
                    print('Line request: ', line,' length: ', len(firmWare[line]))
                    print(firmWare[line])
                    client.sendall(firmWare[line])
            except:
                print('Invalid command request.')
            
        else:
            break
    
    client.close()
    
