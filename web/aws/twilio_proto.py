# interface amazon aws
# interface amazon aws
from boto.dynamodb2.fields import HashKey, RangeKey, KeysOnlyIndex, AllIndex
from boto.dynamodb2.layer1 import DynamoDBConnection
from boto.dynamodb2.table import Table
from boto.dynamodb2.types import NUMBER
# twilio
from datetime import date
from twilio.rest import TwilioRestClient
# time
import time
import datetime

# twilio authentication
account_sid = "ACf038afa2d8ed31ba3676f0f85230742a"
auth_token  = "c51a8ab01a04a7576f6daa4d47b9a983"
client = TwilioRestClient(account_sid, auth_token)

# configure and connect to aws dynamo db
table  = Table('log_prototype')

# get all message from module from today, which has the number +7346199939
messages = client.sms.messages.list(from_="7346199939")

# iterate over each text message
for message in messages:
    timestamp = message.date_created
    year = timestamp.strftime("%Y")
    month = timestamp.strftime("%m")
    day = timestamp.strftime("%d")

    print(message.sid)
    # write data
    table.put_item(data={
        'id': message.sid,
        'modem_id': message.from_,
        'message_body': message.body,
        'sensor_ultrasonic': int(message.body.split("R")[1].split("\r")[0]),
        'timestamp': unicode(timestamp),
        'timestamp_year': int(year),
        'timestamp_month': int(month),
        'timestamp_day': int(day),
    }, overwrite=True)
