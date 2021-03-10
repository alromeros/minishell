NAME	= minishell

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

SRC		=	main.c \
			split.c \
			get_next_line.c \
			minishell_utils.c \
			ft_second_utils.c \
			malloc_words.c \
			fill_words.c \
			frees.c \
			list_add_elements.c \
			list_pop_elements.c \
			list_utils.c \
			num_words.c \
			create_tree.c \
			execute_tree.c \
			built_cd.c \
			init_main.c \
			built_echo_env.c \
			built_echo_print.c \
			built_echo.c \
			built_search_word_env.c \
			built_pwd.c \
			built_export.c \
			built_env.c \
			built_unset.c \
			built_command_path.c \
			execute_with_flags.c \
			signals.c \
			built_command_utils.c \
			create_tree_inserts.c \
			create_tree_nodes.c \
			create_tree_selector.c \
			execute_tree_create_command.c \
			execute_with_flags_second.c \
			execute_redirs.c \
			built_exit.c \
			built_var_env.c \
			built_var_env_2.c \
			built_echo_bar.c
		  
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -ggdb3

all: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -lm -o $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
.PHONY:		all clean fclean re
