import serial
import time

# Modem config
modem_port = serial.Serial()
modem_port.baudrate = 115200
modem_port.port = "COM5"
modem_port.parity = "N"
modem_port.stopbits = 1
modem_port.xonxoff = 0
modem_port.open()

def send_at_command(command):
    modem_port.write(bytes(command+"\r", encoding='ascii'))

if modem_port.isOpen():

    # Ready Module
    send_at_command("AT")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

    # Check network status
    send_at_command("AT+CREG?")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

    send_at_command("AT#CAI?")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

    send_at_command("AT+CSQ")
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print(modem_port.readline().decode('ascii').strip())
    print("\n")

modem_port.close()
