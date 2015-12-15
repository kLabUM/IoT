import serial
import time
import random
from time import sleep

# Modem config
modem_port = serial.Serial()
modem_port.baudrate = 115200
modem_port.port = "COM4" #change for different computers
modem_port.timeout = 2 #increase timeout in case of bad reception
modem_port.open()

def modem_write(command):
    modem_port.write(command+"\r")

def send_at_command(command,timeout=2):
    modem_port.timeout = timeout
    modem_write(command)
    response = modem_port.read(3000).decode('ascii').strip()
    print(response)
    return response

d = {}
meid = send_at_command('AT#MEID?').split('MEID:')[1].split('\r')[0].strip().replace(',', '')
d[meid] = {}
d[meid].update({'ESN' : send_at_command('AT+CGSN').split('\n')[1].strip()})
MDN, MSIN = send_at_command('AT#MODEM?').split()[2].split(',')[:2]
d[meid].update({'MDN' : MDN})
d[meid].update({'MSIN' : MSIN})

with open("modemtest.txt", "a") as outfile:
    outfile.write(str(d))
    
# After all cell modules are read:

import ast
import pandas as pd

r = open('modemtest.txt', 'r').readlines()
L = ast.literal_eval(r[0].replace('}}{', '}},{'))
k = [i.keys()[0] for i in L]
v = [i.values()[0] for i in L]
df = pd.DataFrame.from_dict(dict(zip(k, v)), orient='index').astype(str)
df.to_csv('Telit Modules.csv')