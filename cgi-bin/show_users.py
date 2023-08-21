#!/usr/bin/python3

import json
import os

fullPath = "DataBase/db.json"

htmlRes = """
<!DOCTYPE html>
<html lang="en">
	<head>
		<title>Show Users</title>
		<link rel="icon" href="favicon.ico" type="image/x-icon">
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">  
	</head>
	<body>
		<h1> Show all users inside Users DataBase </h1>
"""

if os.path.exists(fullPath):
	with open(fullPath, "r") as file:
		data = json.load(file)

	if len(data.get("users", [])):
		
		htmlRes += """
			<div>
					<table class="table align-middle table-bordered table-responsive">
						<thead>
							<tr>
								<th scope="col">#</th>
								<th scope="col">Name</th>
								<th scope="col">Age</th>
								<th scope="col">Email</th>
							</tr>
						</thead>
						<tbody>\n"""
		index = 1
		for users in data["users"]:
			htmlRes += "							<tr>\n"
			htmlRes += "								<th scope=\"row\"> " + str(index) + "</th>\n"
			htmlRes += "								<td>" + str(users["name"]) + "</td>\n"
			htmlRes += "								<td>" + str(users["age"]) + "</td>\n"
			htmlRes += "								<td>" + str(users["email"]) + "</td>\n"
			htmlRes += "							</tr>\n"
			index = index + 1
		htmlRes += """
  						</tbody>
					</table>
				</div>
		"""
	else:
		htmlRes += """ <h2> No users in DataBase </h2> """
else:
	htmlRes += """ <h2> The DataBase file does not Exist </h2> """

htmlRes += """
		<div class="d-grid gap-2 col-6 mx-auto">
			<button onclick="window.location.href='/'" type="button" class="btn btn-outline-primary">Initial Page</button>
		</div>
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-HwwvtgBNo3bZJJLYd8oVXjrBZt8cqVSpeBNS5n7C8IVInixGAoxmnlMuBnhbgrkm" crossorigin="anonymous"></script>
	</body>
</html>
"""

out = "HTTP/1.1 200 OK\r\n"
out += "Server: webserv\r\n"
out += "Connection: keep-alive\r\n"
out += "Content-Length: " + str(len(htmlRes)) + "\r\n"
out += "\r\n"
out += htmlRes

print(out)
