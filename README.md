# WebServ
This project is part of the 42 Lisboa curriculum and involves developing an HTTP server in C++ from scratch to serve static files. The server is capable of hosting a fully static website, supports HTTP/1.1, and handles GET, POST, and DELETE methods. Additionally, it can execute CGI scripts in any language installed on the server host.

For more information about WebServ, see the project [subject](https://github.com/dspereira/42Cursus-webserv/blob/main/en.subject.pdf).

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
You can place your configuration file, website source files, and CGI scripts anywhere, but for better organization, we recommend using the following folders:

- `conf.d`:  Configuration files
- `www`:     Website source files
- `cgi-bin`: CGI scripts

In your configuration file, ensure you specify the correct paths for the chosen folders.

```markdown
./webserv path-to-your-config-file
```

## HTTP Request/Response Header Examples
### Request

```
GET / HTTP/1.1
Host: localhost:8080
User-Agent: insomnia/2023.5.8
Accept: */*
```

### Response

```
HTTP/1.1 200 OK
Server: webserv/1.0
Date: Wed, 27 Sep 2023 21:28:10 GMT
Content-Type: text/html
Content-Length: 0
Connection: keep-alive
```

## License
This project is licensed under the [MIT License](https://github.com/dspereira/42Cursus-webserv/blob/main/LICENSE).
