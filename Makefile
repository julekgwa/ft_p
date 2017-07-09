SERVER = server

CLIENT = client

LIBFLAG = -Wall -Wextra -Werror

OPTIONS = -c -I libft/includes/ -I includes/

SRCSERVER = server.c

SRCCLIENT = client.c

OBJSERVER = $(SRCSERVER:.c=.o)

OBJCLIENT = $(SRCCLIENT:.c=.o)

all: client server
	@whoami > author

client:
	@gcc $(LIBFLAG) $(OPTIONS) $(SRCCLIENT)
	@gcc $(LIBFLAG) -o $(CLIENT) $(OBJCLIENT) -L libft/ -lft
	@echo "\x1B[32mCompiled client files.\x1B[0m"

server:
	@gcc $(LIBFLAG) -c $(SRCSERVER)
	@gcc $(LIBFLAG) -o $(SERVER) $(OBJSERVER)
	@echo "\x1B[32mCompiled server files.\x1B[0m"

clean:
	@rm -rf $(OBJSERVER) $(OBJCLIENT)
	@echo "\x1B[32mCleaned up compiled files.\x1B[0m"
fclean: clean
	@/bin/rm -f $(SERVER)
	@/bin/rm -f $(CLIENT)

re: clean	all
