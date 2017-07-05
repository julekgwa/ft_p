SERVER = server

CLIENT = client

LIBFLAG = -Wall -Wextra -Werror

SRCSERVER = server.c

SRCCLIENT = client.c

OBJSERVER = $(SRCSERVER: .c=.o)

OBJCLIENT = $(SRCCLIENT: .c=.o)

all: client server
	@whoami > author

client:
	@gcc $(LIBFLAG) -c $(SRCCLIENT)
	@gcc $(LIBFLAG) -o $(CLIENT) $(OBJCLIENT)

server:
	@gcc $(LIBFLAG) -c $(SRCSERVER)
	@gcc $(LIBFLAG) -o $(SERVER) $(OBJSERVER)

clean:
	@rm -rf $(OBJSERVER) $(OBJCLIENT)
	@echo "\x1B[32mCleaned up compiled files.\x1B[0m"
fclean: clean
	@/bin/rm -f $(SERVER)
	@/bin/rm -f $(CLIENT)

re: clean	all
