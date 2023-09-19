NAME = minishell

SRC = main.c \
	exec.c \
	cmd_list.c \
	parse_cmd.c \
	check_builtins.c \
	builtin.c \
	ft_cd.c \
	ft_export.c \
	ft_exit.c \
	utils.c \
	init.c \
	ft_split.c \
	ctrl.c \
	check_var.c \
	var_utils.c \
	has_var.c \
	env.c \
	dollar.c \
	dollar_utils.c \
	free.c \
	ft_atoi.c \
	ft_len.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_itoa.c \
	builtin_error.c \
	exec_utils.c \
	exec_box.c \
	free_cmd.c \
	mini.c \
	redirect.c \
	ft_strjoin.c \
	error.c \
	parse_utils.c \
	handle_input_delimiter.c \
	parse_command.c \
	parse_identifier.c \
	handle_redirect.c \
	close_token.c \
	handle_output_file.c \
	handle_input_file.c \
	handle_quote.c \
	remove_quotes.c \
	handle_plus.c

INC_HEADER = includes

DIR_S = srcs

SRCS = $(addprefix ${DIR_S}/, ${SRC})

OBJS = $(SRCS:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

READLINE = -lreadline

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE) -I$(INC_HEADER)


all	: $(NAME)

bonus :  $(NAME_BONUS)

clean	:
			rm -rf $(OBJS) $(OBJS_BONUS)

fclean	: clean
			rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: re clean fclean all
