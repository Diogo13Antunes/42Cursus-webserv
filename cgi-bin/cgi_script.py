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

# print(message)
print(message)
time.sleep(1)
print("hello")
time.sleep(1)
print("facking")
time.sleep(1)
print("world")
