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

htmlfile = "<!DOCTYPE html> <html> <body> "
htmlfile = htmlfile + " </body> </html>"
nbrParagraphs = 3000
value = 1
while (value <= nbrParagraphs):
    htmlfile = htmlfile + "<h1> "
    htmlfile = htmlfile + str(value)
    htmlfile = htmlfile + " </h1>"
    htmlfile = htmlfile + "<p>Bacon ipsum dolor amet pancetta cow capicola, ham venison turducken buffalo. Picanha sausage meatloaf hamburger chicken, ball tip biltong tail tri-tip shank salami leberkas shoulder corned beef pork belly. Turkey meatloaf chislic strip steak, corned beef chicken salami alcatra turducken swine. Shankle biltong kevin short ribs.Does your lorem ipsum text long for something a little meatier? Give our generator a try… it’s tasty!</p>"
    value += 1
htmlfile = htmlfile + "<h1> FIM DO HTML </h1>"

resBody = htmlfile;
# content_len = len(resBody)
content_len = 1364072
print(str(content_len), file=sys.stderr)

out = "Status: 200 OK\n"
out += "Server: webserv\n"
out += "Connection: keep-alive\n"
# out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Length: " + str(content_len) + "\n"
out += "Content-Type: " + "text/html" + "\n"
out += "\n"
out += htmlfile

print(out)
