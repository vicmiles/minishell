
NAME		:= minishell

LIBFT		:= libft.a
LIBFT_PATH	:= libft

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra -Iinclude -I$(READLINE_PATH)/include

LDFLAGS := -L$(READLINE_PATH)/lib -lreadline -lhistory


BUILTINS	:=	built_in_func/ft_pwd.c \
				built_in_func/ft_echo.c \
				built_in_func/ft_env.c \
				built_in_func/ft_env_utils.c \
				built_in_func/ft_cd.c \
				built_in_func/ft_export.c \
				built_in_func/ft_unset.c \
				built_in_func/ft_exit.c 

CLEANING	:=	cleaning/ft_clean_ms.c

EXEC		:=	executor/exec_builtins.c \
				executor/exec_redir.c \
				executor/exec_utils.c \
				executor/exec_simple_cmd.c \
				executor/exec.c \
				executor/exec_path.c \
				executor/init_tree.c \
				executor/check_exec.c \
				executor/msg_error.c
				

EXPANDER	:=	expander/ft_star.c \
				expander/ft_clean_empty_str.c \
				expander/ft_expand_utils.c \
				expander/ft_expand.c \
				expander/ft_expand_split.c \
				expander/ft_file_expander_utils.c \
				expander/ft_file_expander.c \
				expander/ft_unquote.c \
				expander/ft_expand_heredoc.c

PARSING		:=	parser/parser_clean.c \
				parser/parser_error.c \
				parser/parser_node_utils.c \
				parser/parser_node.c \
				parser/parser_utils.c \
				parser/parser.c

LEXER		:=	lexer/lexer_appender.c \
				lexer/lexer_handlers.c \
				lexer/lexer_list.c \
				lexer/lexer_utils.c \
				lexer/lexer.c

SRCS		:=	$(BUILTINS)\
				$(CLEANING)\
				$(EXEC)\
				$(EXPANDER)\
				$(PARSING)\
				$(LEXER)\
				main.c main_signals.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	/goinfre/homebrew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline


clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re