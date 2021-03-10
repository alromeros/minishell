/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:32:27 by alromero          #+#    #+#             */
/*   Updated: 2021/02/05 14:54:33 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

typedef	struct	s_node
{
	char			*element;
	struct s_node	*next;
}				t_node;

typedef	struct	s_list
{
	t_node	*first;
	int		size;
}				t_list;

typedef	struct	s_node_d
{
	char			**element;
	struct s_node_d	*next;
}				t_node_d;

typedef	struct	s_list_d
{
	t_node_d	*first;
	int			size;
}				t_list_d;

typedef	struct	s_main
{
	int		i;
	int		i_2;
	int		j;
	int		size_env;
	int		size_export;
	int		num_words;
	int		num_words_split;
	int		is_redir;
	int		is_pipe;
	int		is_a_flag;
	int		is_env_count;
	int		*is_env;
	int		f_doble;
	int		f_simp;
	int		equal_count;
	int		flag_error;
	int		flag;
	int		flag_redir;
	int		flag_semi;
	int		flag_quote;
	int		flag_signal;
	int		flag_semi2;
	int		flag_export;
	int		flag_colon;
	int		flag_n;
	int		flag_bar;
	int		flag_dup;
	int		status_pid;
	t_list	*env;
	t_list	*cmd;
	t_list	*export;
	t_list	*words_list;
	t_list	*list_copy;
	t_list	*flag_list;
	char	**builtin_str;
	char	**split;
	char	**words;
	char	**second_env;
	char	*line;
	pid_t	pid;
}				t_main;

typedef	struct	s_vars
{
	int		i;
	int		j;
	int		k;
	int		to_search;
	int		num_words;
	char	*content_path;
	char	*to_compare;
	char	*first_part;
	char	*last_part;
	char	**split;
	int		cont;
	int		flag;
	int		flag_dup;
	t_list	*cmd_;
	t_node	*iterator;
}				t_vars;

typedef	struct	s_nodo
{
	char			*valor;
	int				type;
	struct s_nodo	*izq;
	struct s_nodo	*dcho;
	struct s_nodo	*padre;
}				t_nodo;

typedef	t_nodo	t_arbol;

typedef	struct	s_flags
{
	int		*pipe_n;
	int		status;
	int		p_write;
	int		p_read;
	int		redir;
	int		redir_before;
	int		conductor;
	pid_t	pid_right;
	pid_t	pid_left;
	pid_t	pid;
	t_list	*cmd;
}				t_flags;

typedef	struct	s_tree_vars
{
	t_nodo	*arbol;
	t_nodo	*temp;
	t_nodo	*nuevo;
	t_list	*command;
	t_node	*iterator;
	char	**str;
	int		i;
	int		flag_word;
	int		flag;
	int		flag_dup;
	int		f_s;
	int		flag_redir;
	int		f_c;
	int		type;
	int		select_word;
}				t_tree_vars;

void			get_env_and_export(t_main *main, char **environ);
void			size_env(t_main *main, char **environ);
void			init_builtins_str(t_main *main);
size_t			ft_strlen(const char *s);
char			*ft_strdup(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *str, int c);
int				get_next_line(char **line);
char			*ft_strjoin_new(char const *s1, char const *s2);
int				ft_isspace(char c);
int				notflags(char c);
t_list			*new_list(void);
t_node			*new_node(char *s);
void			destructor_node(t_node *node);
void			destructor_list(t_list *list);
void			pop_front(t_list *list);
void			pop_back(t_list *list);
void			pop_n_element(t_list *list, int n);
void			push_front(t_list *list, char *s);
void			push_back(t_list *list, char *s);
void			push_after_n(t_list *list, char *s, int n);
char			*get_element(t_list *list, int n);
void			modify_element(t_list *list, char *s, int n);
void			split(t_main *main);
void			free_default(char **s, int n);
void			malloc_words(t_main *main);
void			num_words(t_main *main);
void			fill_words(t_main *main);
void			free_all_line(t_main *main);
int				contains_flags(t_list *list);
void			execute(t_main *main);
void			cd(t_main *main, t_list *list);
void			is_env(t_main *main);
int				check_word_env(t_main *main, char *s, int pos);
int				check_word(char *s);
char			*piece_of_word(char *s, char c);
void			print_until_c(t_vars *vars, char *s, char c);
void			print_since_c(char *s, char c);
int				search_word_in_env(t_main *main, char *s);
char			*create_word(t_vars *vars, char *s);
void			echo(t_main *main, t_list *list);
void			print_final_word(t_main *main, t_vars *vars, char *s);
void			pwd();
void			export(t_main *main, t_list *list);
int				compare_element_c(char *s, char c);
int				check_first_letter(char *s, int flag);
void			search_words_list_env(t_main *main,
t_list *list_to_search, t_list *words_list);
int				search_in_list(t_list *list, char *s, int i);
void			env(t_list *list);
void			unset(t_main *main, t_list *list);
t_list			*copy_list(t_list *list);
void			execute_flags(t_main *main);
void			search_command(t_main *main, t_list *command);
char			*create_word_since(char *s, char c);
int				count_words(char *s, char c);
char			*malloc_word(char *s, char c);
int				error_word_not_found(char *s);
char			*search_cmd_path(t_list *env, char *command);
int				compare_words(char **s, char *to_compare);
void			execute_builtins(t_main *main, t_list *cmd, int select_word,
t_arbol *tree);
void			execute_builtins_flags(t_main *main, int select_word);
void			free_pipes(int **pipes, int n_pipes);
int				create_tree(t_nodo **arbol, t_tree_vars *vars, t_list *list);
void			print_tree(t_nodo *nodo, int level, int side);
void			execute_tree(t_tree_vars *vars, t_main *main);
void			destruir_nodo(t_nodo *nodo);
void			execute_with_flags(t_arbol *tree, t_tree_vars *vars,
t_main *main);
void			execute_pipe(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags flags);
void			execute_with_flags(t_arbol *tree, t_tree_vars *vars,
t_main *main);
t_list			*create_command_list(t_arbol *tree, t_tree_vars *vars);
t_list			*create_command(t_arbol *tree, t_tree_vars *vars, t_list *new);
int				compare_command(char *command, t_main *main);
void			execute_no_flags(t_arbol *tree, t_tree_vars *vars,
t_main *main);
void			redir(t_arbol *tree, t_main *main, t_flags *flags);
void			redir_concat(t_arbol *tree, t_main *main, t_flags *flags);
void			signals(int signal);
int				*gnl_works(void);
char			*strjoin_with_c(char *s1, char *s2, char c);
char			**second_split(t_vars *va, char *s, char c);
void			print_echo(char *s);
void			insert(t_nodo *arbol, t_nodo *nuevo, int n, int type);
void			insert_right_left(t_nodo *arbol, t_nodo *nuevo,
int first_type, int second_type);
void			insert_redir(t_nodo *arbol, t_nodo *nuevo);
void			insert_right(t_nodo *arbol, t_nodo *nuevo);
t_nodo			*crear_nodo(t_nodo *padre, char *s, int type);
void			destruir_nodo(t_nodo *nodo);
int				errors_tree(char *s);
void			its_a_word(t_nodo **arbol, t_tree_vars *vars);
int				its_a_redir_input(t_nodo **arbol, t_tree_vars *vars);
int				its_a_semicolon(t_nodo **arbol, t_tree_vars *vars);
int				its_a_pipe(t_nodo **arbol, t_tree_vars *vars);
void			init_pipe_and_pid(t_flags *flags);
void			redir_out(t_arbol *tree, t_main *main, t_flags *flags);
void			redir_concat(t_arbol *tree, t_main *main, t_flags *flags);
void			redir(t_arbol *tree, t_main *main, t_flags *flags);
void			execute_flag_command(t_arbol *tree, t_main *main,
t_tree_vars *vars, t_flags *flags);
void			deleting_elements(t_list *list, t_node *previous_position,
t_node *pop, int n);
void			ft_signal_c1(int sign);
void			ft_signal_quit(int sign);
void			exec_cmd_redir(t_arbol *tree, t_main *main, t_tree_vars *vars,
t_flags *flags);
int				is_last_redir(t_arbol *tree);
void			select_redir(t_arbol *tree, t_main *main, t_flags *flags);
int				check_words(t_main *main);
void			built_exit(t_main *main, t_arbol *tree);
char			*get_oldpwd(t_main *main, char *s);
int				var_env(t_main *main, t_list *cmd);
void			execute_builtins_2(t_main *main, t_list *cmd, int select_word);
int				is_a_directory(char *path);
char			*search_cmd_path_2(t_list *env, char *command);
char			*command_path(t_vars *va, char *command);
int				check_comillas(t_main *main, int c, int c2);
void			more_cmd_after_env(t_main *main, t_list *cmd);
void			search_command_2(t_main *main, char **cmd);
int				is_bar(t_main *main, char *s);
void			redir_without_inputs(t_arbol *tree);
void			execute_words(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags flags);
void			create_word_pid(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags flags);
char			**create_char_with_list(t_list *command);
#endif
