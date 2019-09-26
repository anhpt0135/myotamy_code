#1> how to write http client
##from url find the server, port, request
##using getaddrinfo() to get the server information and save into res variable
##from the res variable we create a socket 
##also from the res variable we make a connection
##finally, we write() to socket with a request, for example:

static const char *REQUEST = "GET / HTTP/1.1\r\n"
    "Host: "WEB_SERVER"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";


close the socket.
