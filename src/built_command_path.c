/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:51:19 by alromero          #+#    #+#             */
/*   Updated: 2021/02/05 15:27:59 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_path(t_vars *va, char *command)
{
	struct stat status;

	while (va->split[va->i])
	{
		va->to_compare = strjoin_with_c(va->split[va->i], command, '/');
		if (stat(va->to_compare, &status) == 0)
		{
			free_default(va->split, va->num_words);
			return (va->to_compare);
		}
		free(va->to_compare);
		va->i++;
	}
	free_default(va->split, va->num_words);
	return (NULL);
}

char	*search_cmd_path(t_list *env, char *command)
{
	t_vars		va;
	struct stat status;

	va.to_search = search_in_list(env, "PATH", 0);
	if (va.to_search >= 0)
	{
		va.content_path =
		create_word_since(get_element(env, va.to_search), '=');
		va.split = second_split(&va, va.content_path, ':');
		free(va.content_path);
		va.i = 0;
		if (stat(command, &status) == 0)
		{
			free_default(va.split, va.num_words);
			return (va.to_compare = ft_strdup(command));
		}
		else
			return (command_path(&va, command));
		return (NULL);
	}
	else
		return (NULL);
}

char	**create_char_with_list(t_list *command)
{
	char	**words;
	t_node	*iterator;
	int		i;

	words = (char**)malloc(sizeof(char*) * command->size + 1);
	iterator = command->first;
	i = 0;
	while (iterator)
	{
		words[i] = ft_strdup(iterator->element);
		i++;
		iterator = iterator->next;
	}
	words[i] = NULL;
	return (words);
}

void	search_command(t_main *main, t_list *command)
{
	char	*path;
	pid_t	pid;
	char	**cmd_words;

	path = search_cmd_path(main->env, command->first->element);
	if (!path)
		main->status_pid =
		(error_word_not_found(command->first->element) * 256);
	else
	{
		cmd_words = create_char_with_list(command);
		pid = fork();
		if (pid == 0)
			execve(path, cmd_words, main->second_env);
		if (pid == 0)
			exit(EXIT_SUCCESS);
		else if (pid > 0)
			waitpid(pid, &main->status_pid, 0);
		free_default(cmd_words, command->size + 1);
		free(path);
	}
}
