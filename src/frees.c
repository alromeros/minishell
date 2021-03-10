/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:33:36 by alromero          #+#    #+#             */
/*   Updated: 2021/03/10 17:38:34 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	free_default(char **s, int n)
{
	int i;

	i = 0;
	while (i < n)
		free(s[i++]);
	free(s);
}

void	free_pipes(int **pipes, int n_pipes)
{
	int i;

	i = 0;
	while (i < n_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	free_all_line(t_main *main)
{
	free_default(main->words, main->num_words);
	destructor_list(main->words_list);
}

int		ch_w_2(t_main *main, char *s1, char *s2)
{
	t_node	*iterator;
	int		cont;

	cont = 0;
	iterator = main->words_list->first;
	while (iterator != NULL)
	{
		if (ft_strcmp(iterator->element, s1) == 0)
		{
			if (iterator->next != NULL &&
			ft_strcmp(iterator->next->element, s2) == 0)
				cont++;
		}
		iterator = iterator->next;
	}
	return (cont);
}

int		check_words(t_main *main)
{
	char	*error;
	int		cont;
	int		cont2;
	int		cont3;

	error = "minishell: syntax error near unexpected token `";
	cont = ch_w_2(main, ";", ";");
	cont2 = ch_w_2(main, ">", "<");
	cont3 = ch_w_2(main, "<", ">");
	if (cont >= 1 || cont2 >= 1 || cont3 >= 1)
	{
		write(1, error, ft_strlen(error));
		if (cont)
			write(1, ";", 1);
		else if (cont2)
			write(1, "<", 1);
		else if (cont3)
			write(1, "newline", 7);
		write(1, "\'\n", 2);
		return (1);
	}
	return (0);
}
