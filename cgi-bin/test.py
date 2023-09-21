#!/usr/bin/python3

import sys
import time


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

content_length = 9

#input_data = input()
#time.sleep(35)

htmlfile = "<!DOCTYPE html> <html> <body> <h1> Script de teste </h1> </body> </html>"

out = "Status: 200 OK\n"
out = "Content-Type: text/html" + "\n"
out += "\n"
out += htmlfile

print(out)
exit(0)