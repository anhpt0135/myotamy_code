PREFIX?=/usr/local ==> ?= de noi rang neu PREFIX chua duoc cai dat truoc do \
thi no se duoc cai dat luc nay

SOURCE=$(wildcard src/**/*.c src/*.c) ==> 
OBJECTS=$(patsubst %.c,%.o,$(SOURCE)) ==>chuyen tat ca file .c thanh .o \
o trong thu muc $(SOURCE)

#The target build
all: $(TARGET) $(SO_TARGET) tests ==> 