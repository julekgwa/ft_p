# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/14 07:28:36 by julekgwa          #+#    #+#              #
#    Updated: 2017/07/15 23:06:23 by julekgwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ./src/ft_memset.c ./src/ft_bzero.c ./src/ft_memcpy.c ./src/ft_memccpy.c ./src/ft_memmove.c \
      ./src/ft_memchr.c ./src/ft_memcmp.c ./src/ft_strlen.c ./src/ft_strnstr.c \
      ./src/ft_strdup.c ./src/ft_strcpy.c ./src/ft_strncpy.c ./src/ft_strcat.c ./src/ft_strncat.c \
      ./src/ft_strlcat.c ./src/ft_strchr.c ./src/ft_strrchr.c ./src/ft_strstr.c ./src/ft_strcmp.c \
      ./src/ft_strncmp.c ./src/ft_atoi.c ./src/ft_isalpha.c ./src/ft_isdigit.c ./src/ft_isalnum.c \
      ./src/ft_isprint.c ./src/ft_isascii.c ./src/ft_toupper.c ./src/ft_tolower.c \
      ./src/ft_memalloc.c ./src/ft_memdel.c ./src/ft_strnew.c ./src/ft_strdel.c ./src/ft_strclr.c \
      ./src/ft_striter.c ./src/ft_striteri.c ./src/ft_strmap.c ./src/ft_strmapi.c \
      ./src/ft_strequ.c ./src/ft_strnequ.c ./src/ft_strsub.c ./src/ft_strjoin.c ./src/ft_strtrim.c \
      ./src/ft_strsplit.c ./src/ft_itoa.c ./src/ft_putchar.c ./src/ft_putstr.c ./src/ft_putendl.c \
      ./src/ft_putnbr.c ./src/ft_putchar_fd.c ./src/ft_putstr_fd.c ./src/ft_putendl_fd.c \
      ./src/ft_putnbr_fd.c ./src/ft_lstnew.c ./src/ft_lstdelone.c ./src/ft_lstdel.c \
      ./src/ft_lstadd.c ./src/ft_lstiter.c ./src/ft_lstmap.c ./src/ft_check_flags.c \
      ./src/ft_flags.c ./src/ft_handle_d_i.c ./src/ft_handle_o_h.c ./src/ft_printf.c \
      ./src/ft_neg_to_pos.c ./src/ft_str_contains.c ./src/ft_strhex_lower.c ./src/ft_base.c \
      ./src/ft_putnstr.c ./src/ft_num_digits.c ./src/ft_manage_c.c ./src/ft_find_width.c \
      ./src/ft_handle_s.c ./src/ft_strhex.c ./src/ft_putwchar_t.c ./src/ft_handle_prec.c \
      ./src/ft_manage_width.c ./src/ft_realloc.c ./src/get_next_line.c ./src/ft_getchar.c \
      ./src/ft_lstsize.c ./src/util.c ./src/commands/ft_commands.c ./src/utils/ft_ctrl_c_signal_handler.c \
      ./src/commands/ft_cd.c ./src/commands/ft_echo.c ./src/env/ft_env.c \
      ./src/utils/ft_utils.c ./src/exec/ft_get_data.c ./src/history/ft_history.c \
      ./src/utils/ft_more_utils.c ./src/keyboard/ft_ctrl_keyboard.c ./src/signals/ft_signals.c\
      ./src/keyboard/ft_ctrl_terminal.c ./src/keyboard/ft_term_utils.c ./src/pipe/ft_manage_pipes.c \
      ./src/buffer/ft_manage_buff.c ./src/history/ft_hist_utils.c ./src/memory/ft_free.c \
      ./src/utils/ft_cmd_utils.c ./src/env/ft_env_utils.c ./src/redirection/ft_redirection.c \
      ./src/redirection/ft_redirection_utils.c ./src/redirection/ft_here_doc.c \
      ./src/parenthesis/ft_parenthesis.c ./src/parenthesis/ft_parenthesis_utils.c \
      ./src/redirection/ft_here_doc_utils.c ./src/env/ft_export.c ./src/logical/ft_logical_op.c \
      ./src/history/ft_bck_i_search.c ./src/history/ft_manage_hist.c ./src/copy/ft_cut.c \
      ./src/auto/ft_auto_search.c ./src/auto/ft_auto_utils.c ./src/auto/ft_auto_misc.c \
      ./src/hash_table/ft_hash_table.c ./src/hash_table/ft_hash_table_utils.c \
      ./src/exec/ft_execute.c ./src/substitution/ft_sub.c ./src/auto/ft_format.c \
      ./src/pipe/ft_pipes_utils.c ./src/servers/file_io.c ./src/servers/server_utils.c
OBJECT = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
      ft_memchr.o ft_memcmp.o ft_strlen.o ft_strnstr.o \
      ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o \
      ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strcmp.o \
      ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o ft_isalnum.o \
      ft_isprint.o ft_isascii.o ft_toupper.o ft_tolower.o \
      ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o \
      ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o \
      ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o \
      ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o \
      ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o \
      ft_putnbr_fd.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o \
      ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_check_flags.o \
      ft_flags.o ft_handle_d_i.o ft_handle_o_h.o ft_printf.o \
      ft_neg_to_pos.o ft_str_contains.o ft_strhex_lower.o ft_base.o \
      ft_putnstr.o ft_num_digits.o ft_manage_c.o ft_find_width.o \
      ft_handle_s.o ft_strhex.o ft_putwchar_t.o ft_handle_prec.o \
      ft_manage_width.o ft_realloc.o get_next_line.o ft_getchar.o ft_lstsize.o \
      util.o ft_commands.o ft_ctrl_c_signal_handler.o ft_cd.o ft_echo.o \
      ft_env.o ft_utils.o ft_get_data.o ft_more_utils.o ft_ctrl_terminal.o \
      ft_term_utils.o ft_ctrl_keyboard.o ft_manage_pipes.o ft_manage_buff.o \
      ft_history.o ft_signals.o ft_hist_utils.o ft_free.o ft_cmd_utils.o ft_env_utils.o \
      ft_redirection.o ft_redirection_utils.o ft_here_doc.o ft_parenthesis.o \
      ft_parenthesis_utils.o ft_here_doc_utils.o ft_export.o ft_logical_op.o \
      ft_bck_i_search.o ft_manage_hist.o ft_cut.o ft_auto_search.o ft_auto_utils.o \
      ft_auto_misc.o ft_hash_table.o ft_hash_table_utils.o ft_execute.o ft_sub.o \
      ft_format.o ft_pipes_utils.o file_io.o server_utils.o
FLAGS = -Wall -Wextra -Werror
OPTIONS = -c -I ./includes/

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(OPTIONS) $(SRC)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)
	@echo "\033[32mBuilt library.\033[0m"

clean:
	@/bin/rm -f $(OBJECT)
	@echo "\033[32mCleaned up object files.\033[0m"

fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[32mCleaned up compiled files.\033[0m"

re: fclean	all
