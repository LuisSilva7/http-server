CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC = src/main.c src/server.c src/request.c src/response.c src/file_handler.c
OBJ = $(SRC:.c=.o)
EXEC = http_server

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)

