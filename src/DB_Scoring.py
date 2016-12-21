# -*- coding: utf-8 -*-

import pymongo
import json
import sys
from pymongo import MongoClient

Ass_name = sys.argv[1]
Student = sys.argv[2]

result = open('/usr/local/Auto_Scoring_System/Assignment/' + Ass_name + "/" + Student+ '/Result/Result.json', 'r')

a = json.load(result)

print(a)

for e in a['assert']:
    print(e)

# DB-Client.
client = MongoClient('localhost', 27017)

# Database.
db = client.ass

# Collections.
#boards = db.boards
#users = db.users
uploads = db.uploads

uploads.update({'uploader': Student}, {'$set': a});
#uploads.update({'uploader': Student}, {'$push': a});

result.close()