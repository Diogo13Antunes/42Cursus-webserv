#!/usr/bin/python3

from urllib.parse import parse_qs
import json
import os

data = input()
dataDict = parse_qs(data)

dataBaseDir = "mysite/users_database_website/DataBase"
dataBaseFileName = "db.json"
dataBasePath = os.path.join(dataBaseDir, dataBaseFileName)

if not os.path.exists(dataBaseDir):
    os.makedirs(dataBaseDir)

if not os.path.exists(dataBasePath) or os.stat(dataBasePath).st_size == 0:
	initData = {"users": [], "last_id": 0}
	with open(dataBasePath, "w") as file:
		json.dump(initData, file)

with open(dataBasePath, "r") as file:
	fileData = json.load(file)

username = dataDict['name'][0]
age = dataDict['age'][0]
email = dataDict['email'][0]

if "last_id" in fileData:
    last_id = fileData["last_id"]
else:
    last_id = 0

new_id = last_id + 1

userFileData = {
    "id": new_id,
	"name": username,
	"age": age,
	"email": email
}

fileData["users"].append(userFileData)
fileData["last_id"] = new_id

with open(dataBasePath, "w") as file:
	json.dump(fileData, file, indent=4)

htmlfile = """ <!DOCTYPE html> <html> <body> <h1> User added to DataBase </h1> <button onclick="window.location.href='/'" type="button">Initial Page</button> </body> </html> """

out = "Status: 201 Created\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Type: text/html\n"
out += "\n"
out += htmlfile

print(out)
