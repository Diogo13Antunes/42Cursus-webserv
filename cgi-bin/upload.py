#!/usr/bin/python3

import cgi, os, sys

form = cgi.FieldStorage()
status = "200 OK"

directory = os.getenv('DOCUMENT_ROOT')

if not os.path.exists(directory) or not os.path.isdir(directory):
	os.mkdir(directory)

file = form['fileTest']
if file.filename:
	fileName = os.path.basename(file.filename)
	open(directory + fileName, 'wb').write(file.file.read())
	status = "201 Created"
	htmlfile = """
<!DOCTYPE html>
<html lang="en">
	<head>
		<title>Upload</title>
		<link rel="icon" href="favicon.ico" type="image/x-icon">
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">  
	</head>
	<body>
		<h1> File Uploaded Successfully </h1>
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-HwwvtgBNo3bZJJLYd8oVXjrBZt8cqVSpeBNS5n7C8IVInixGAoxmnlMuBnhbgrkm" crossorigin="anonymous"></script>
	</body>
</html>
"""
else:
	htmlfile = """
<!DOCTYPE html>
<html lang="en">
	<head>
		<title>Upload</title>
		<link rel="icon" href="favicon.ico" type="image/x-icon">
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">  
	</head>
	<body>
		<h1> File was not Uploaded with Success </h1>
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-HwwvtgBNo3bZJJLYd8oVXjrBZt8cqVSpeBNS5n7C8IVInixGAoxmnlMuBnhbgrkm" crossorigin="anonymous"></script>
	</body>
</html>
"""

out = "Status: " + status +"\n"
out += "Server: webserv\n"
out += "Connection: keep-alive\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Type: " + "text/html" + "\n"
out += "\n"
out += htmlfile

print (out);
