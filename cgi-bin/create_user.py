#!/usr/bin/python3

from urllib.parse import parse_qs
import json
import os

data = input()
dataDict = parse_qs(data)

dataBasePath = "DataBase/db.json"

if not os.path.exists(dataBasePath) or os.stat(dataBasePath).st_size == 0:
	initData = {"users": []}
	with open(dataBasePath, "w") as file:
		json.dump(initData, file)

with open(dataBasePath, "r") as file:
	fileData = json.load(file)

username = dataDict['name'][0]
age = dataDict['age'][0]
email = dataDict['email'][0]

userFileData = {
	"name": username,
	"age": age,
	"email": email
}

fileData["users"].append(userFileData)

with open(dataBasePath, "w") as file:
	json.dump(fileData, file, indent=4)

htmlfile = "<!DOCTYPE html> <html> <body> <h1> User added to DataBase </h1> </body> </html>"

out = "HTTP/1.1 201 Created\r\n"
out += "Server: webserv\r\n"
out += "Connection: keep-alive\r\n"
out += "Content-Length: " + str(len(htmlfile)) + "\r\n"
out += "\r\n"
out += htmlfile

print(out)
