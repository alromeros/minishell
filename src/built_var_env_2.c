/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_var_env_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:58:09 by alromero          #+#    #+#             */
/*   Updated: 2021/02/22 11:59:37 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtins_2(t_main *main, t_list *cmd, int select_word)
{
	if (select_word == 0)
		cd(main, cmd);
	else if (select_word == 1)
		echo(main, cmd);
	else if (select_word == 2)
		exit(EXIT_SUCCESS);
	else if (select_word == 3)
		pwd();
	else if (select_word == 4)
		unset(main, cmd);
	else if (select_word == 5)
		env(main->env);
	else if (select_word == 6)
		export(main, cmd);
	else if (select_word == 7)
		var_env(main, cmd);
}

char	*search_cmd_path_2(t_list *env, char *command)
{
	t_vars	va;

	va.to_search = search_in_list(env, "PATH", 0);
	if (va.to_search >= 0)
	{
		va.content_path =
		create_word_since(get_element(env, va.to_search), '=');
		va.split = second_split(&va, va.content_path, ':');
		free(va.content_path);
		va.i = 0;
		return (command_path(&va, command));
	}
	else
		return (NULL);
}

void	more_cmd_after_env(t_main *main, t_list *cmd)
{
	t_node	*iter;
	int		i;
	int		j;
	char	**new_cmd;

	j = 0;
	iter = cmd->first->next;
	while (iter)
	{
		iter = iter->next;
		j++;
	}
	new_cmd = (char **)malloc(sizeof(char *) * j + 1);
	iter = cmd->first->next;
	i = 0;
	while (iter)
	{
		new_cmd[i] = ft_strdup(iter->element);
		iter = iter->next;
		i++;
	}
	new_cmd[i] = NULL;
	search_command_2(main, new_cmd);
	free_default(new_cmd, j);
}
