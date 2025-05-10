CC = gcc
CFLAGS = -Wall -Wextra -O2 

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=%.o)

TARGET = ft_ssl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lm

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: 
	gcc -I./src -o test ./tests/test_md5.c ./src/md5.c -lcunit
	./test

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
run:
	./ping www.google.com
