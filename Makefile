CC = gcc
CFLAGS = -Wall -pthread
TARGET = tcp_echo_server
PORT = 2345
FLAGS = -v

SRCS = main.c server.c client_handler.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) -p $(PORT) $(FLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
