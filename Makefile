
BIN = producer_consumer

CFLAGS = -Wall -Wextra -g -pthread

SRC = src/main.c \
      src/queue.c \
      src/producer.c \
      src/consumer.c

all: $(BIN)

clean:
	$(RM) $(BIN)

$(BIN): $(SRC)
	$(CC) -o $@ $(CFLAGS) $^
