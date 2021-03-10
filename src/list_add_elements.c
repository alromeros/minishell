/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:41:56 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 14:47:10 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_front(t_list *list, char *s)
{
	t_node *new;

	new = new_node(s);
	new->next = list->first;
	list->first = new;
	list->size++;
}

void	push_back(t_list *list, char *s)
{
	t_node *new;
	t_node *iterator;

	new = new_node(s);
	iterator = NULL;
	if (list->first == NULL)
		list->first = new;
	else
	{
		iterator = list->first;
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = new;
	}
	list->size++;
}

void	push_after_n(t_list *list, char *s, int n)
{
	t_node	*new;
	t_node	*iterator;
	int		i;

	new = new_node(s);
	iterator = NULL;
	if (list->first == NULL)
		list->first = new;
	else
	{
		iterator = list->first;
		i = 0;
		while (iterator->next != NULL && i < n)
		{
			iterator = iterator->next;
			i++;
		}
		new->next = iterator->next;
		iterator->next = new;
	}
	list->size++;
}

char	*get_element(t_list *list, int n)
{
	t_node	*iterator;
	int		i;

	iterator = NULL;
	if (list->first == NULL)
		return (NULL);
	else
	{
		i = 0;
		iterator = list->first;
		while (iterator->next != NULL && i < n)
		{
			iterator = iterator->next;
			i++;
		}
		if (i != n)
			return (NULL);
		else
			return (iterator->element);
	}
}

void	modify_element(t_list *list, char *s, int n)
{
	t_node	*iterator;
	int		i;
	int		sign;

	iterator = NULL;
	sign = compare_element_c(s, '=');
	if (sign == 1)
	{
		if (n < list->size && list->first != NULL)
		{
			iterator = list->first;
			i = 0;
			while (i < n)
			{
				iterator = iterator->next;
				i++;
			}
			free(iterator->element);
			iterator->element = ft_strdup(s);
		}
	}
}
