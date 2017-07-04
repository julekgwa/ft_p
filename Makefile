SERVER = server
CLIENT = client
LIBFLAG = -Wall -Wextra -Werror

all: client server

client:
	@gcc -o $(CLIENT) client.c

server:
	@gcc -o $(SERVER) server.c

clean: clean
		@/bin/rm -f $(SERVER)
		@/bin/rm -f $(CLIENT)
		@echo "\x1B[32mCleaned up compiled files.\x1B[0m"

re: clean	all
