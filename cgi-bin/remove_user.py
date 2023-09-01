#!/usr/bin/python3

from urllib.parse import parse_qs
import json
import os

def removeUserFromDataBase(db, userToRemove):
	users_list = db["users"]
	for user in users_list:
		if user["id"] == userToRemove:
			users_list.remove(user)
			return True
	return False

data = input()
dataDict = parse_qs(data)
id = int(dataDict['id'][0])

dataBaseDir = "mysite/users_database_website/DataBase"
dataBaseFileName = "db.json"
dataBasePath = os.path.join(dataBaseDir, dataBaseFileName)

with open(dataBasePath, "r") as file:
	fileData = json.load(file)

if removeUserFromDataBase(fileData, id) == True:
	with open(dataBasePath, "w") as file:
		json.dump(fileData, file, indent=4)
	msg = "User removed from DataBase"
else:
	msg = "Id does not match any existent user in DataBase"

htmlfile = "<!DOCTYPE html> <html> <body> <h1> "
htmlfile += msg
htmlfile += " </h1> </body> </html>"

out = "Status: 200 OK\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Type: text/html\n"
out += "\n"
out += htmlfile

print(out)
