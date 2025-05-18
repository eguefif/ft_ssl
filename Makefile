CC = gcc
CFLAGS = -Wall -Wextra -O2 

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=%.o)
SRCS_NO_MAIN := ./src/md5.c

TARGET = ft_ssl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lm

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(SRCS) ./tests/test_md5.c
	gcc -I./src -o test ./tests/test_md5.c $(SRCS_NO_MAIN) -lcunit -lm
	./test

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
run:
	./ping www.google.com
