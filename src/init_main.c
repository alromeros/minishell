/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:40:53 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 19:41:45 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	size_env(t_main *main, char **environ)
{
	main->size_env = 0;
	main->size_export = 0;
	while (environ[main->size_env] != NULL)
	{
		main->size_env++;
		main->size_export++;
	}
}

void	get_env_and_export(t_main *main, char **environ)
{
	int i;

	main->env = new_list();
	main->export = new_list();
	main->second_env = (char **)malloc(sizeof(char *) * main->size_env + 1);
	i = 0;
	while (i < main->size_env)
	{
		push_back(main->env, environ[i]);
		push_back(main->export, environ[i]);
		main->second_env[i] = ft_strdup(environ[i]);
		i++;
	}
}

void	init_builtins_str(t_main *main)
{
	main->builtin_str = (char**)malloc(sizeof(char*) * 8);
	main->builtin_str[0] = ft_strdup("cd");
	main->builtin_str[1] = ft_strdup("echo");
	main->builtin_str[2] = ft_strdup("exit");
	main->builtin_str[3] = ft_strdup("pwd");
	main->builtin_str[4] = ft_strdup("unset");
	main->builtin_str[5] = ft_strdup("env");
	main->builtin_str[6] = ft_strdup("export");
    main->builtin_str[7] = NULL;
}

int		check_comillas(t_main *main, int c, int c2)
{
	int flag;
	int flag2;

	flag2 = 0;
	flag = 1;
	main->i++;
	while (main->line[main->i])
	{
		if (main->line[main->i] == c && flag == 1)
			flag = 0;
		else if (main->line[main->i] == c && flag == 0)
			flag = 1;
		else if (main->line[main->i] == c2 && flag2 == 0)
			flag2 = 1;
		else if (main->line[main->i] == c2 && flag2 == 1)
			flag2 = 0;
		main->i++;
	}
	if (flag2 == 1)
		return (1);
	return (flag);
}
