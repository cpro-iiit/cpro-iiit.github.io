CC = gcc
CFLAGS = -Wall -I./include -g
SRCS = src/main.c src/network.c src/friendships.c
OBJS = $(SRCS:.c=.o)
TARGET = mini_social_network

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
