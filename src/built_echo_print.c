/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:08:29 by alromero          #+#    #+#             */
/*   Updated: 2021/02/22 13:49:45 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_final_word(t_main *main, t_vars *vars, char *s)
{
	char	*tmp;

	main->is_a_flag = 0;
	while (s[vars->i] != '\0')
	{
		if (s[vars->i] != '$')
			write(1, &s[vars->i++], 1);
		else if (s[vars->i] == '$')
		{
			vars->i++;
			tmp = create_word(vars, s);
			search_word_in_env(main, tmp);
			free(tmp);
		}
	}
}

void	print_since_c(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c)
		i++;
	i++;
	while (s[i] != '\0')
		write(1, &s[i++], 1);
}

void	print_until_c(t_vars *vars, char *s, char c)
{
	while (s[vars->i] != c && s[vars->i] != '\0')
	{
		if (s[vars->i] == 92 && s[vars->i + 1] == '$')
			vars->i++;
		else
			write(1, &s[vars->i++], 1);
	}
}

void	print_echo(char *s)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(s);
	i = 0;
	while (tmp[i] != '\0')
		write(1, &tmp[i++], 1);
	free(tmp);
}
