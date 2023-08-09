import json
import os

fullPath = "DataBase/db.json"

if os.path.exists(fullPath):
	with open(fullPath, "r") as file:
		data = json.load(file)

	if len(data.get("users", [])):
		print("------------------------------")
		for users in data["users"]:
			print("Name:", users["name"])
			print("Age:", users["age"])
			print("------------------------------")
	else:
		print("------------------------------")
		print("No users in DataBase")
		print("------------------------------")
else:
	print("Error: DataBase file does not exist.")
