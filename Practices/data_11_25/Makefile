SRC=main.c heap_stack_allocation.c
CFLAGS=-Wall 
TARGET=output
CC=gcc

OBJ:= $(SRC: .c=.o)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -rf *.o $(TARGET)
