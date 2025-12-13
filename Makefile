CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

TARGET  = program
SRC     = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)
	@echo "Run ./program"

.PHONY: force

$(TARGET): force $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

force:

clean:
	rm -f $(TARGET)
