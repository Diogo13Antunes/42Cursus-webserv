#!/usr/bin/python3

import time
import sys

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

"""
print("-----------------------------------------------------------------")
print("From C++    -> " + message)
print("From Python -> Hi! I am the python script. =)")
print("-----------------------------------------------------------------")
"""

htmlfile = "<!DOCTYPE html> <html> <body> <h1> Hello World </h1> " 
htmlfile += "<h1> " + message + " </h1>"
htmlfile += " </body> </html>"

out = "HTTP/1.1 200 OK\r\n"
out += "Server: webserv\r\n"
out += "Connection: keep-alive\r\n"
out += "Content-Lemgth: " + str(len(htmlfile)) + "\r\n"
out += "\r\n"
out += htmlfile

print(out)

exit(0)