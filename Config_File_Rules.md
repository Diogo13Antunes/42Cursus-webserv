# Config File Rules

## Table of Content

- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Config Elements](#config-elements)

### Introduction

This document provides essential information about our configuration files, which is based on YAML. The config file plays a crucial role in customizing and configuring various aspects of WebServ. In this guide, you will learn about its purpose, how to work with it, and any special instructions to ensure smooth configuration management.

### Getting Started

1. Create the config file:
```bash
touch directory/of/your/choice/config_file_name.conf
```

2. Inside the config file create a server:
```txt
server:
```

3. Add **listen**:
```txt
server:
  listen: [domain/localhost]:[port]
```

4. Add **server_name**:
```txt
server:
  server_name: "[your_server_name]"
```

5. Add **master_root**:
```txt
server:
  master_root: "[main/location/of/your/server/]"
```

6. Add **locations**:
```txt
server:
  location:
    "/":
      root: "your/location/root/"
      index: "index.html"
```

### Config Elements

The config file has some elements with specific indentations levels
(1 identation level = 2 spaces):

<details>
<summary>server</summary>
The server is the only element without identation  
Identation Level: 0
</details>

<details>
<summary>listen</summary>
Specifies the IP address and port the server should listen on (127.0.0.1:8080 in this case)
Identation Level: 1
</details>

<details>
<summary>server_name</summary>
Defines the server name or hostname.
Identation Level: 1
</details>

<details>
<summary>client_max_body_size</summary>
Specifies the maximum allowed request body size in bytes.
Identation Level: 1
</details>

<details>
<summary>master_root</summary>
Sets the root directory for the server.
Identation Level: 1
</details>

<details>
<summary>error_pages</summary>
Configures custom error pages for specific HTTP error codes (404 in this case).
Identation Level: 1
</details>

<details>
<summary>location</summary>
This section defines how requests to different URL paths should be handled.
Identation Level: 1
</details>

<details>
<summary>mime_types</summary>
This section associates file extensions with their corresponding MIME types, which helps the server send the correct content type headers in responses.
Identation Level: 1
</details>

### Example

```conf
server:
  listen: "127.0.0.1:8080"
  server_name: "multiple_tests"
  client_max_body_size: 100000000
  master_root: "./www/multiple_tests/"
  error_pages:
    "404": "./www/multiple_tests/error_pages/404.html"
  location:
    "/":
      root: "./www/multiple_tests/"
      index: "index.html"
    "/user":
      alias: "./www/multiple_tests/"
      index: "user.html"
    "/redir1":
      redirect:
        "301": "/user/"
    "/redir2":
      redirect:
        "302": "/user/"
    "/Folder1":
      autoindex: on
    "/Folder1/Folder2":
      autoindex: off
    "/Folder1/Folder2/Folder3/Folder4":
      autoindex: on
    "/uploads":
      alias: "./www/multiple_tests/"
      index: "uploads.html"
    "*.py": # Python CGI Scripts
      cgi: "./cgi-bin/"
      upload_store: "./www/multiple_tests/uploads/"
      allowed: ["GET", "POST"]
    "*.js": # JavaScript CGI Scripts
      cgi: "./cgi-bin/"
      allowed: ["GET", "POST"]
    "/directory":
      alias: "./www/multiple_tests/YoupiBanane/"
      index: "youpi.bad_extension"
    "*.bla":
      cgi: "./cgi-bin/ubuntu_cgi_tester"
      upload_store: "./www/multiple_tests/"
      client_max_body_size: 100000000
      allowed: ["POST"]
  mime_types:
    "js": "text/javascript"
    "css": "text/css"
    "html": "text/html"
    "ico": "image/x-icon"
```
