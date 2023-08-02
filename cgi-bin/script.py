#!/usr/bin/python3

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

content_length = 9

input_data = input()

nome_arquivo = "fromPython.txt"

# Abre o arquivo no modo de escrita ("w") e grava o input nele
with open(nome_arquivo, "w") as arquivo:
    arquivo.write(input_data)

htmlfile = "<!DOCTYPE html> <html> <body> <h1> Mensagem enviada para o Script </h1> </body> </html>"

out = "HTTP/1.1 200 OK\r\n"
out += "Server: webserv\r\n"
out += "Connection: keep-alive\r\n"
out += "Content-Length: " + str(len(htmlfile)) + "\r\n"
out += "\r\n"
out += htmlfile

print(out)
exit(0)
