/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:50:16 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 19:51:29 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		its_a_number(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] >= 48 && s[i] <= 57)
		{
			n = (n * 10) + (s[i] - '0');
			i++;
		}
		else
			return (0);
	}
	return (n);
}

void	exit_numbers(t_arbol *tree, int ret)
{
	if (tree->izq != NULL)
		write(1, "bash: exit: too many arguments\n", 31);
	else
	{
		system("leaks minishell");
		exit(ret);
	}
}

void	built_exit(t_main *main, t_arbol *tree)
{
	int ret;

	ret = 0;
	write(1, "\x1b[31mexit\x1b[0m\n", 14);
	if (tree->izq != NULL)
	{
		ret = its_a_number(tree->izq->valor);
		if (ret == 0)
			exit(255);
		else
			exit_numbers(tree->izq, ret);
	}
	else
		exit(main->status_pid / 256);
}
