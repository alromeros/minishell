/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:14:35 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 19:20:03 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_word_not_found(char *s)
{
	write(1, "minishell: ", 11);
	write(1, s, ft_strlen(s));
	write(1, ": command not found\n", 20);
	return (127);
}

int		compare_command(char *command, t_main *main)
{
	int i;

	i = 0;
	if (command[i] == '$')
		return (7);
	while (main->builtin_str[i] != NULL)
	{
		if (ft_strcmp(command, main->builtin_str[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	execute_builtins(t_main *main, t_list *cmd, int select_word,
t_arbol *tree)
{
	if (select_word == 0)
		cd(main, cmd);
	else if (select_word == 1)
		echo(main, cmd);
	else if (select_word == 2)
		built_exit(main, tree);
	else if (select_word == 3)
		pwd();
	else if (select_word == 4)
		unset(main, cmd);
	else if (select_word == 5)
	{
		if (tree->izq)
			more_cmd_after_env(main, cmd);
		else
			env(main->env);
	}
	else if (select_word == 6)
		export(main, cmd);
	else if (select_word == 7)
		var_env(main, cmd);
}

void	execute_no_flags(t_arbol *tree, t_tree_vars *vars, t_main *main)
{
	if (tree->type == 1)
	{
		execute_no_flags(tree->izq, vars, main);
		execute_no_flags(tree->dcho, vars, main);
	}
	else if (tree->type == 3)
	{
		vars->command = create_command_list(tree, vars);
		vars->select_word = compare_command(tree->valor, main);
		if (vars->select_word >= 0)
			execute_builtins(main, vars->command, vars->select_word, tree);
		else
			search_command(main, vars->command);
		destructor_list(vars->command);
	}
}

void	execute_tree(t_tree_vars *vars, t_main *main)
{
	if (vars->flag == 0)
		execute_no_flags(vars->arbol, vars, main);
	else if (vars->flag == 1)
		execute_with_flags(vars->arbol, vars, main);
}
