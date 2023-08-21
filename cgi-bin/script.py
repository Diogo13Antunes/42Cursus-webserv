#!/usr/bin/python3

input_data = input()
input_data += input()
input_data += input()
input_data += input()
input_data += input()
input_data += input()
input_data += input()
input_data += input()
input_data += input()

htmlfile = "<!DOCTYPE html> <html> <body> <h1> Mensagem enviada para o Script </h1> " + "<h2>" + input_data + "</h2>" " </body> </html>"

out = "Status: 200 OK\n"
out += "Server: webserv\n"
out += "Connection: keep-alive\n"
out += "Content-Type: text/html" + "\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "\n"
out += htmlfile

print(out)
exit(0)
