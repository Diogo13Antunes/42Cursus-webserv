# WebServ
This project is an integral part of the 42 Lisboa curriculum and aims to develop an HTTP server for serving static files. The server is capable of hosting a fully static website, is compatible with HTTP/1.1, and supports the GET, POST, and DELETE methods. Additionally, it can execute CGI scripts in any language installed on the server host.


## Introduction

The WebServ project is a comprehensive web server development project to create a functional web server from scratch. The project aims to teach the following key concepts and skills:

1. **HTTP Protocol:** Learn about the HTTP protocol, its methods (GET, POST, etc.), and how it works to facilitate communication between clients (browsers) and servers.
    
2. **Server Architecture:** Design and implement the core architecture of a web server, including request handling, routing, and response generation.
    
3. **Socket Programming:** They gain hands-on experience in socket programming to establish network connections and manage incoming client requests.
    
4. **Concurrency:** The project likely includes lessons on handling multiple concurrent connections efficiently to ensure the server can serve multiple clients simultaneously.
    
5. **Security:** Security considerations are an integral part of the project, teaching students how to handle common security vulnerabilities and protect against them.
    
6. **File I/O:** Learn how to read and write files, which is essential for serving static web content like HTML, CSS, and JavaScript files.
    
7. **Dynamic Content:** The project may involve handling dynamic content generation, such as server-side scripting (e.g., PHP, Python, Ruby) or templating engines.
    
8. **Error Handling:** Proper error handling and status code responses are emphasized to create a robust server.
    
9. **Logging and Debugging:** Gain experience in logging and debugging techniques to troubleshoot issues effectively.
    
10. **Testing:** The project likely includes testing methodologies to ensure the server functions correctly under various scenarios.
    
11. **Performance Optimization:** Techniques for optimizing server performance may be covered, such as caching, load balancing, and resource management.
    
12. **Deployment:** Learn how to deploy their web server to a production environment, configure domain names, and manage server infrastructure.



## Configuration File
To define how your website will be served such as routes, methods, and other options you need to create a configuration file where you can specify all the necessary rules. The configuration file uses YAML syntax for easy readability and flexibility.

For a full list of configuration requirements, click [HERE](./Config_File_Rules.md).

## Installation / Usage
This project is designed to work on Linux.

### Clone repo:
```bash
git clone git@github.com:dspereira/42Cursus-webserv.git webserv && cd webserv
```
### Build:
```bash
make
```
### Usage
```markdown
./webserv path-to-your-config-file
```
Note: In the conf.d folder, you’ll find multiple example configuration files that you can use or customize as needed.


### HTTP Request Example

```
GET / HTTP/1.1
Host: localhost:8080
User-Agent: insomnia/2023.5.8
Accept: */*
```

### HTTP Response Example

```
HTTP/1.1 200 OK
Server: webserv/1.0
Date: Wed, 27 Sep 2023 21:28:10 GMT
Content-Type: text/html
Content-Length: 0
Connection: keep-alive
```
