/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:03:51 by alromero          #+#    #+#             */
/*   Updated: 2021/03/10 17:23:47 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

void	init_stats(t_main *main)
{
	signal(SIGINT, &signals);
	signal(SIGQUIT, &signals);
	main->num_words = 0;
	main->num_words_split = 0;
	main->is_redir = 0;
	main->is_pipe = 0;
	main->equal_count = 0;
	main->flag_quote = 0;
	main->f_doble = 0;
	main->f_simp = 0;
	main->flag_semi = 0;
	main->flag_colon = 0;
	main->flag_export = 0;
}

int		have_a_flag(t_node *iterator)
{
	while (iterator)
	{
		if ((ft_strcmp(iterator->element, ">") == 0)
		|| (ft_strcmp(iterator->element, ">>") == 0)
		|| (ft_strcmp(iterator->element, "<") == 0)
		|| (ft_strcmp(iterator->element, "|") == 0))
			return (1);
		else
			iterator = iterator->next;
	}
	return (0);
}

void	checking_signals(t_main *main)
{
	*gnl_works() = 0;
	if (!get_next_line(&main->line))
	{
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	*gnl_works() = 1;
	main->i = 0;
	while (main->line[main->i])
	{
		if (main->line[main->i] == 34)
			main->f_doble = check_comillas(main, 34, 39);
		else if (main->line[main->i] == 39)
			main->f_simp = check_comillas(main, 39, 34);
		if (main->line[main->i])
			main->i++;
	}
}

void	execute_minishell(t_main *main)
{
	t_tree_vars vars;

	main->flag = 0;
	write(1, "\x1b[35mminishell\\> \x1b[0m", 22);
	init_stats(main);
	checking_signals(main);
	if (main->line[0] == 0)
		main->flag = 1;
	if (main->flag == 0 && main->f_doble == 0 && main->f_simp == 0)
	{
		vars.arbol = NULL;
		malloc_words(main);
		fill_words(main);
		vars.iterator = main->words_list->first;
		vars.flag = have_a_flag(vars.iterator);
		vars.f_s = main->flag_colon;
		if (!create_tree(&vars.arbol, &vars, main->words_list)
		&& main->flag_semi == 0 && (check_words(main) == 0))
			execute_tree(&vars, main);
		free_all_line(main);
	}
	free(main->line);
}

int		main(int argc, char **argv, char **environ)
{
	t_main main;

	(void)argv;
	(void)argc;
	main.status_pid = 0;
	size_env(&main, environ);
	get_env_and_export(&main, environ);
	init_builtins_str(&main);
	while (1)
		execute_minishell(&main);
	free_default(main.second_env, main.size_env);
	return (0);
}
