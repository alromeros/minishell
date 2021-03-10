/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_var_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:04:51 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 17:45:29 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
    j = 0;
	while (s[i])
		i++;
	if (!(ret = (char *)malloc(sizeof(char) * i)) || !i)
        return NULL;
	i = 1;
	while (s[i])
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}

int		num_words_2(char *s)
{
	int		count;

	count = 0;
	while (*s)
	{
		while (*s && *s == 32)
			s++;
		if (*s && *s != 32)
		{
			count++;
			while (*s && *s != 32)
				s++;
		}
	}
	return (count);
}

void	split_cmd(char *all_cmd, int n_words, t_vars *vars)
{
	vars->split = (char **)malloc(sizeof(char *) * n_words + 1);
	while (all_cmd[vars->i])
	{
		while (all_cmd[vars->i] && all_cmd[vars->i] == 32)
			vars->i++;
		if (all_cmd[vars->i] && all_cmd[vars->i] != 32)
		{
			vars->k = 0;
			while (all_cmd[vars->i] && all_cmd[vars->i] != 32)
			{
				vars->k++;
				vars->i++;
			}
			vars->split[vars->j] = (char *)malloc(sizeof(char) * vars->k + 1);
			vars->i -= vars->k;
			vars->k = 0;
			while (all_cmd[vars->i] && all_cmd[vars->i] != 32)
				vars->split[vars->j][vars->k++] = all_cmd[vars->i++];
			vars->split[vars->j][vars->k] = '\0';
			push_back(vars->cmd_, vars->split[vars->j]);
			vars->j++;
		}
	}
	vars->split[vars->j] = NULL;
}

void	search_command_2(t_main *main, char **cmd)
{
	char	*path;
	pid_t	pid;

	path = search_cmd_path_2(main->env, cmd[0]);
	if (!path)
		main->status_pid =
		(error_word_not_found(cmd[0]) * 256);
	else
	{
		pid = fork();
		if (pid == 0)
			execve(path, cmd, main->second_env);
		if (pid == 0)
			exit(EXIT_SUCCESS);
		else if (pid > 0)
			waitpid(pid, &main->status_pid, 0);
		free(path);
	}
}

int		var_env(t_main *main, t_list *cmd)
{
	char	*s_without;
	char	*all_cmd;
	int		n_words;
	t_vars	vars_cmd;

	vars_cmd.i = 0;
	vars_cmd.j = 0;
	vars_cmd.cmd_ = new_list();
	s_without = get_string(cmd->first->element);
	all_cmd = get_oldpwd(main, s_without);
	if (all_cmd)
	{
		n_words = num_words_2(all_cmd);
		split_cmd(all_cmd, n_words, &vars_cmd);
		vars_cmd.to_search = compare_command(vars_cmd.split[0], main);
		if (vars_cmd.to_search >= 0)
			execute_builtins_2(main, vars_cmd.cmd_, vars_cmd.to_search);
		else
			search_command_2(main, vars_cmd.split);
		free(all_cmd);
		free_default(vars_cmd.split, n_words);
	}
	free(s_without);
	destructor_list(vars_cmd.cmd_);
	return (1);
}
