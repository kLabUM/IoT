# interface amazon aws
from boto.dynamodb2.fields import HashKey, RangeKey, KeysOnlyIndex, AllIndex
from boto.dynamodb2.layer1 import DynamoDBConnection
from boto.dynamodb2.table import Table
from boto.dynamodb2.types import NUMBER

# socket framework
import socket

# time
import time
import datetime

# configure and connect socket
host = ''
port = 50123
backlog = 5
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host,port))
s.listen(backlog)

# configure and connect to aws dynamo db
log = Table('dev_raw')

# listen for tcp connection
while 1:
    client, address = s.accept()
    packet = client.recv(size)

    if packet:
        timestamp = str(datetime.datetime.now())
        log.put_item(data={
            'id': timestamp,
            'packet': str(packet)
        })
        client.send(packet)
        time.sleep(1)

    client.close()

