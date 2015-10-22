import serial
import time

# Modem config
modem_port = serial.Serial()
modem_port.baudrate = 115200
modem_port.port = "COM5" #change for different computers
modem_port.timeout = 10 #increase timeout in case of bad reception
modem_port.open()

def send_at_command(command):
    modem_port.write(bytes(command+"\r",'UTF-8'))
    #modem_port.sendBreak() #may need to uncomment this line for windows

if modem_port.isOpen():

    i = 0
    while(i < 1):

        # Ready module
        send_at_command("AT+CSQ")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")

        # Ready module
        send_at_command("AT+CREG=1")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")
        
        #send_at_command("AT#SCFG=1,1,0,0,1200,0")
        #response = modem_port.read(100).decode('ascii').strip()
        #print(response)
        #print("\n")
        
        send_at_command("AT#CGPADDR=1")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")
        
        if("\"" not in response):
            send_at_command("AT#SGACT=1,1")
            response = modem_port.read(100).decode('ascii').strip()
            print(response)
            print("\n")

        send_at_command("AT#SD=1,0,50030,\"184.72.228.61\",0,0,1")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")
        
        send_at_command("AT#SSEND=1")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")
        
        send_at_command("Sent from evk2." + str(i) + "\032")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")

        #close connection
        send_at_command("AT#SH=1")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")

        send_at_command("AT#SGACT=1,0")
        response = modem_port.read(100).decode('ascii').strip()
        print(response)
        print("\n")

        i += 1

modem_port.close()
