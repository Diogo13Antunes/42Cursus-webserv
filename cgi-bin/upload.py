#!/usr/bin/python3

import cgi, os

form = cgi.FieldStorage()
status = "200 OK"

directory = os.getenv('DOCUMENT_ROOT')

if not os.path.exists(directory):
    os.makedirs(directory)

htmlfile = """
<!DOCTYPE html>
<html lang="en">
	<head>
		<title>Upload</title>
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">  
	</head>
	<body>
"""

file = form['fileTest']
if file.filename:
	fileName = os.path.basename(file.filename)
	open(directory + fileName, 'wb').write(file.file.read())
	status = "201 Created"
	msg = " <h1> File Uploaded Successfully </h1> "
else:
	msg = "<h1> File was not Uploaded with Success </h1> "

htmlfile += msg

htmlfile += """		
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/js/bootstrap.bundle.min.js" integrity="sha384-HwwvtgBNo3bZJJLYd8oVXjrBZt8cqVSpeBNS5n7C8IVInixGAoxmnlMuBnhbgrkm" crossorigin="anonymous"></script>
		<div class="d-grid gap-2 mx-3">
			<button onclick="window.location.href='/'" type="button" class="btn btn-outline-primary">Initial Page</button>
		</div>
	</body>
</html>
"""

out = "Status: " + status +"\n"
out += "Connection: keep-alive\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Type: " + "text/html" + "\n"
out += "\n"
out += htmlfile

print (out)
