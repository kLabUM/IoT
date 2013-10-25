import time
import datetime
import random
import string
import os
from twisted.internet import protocol, reactor
from twisted.application import internet, service

# interface amazon aws
from boto.dynamodb2.fields import HashKey, RangeKey, KeysOnlyIndex, AllIndex
from boto.dynamodb2.layer1 import DynamoDBConnection
from boto.dynamodb2.table import Table
from boto.dynamodb2.types import NUMBER
# configure and connect to aws dynamo db
log = Table('log_raw')

class Echo(protocol.Protocol):
    def dataReceived(self, packet):
        self.transport.write(packet)
        timestamp = datetime.datetime.fromtimestamp(time.time()).strftime('%Y%m%d%H%M%S:')
        random_string = ''.join(random.sample(string.lowercase+string.digits, 10))
        log.put_item(data={
            'id': timestamp + random_string,
            'message': str(packet)
        })

class EchoFactory(protocol.Factory):
    def buildProtocol(self, addr):
        return Echo()

port = 50123
factory = EchoFactory()

# this is the important bit
application = service.Application("echo")  # create the Application
echoService = internet.TCPServer(port, factory) # create the service
# add the service to the application
echoService.setServiceParent(application)
