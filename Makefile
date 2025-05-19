CC = gcc
CFLAGS = -Wall -Wextra -O2 

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=%.o)

# Source variable for test
TEST_SHA256_SRC = ./tests/test_sha256.c ./src/sha256.c ./src/serialization.c
TEST_MD5_SRC = ./tests/test_md5.c ./src/md5.c ./src/serialization.c

TARGET = ft_ssl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lm

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test_md5: $(SRCS) $(TEST_MD5_SRC)
	gcc -I./src -o test $(TEST_MD5_SRC) -lcunit -lm
	./test

test_sha256: $(SRCS) $(TEST_SHA256_SRC)
	gcc -I./src -o test $(TEST_SHA256_SRC) -lcunit -lm
	./test

clean:
	rm -f $(OBJS)

.PHONY: all clean
run:
	./ping www.google.com
