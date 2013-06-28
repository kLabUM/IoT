import serial
import time

# Modem config
modem_port = serial.Serial()
modem_port.baudrate = 115200
modem_port.port = "/dev/tty.usbserial-00002114B"
modem_port.timeout = 5
modem_port.open()


def send_at_command(command):
    modem_port.write(bytes(command+"\r", encoding='ascii'))
    modem_port.sendBreak()

if modem_port.isOpen():

    # Ready module
    send_at_command("AT")
    print(modem_port.read(100).decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    print("\n")

    '''

    # Check network status
    send_at_command("AT+CREG=1")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

    send_at_command("AT+CREG?")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    print("\n")

    # Check signal strength
    send_at_command("AT+CSQ")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    print("\n")

    # Configure socket
    send_at_command("AT#SCFG=1,1,0,0,600,0")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

    # Obtain IP from network
    send_at_command("AT#SGACT=1,1")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    #print(modem_port.readline().decode('ascii').strip())
    print("\n")

    # Connect
    send_at_command("#AT#SD=1,0,10510,\"88.37.127.164\"")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

    #AT#SD=1,0,10510,"88.37.127.164"
    #AT#SD=1,0,35421,"50.19.242.87”
    #AT#SD=1,0,54321,"68.40.205.20”

    '''
modem_port.close()
