import serial
import time

# Modem config
modem_port = serial.Serial()
modem_port.baudrate = 115200
modem_port.port = "/dev/tty.usbserial-00001114B" #change for different computers
modem_port.timeout = 2 #increase timeout in case of bad reception
modem_port.open()

def send_at_command(command):
    modem_port.write(command+"\r")
    #modem_port.sendBreak() #may need to uncomment this line for windows

if modem_port.isOpen():

    # Ready module
    send_at_command("AT")
    response = modem_port.read(100).decode('ascii').strip()
    print(response)
    print("\n")

modem_port.close()
