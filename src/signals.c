/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:13:37 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 15:14:12 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*gnl_works(void)
{
	static int i = 0;

	return (&i);
}

void	signals(int signal)
{
	if (signal == SIGINT)
	{
		if (*gnl_works() == 0)
		{
			write(1, "\033[2D\033[0K", 9);
			write(1, "\n\x1b[35mminishell\\> \x1b[0m", 23);
		}
		else
			write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		write(1, "\033[2D\033[0K", 9);
		if (*gnl_works())
			write(1, "Quit: 3\n", 8);
	}
}

void	deleting_elements(t_list *list, t_node *previous_position,
t_node *pop, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		previous_position = pop;
		pop = pop->next;
		i++;
	}
	if (i == n)
	{
		previous_position->next = pop->next;
		destructor_node(pop);
		list->size--;
	}
}

void	ft_signal_c1(int sign)
{
	if (sign == SIGINT)
		write(1, "\n", 1);
}

void	ft_signal_quit(int sign)
{
	if (sign == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}
