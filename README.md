# C socket HTTP GET request
C program to connect to google.com and get the page's html sending 'get http 1.0'.

Programed using [*Beej’s Guide to Network Programming*](https://beej.us/guide/bgnet/), which I highly recommend! 
## Compilation Process
```
> mkdir build
> cd build
> cmake ..
    -- The C compiler identification is AppleClang 16.0.0.16000026
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /usr/bin/cc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Configuring done (0.9s)
    -- Generating done (0.0s)
    -- Build files have been written to: /Users/wymac/Developer/c_socket_get_http/build

> make
    [ 50%] Building C object CMakeFiles/c_socket_get_http.dir/main.c.o
    [100%] Linking C executable c_socket_get_http
    [100%] Built target c_socket_get_http
```
## Run
```
> ./c_socket_get_http
        Start socket test.
        Socket address: http://www.google.com
                IP version: IPv4
                IP address: 172.217.30.4

        Sending request:
        GET / HTTP/1.0


        HTTP/1.0 200 OK
        Date: Wed, 03 Sep 2025 14:01:02 GMT
        Expires: -1
        [...]
```