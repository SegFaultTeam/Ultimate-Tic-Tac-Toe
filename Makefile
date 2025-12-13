CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

TARGET  = program
SRC     = main.c

.PHONY: all clean

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
