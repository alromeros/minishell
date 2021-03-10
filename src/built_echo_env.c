/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:01:18 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 13:04:06 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_word(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*create_word(t_vars *vars, char *s)
{
	char *tmp;

	vars->j = 0;
	while (s[vars->i] != '\0' && s[vars->i] != ' ')
	{
		vars->j++;
		vars->i++;
	}
	tmp = (char*)malloc(sizeof(char) * vars->j + 1);
	vars->i -= vars->j;
	vars->j = 0;
	while (s[vars->j] != '\0' && s[vars->i] != ' ')
		tmp[vars->j++] = s[vars->i++];
	tmp[vars->j] = '\0';
	return (tmp);
}

int		search_word_in_env(t_main *main, char *s)
{
	t_node	*iterator;
	char	*tmp;
	char	*tmp_env;

	iterator = main->env->first;
	while (iterator != NULL)
	{
		tmp = piece_of_word(iterator->element, '=');
		if (ft_strcmp(tmp, s) == 0)
		{
			tmp_env = ft_strdup(iterator->element);
			print_since_c(tmp_env, '=');
			free(tmp);
			free(tmp_env);
			return (1);
		}
		else
		{
			free(tmp);
			iterator = iterator->next;
		}
	}
	return (0);
}

void	print_dolar(t_main *main, t_vars *vars, char *s)
{
	char *tmp;

	if (s[vars->i - 1] && s[vars->i - 1] == 92)
		print_until_c(vars, s, 32);
	else
	{
		vars->i++;
		vars->cont = vars->i;
		tmp = create_word(vars, s);
		if (is_bar(main, tmp) != 0)
			vars->flag = search_word_in_env(main, tmp);
		free(tmp);
	}
}

int		check_word_env(t_main *main, char *s, int pos)
{
	t_vars	vars;

	vars.cont = 0;
	vars.i = 0;
	if (main->flag_quote == pos)
		write(1, s, ft_strlen(s));
	else
	{
		while (s[vars.i] != '\0')
		{
			if (s[vars.i] != '$' && s[vars.i] != '\0')
				print_until_c(&vars, s, '$');
			else if (s[vars.i] == '$' && s[vars.i] != '\0')
				print_dolar(main, &vars, s);
		}
	}
	return (1);
}
