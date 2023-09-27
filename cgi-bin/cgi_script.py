#!/usr/bin/python3

import sys
import os
import time

message = input()

#time.sleep(10)

RequestMethod = os.environ.get("REQUEST_METHOD")

htmlfile = "<!DOCTYPE html> <html> <body> <h1> Hello World </h1> " 
htmlfile += "<h2> " + " ---- Body Message ---- " + " </h2>"
htmlfile += "<p> " + message + " </p>"
htmlfile += "<h2> " + " ---- Env Variables ---- " + " </h2>"
for key, value in os.environ.items():
	if key != 'LC_CTYPE':
		htmlfile += "<p> " + str(key) + " -> " + str(value) + " </p>"
htmlfile += " </body> </html>"


out = "Status: 200 OK\n"
out = "Content-Type: text/html" + "\n"
out += "\n"
out += htmlfile

print(out)

