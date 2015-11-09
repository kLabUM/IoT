import serial
import time
import struct

# Modem config
modem_port = serial.Serial()
modem_port.baudrate = 9600
modem_port.port = "/dev/tty.USA19Hfa13P1.1" #change for different computers
modem_port.timeout = 2 #increase timeout in case of bad reception
modem_port.open()

def send_command(command):
    modem_port.write(command)
    #modem_port.sendBreak() #may need to uncomment this line for windows

if modem_port.isOpen():

    # Ready module
    test_command = "\x00\x61\xFF\x18\x24\x10" # B command...returns temperature and depth
    #test_command = "\xFF\xFF\xFF\xFF\xFF\xFF" # B command...returns temperature and depth
    #test_command = "\x00\x00\x00\x00\x00\x00" # B command...returns temperature and depth
    send_command(test_command)
    
    response = modem_port.read(100)

    data = response.split('+')
    
    celsius = data[1][:data[1].find('\xb0')]
    meters = data[2][:data[2].find('m')]
    print 'Temp: ', celsius, 'C'
    print 'Depth: ', meters, 'm'

modem_port.close()
