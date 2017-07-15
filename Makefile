SERVER = server

CLIENT = client

LIBFLAG = -Wall -Wextra -Werror

OPTIONS = -c -I includes/ -I libft/includes/

SRCSERVER = server.c read_file.c

SRCCLIENT = client.c read_file.c client_utils.c

OBJSERVER = $(SRCSERVER:.c=.o)

OBJCLIENT = $(SRCCLIENT:.c=.o)

all: lib client server
	@whoami > author

client:
	@gcc $(LIBFLAG) $(OPTIONS) $(SRCCLIENT)
	@gcc $(LIBFLAG) -o $(CLIENT) $(OBJCLIENT) -L libft/ -lft -ltermcap
	@echo "\x1B[32mCompiled client files.\x1B[0m"

server:
	@gcc $(LIBFLAG) $(OPTIONS) $(SRCSERVER)
	@gcc $(LIBFLAG) -o $(SERVER) $(OBJSERVER) -L libft/ -lft -ltermcap
	@echo "\x1B[32mCompiled server files.\x1B[0m"

lib:
	@make -C libft/

clean:
	@make -C libft/ clean
	@rm -rf $(OBJSERVER) $(OBJCLIENT)
	@echo "\x1B[32mCleaned up compiled files.\x1B[0m"
fclean: clean
	@make -C libft/ fclean
	@/bin/rm -f $(SERVER)
	@/bin/rm -f $(CLIENT)

re: fclean	all
