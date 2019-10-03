##2 VARIABLE:
#! /bin/bash
echo "hello world!"

echo $BASH
echo $BASH_VERSION
echo $HOME
echo $PWD

name=TuanAnh

echo "the name is: " $name
echo the name is $name

##3 READ USER INPUT:

echo "Enter name:"
read name1 name2 name3
echo "$name1 $name2 $name3"

#read -p allow to read the input on the same line
#read -s allow to hide the input on the screen 
read -p 'username:' user_var
read -sp 'password:' pass_var

##4 PASS ARGUMENT TO A BASH-SCRIPT

echo $0 $1 $2 $3

#pass argument to an array
#${args[0] = $1}

args=("$@")

echo ${args[0]} ${args[1]} ${args[2]}
echo ${args[@]}
echo $@
#argc:
echo $#



NOTE: http header:

#define HTTP_MSG_RESPONSE_FORMAT    "HTTP/1.1 %d %s\r\n" \
                                "Content-type: %s\r\n" \
                                "Connection: Keep-Alive\r\n"\
                                "Content-Length: %d\r\n\r\n" /**< Define HTTP message respone format. */
#define HTTP_FILE_RESPONSE_FORMAT    "HTTP/1.1 %d %s\r\n"\
                                "Content-type: %s\r\n"\
                                STD_HEADER \
                                "Content-Disposition: filename=\"%s\"\r\n" \
                                "Content-Length: %d\r\n\r\n" /**< Define HTTP file respone format. */