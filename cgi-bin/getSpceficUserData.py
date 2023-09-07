#!/usr/bin/python3

from urllib.parse import parse_qs
import json
import os

def getUserInfo(db, userToRemove):
	if userToRemove == None:
		return None
	users_list = db["users"]
	for user in users_list:
		if user["id"] == userToRemove:
			return user
	return None

data = os.getenv('QUERY_STRING')
dataDict = parse_qs(data)

if 'id' in dataDict and dataDict['id']:
	id = int(dataDict['id'][0])
else:
	id = None

dataBaseDir = "mysite/users_database_website/DataBase"
dataBaseFileName = "db.json"
dataBasePath = os.path.join(dataBaseDir, dataBaseFileName)

with open(dataBasePath, "r") as file:
	fileData = json.load(file)

user_data = getUserInfo(fileData, id)

if user_data:
	id_str = f"<h2>USER ID -> {user_data['id']} </h2>"
	name = f"<p>Name:  {user_data['name']} </p>"
	age = f"<p>Age:   {user_data['age']} </p>"
	email = f"<p>Email: {user_data['email']} </p>"
	msg = id_str + name + age + email
else:
	msg = "Id does not match any existent user in DataBase"

htmlfile = "<!DOCTYPE html> <html> <body> <h1> "
htmlfile += msg
htmlfile += """ </h1> <button onclick="window.location.href='/'" type="button">Initial Page</button> </body> </html> """

out = "Status: 200 OK\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Type: text/html\n"
out += "\n"
out += htmlfile

print(out)
