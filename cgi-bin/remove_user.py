import json

def removeUserFromDataBase(db, userToRemove):
	for users in db["users"]:
		if users["name"] == userToRemove:
			db["users"].remove(users)
			return True
	return False

username = input("USERNAME -> ")
dataBasePath = "DataBase/db.json"

with open(dataBasePath, "r") as file:
	fileData = json.load(file)

if removeUserFromDataBase(fileData, username) == True:
	with open(dataBasePath, "w") as file:
		json.dump(fileData, file, indent=4)
	msg = "Username removed from DataBase"
else:
	msg = "Error: Username does not exist"

htmlfile = "<!DOCTYPE html> <html> <body> <h1> "
htmlfile += msg
htmlfile += " </h1> </body> </html>"

out = "HTTP/1.1 201 Created\r\n"
out += "Server: webserv\r\n"
out += "Connection: keep-alive\r\n"
out += "Content-Length: " + str(len(htmlfile)) + "\r\n"
out += "\r\n"
out += htmlfile

print(out)
