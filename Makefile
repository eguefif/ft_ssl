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

test_md5: $(SRCS) ./tests/test_md5.c
	gcc -I./src -o test ./tests/test_md5.c ./src/md5.c -lcunit -lm
	./test

test_sha256: $(SRCS) ./tests/test_sha256.c
	gcc -I./src -o test ./tests/test_sha256.c ./src/sha256.c -lcunit -lm
	./test

clean:
	rm -f $(OBJS)

.PHONY: all clean
run:
	./ping www.google.com
