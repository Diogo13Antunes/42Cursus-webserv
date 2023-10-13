#!/usr/bin/node

let output;
let html;
let msg = "Hello from JavaScript!";

html = "<!DOCTYPE html> <html> <body> <h1> " + msg + " </h1> </body> </html>";

output = "Status: 200 OK\n"
output += "Content-Type: text/html" + "\n"
output += "Content-Length: " + html.length + "\n"
output += "\n"
output += html

console.log(output);