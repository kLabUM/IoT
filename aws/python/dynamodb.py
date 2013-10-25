from boto.dynamodb2.fields import HashKey, RangeKey, KeysOnlyIndex, AllIndex
from boto.dynamodb2.layer1 import DynamoDBConnection
from boto.dynamodb2.table import Table
from boto.dynamodb2.types import NUMBER

items = Table('log_dev')
all_items = items.scan()
for item in all_items:
   print(item["id"])
   item.delete()
