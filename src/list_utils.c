/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:01:54 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 15:03:40 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_list(void)
{
	t_list *list;

	list = (t_list *)malloc(sizeof(t_list));
	list->first = NULL;
	list->size = 0;
	return (list);
}

t_node	*new_node(char *s)
{
	t_node *node_n;

	node_n = (t_node *)malloc(sizeof(t_node));
	node_n->element = ft_strdup(s);
	node_n->next = NULL;
	return (node_n);
}

void	destructor_node(t_node *node)
{
	free(node->element);
	free(node);
}

void	destructor_list(t_list *list)
{
	int i;

	i = 0;
	while (list->first != NULL)
	{
		pop_front(list);
		i++;
	}
	free(list);
}

int		size_list(t_list *lista)
{
	return (lista->size);
}
