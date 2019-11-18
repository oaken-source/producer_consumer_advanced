
BIN = producer_consumer

CFLAGS = -Wall -Wextra -g
LDADD = -lpthread

SRC = src/main.c \
      src/queue.c \
      src/producer.c \
      src/consumer.c

all: $(BIN)

clean:
	$(RM) $(BIN)

$(BIN): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDADD) $^
