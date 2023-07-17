#!/usr/bin/python3

import sys
import os

class Unbuffered(object):
   def __init__(self, stream):
       self.stream = stream
   def write(self, data):
       self.stream.write(data)
       self.stream.flush()
   def writelines(self, datas):
       self.stream.writelines(datas)
       self.stream.flush()
   def __getattr__(self, attr):
       return getattr(self.stream, attr)

sys.stdout = Unbuffered(sys.stdout)

message = input()

RequestMethod = os.environ.get("REQUEST_METHOD")

htmlfile = "<!DOCTYPE html> <html> <body> <h1> Hello World </h1> " 
htmlfile += "<h1> " + message + " </h1>"
htmlfile += "<h2> " + " ---- Env Variables ---- " + " </h2>"
for key, value in os.environ.items():
	if key != 'LC_CTYPE':
		htmlfile += "<p> " + str(key) + " -> " + str(value) + " </p>"
htmlfile += " </body> </html>"

out = "HTTP/1.1 200 OK\r\n"
out += "Server: webserv\r\n"
out += "Connection: keep-alive\r\n"
out += "Content-Length: " + str(len(htmlfile)) + "\r\n"
out += "\r\n"
out += htmlfile

print(out)

exit(0)