/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:47:44 by alromero          #+#    #+#             */
/*   Updated: 2021/03/10 17:33:55 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_front(t_list *list)
{
	t_node *pop;

	pop = list->first;
	if (list->first != NULL)
	{
		list->first = list->first->next;
		destructor_node(pop);
		list->size--;
	}
}

void	pop_back(t_list *list)
{
	t_node *pop;
	t_node *previous_position;

	pop = list->first;
	previous_position = NULL;
	if (list->first != NULL)
	{
		if (list->size > 1)
		{
			while (pop->next != NULL)
			{
				previous_position = pop;
				pop = pop->next;
			}
            if (previous_position)
			    previous_position->next = NULL;
			destructor_node(pop);
			list->size--;
		}
		else
		{
			list->first = NULL;
			destructor_node(pop);
			list->size--;
		}
	}
}

void	pop_n_element(t_list *list, int n)
{
	t_node	*pop;
	t_node	*previous_position;

	pop = list->first;
	previous_position = NULL;
	if (list->first != NULL)
	{
		if (n == 0)
			pop_front(list);
		else if (n < list->size)
			deleting_elements(list, previous_position, pop, n);
	}
}

int		compare_element_c(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

t_list	*copy_list(t_list *list)
{
	t_list	*copy;
	t_node	*iterator;

	copy = new_list();
	iterator = list->first;
	while (iterator != NULL)
	{
		push_back(copy, iterator->element);
		iterator = iterator->next;
	}
	return (copy);
}
