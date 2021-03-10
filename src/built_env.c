/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:23:14 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 13:51:49 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_vars *va)
{
	va->k = 0;
	va->j = 0;
}

void	is_env(t_main *main)
{
	t_vars va;

	init_vars(&va);
	main->is_env_count = 0;
	main->is_env = (int*)malloc(sizeof(int) * main->num_words + 1);
	va.iterator = main->words_list->first;
	while (va.iterator != NULL)
	{
		va.i = 0;
		while (va.iterator->element[va.i] != '\0')
		{
			if (va.iterator->element[va.i] == '$' &&
			va.iterator->element[va.i + 1] == '$')
				va.i++;
			else if (va.iterator->element[va.i] == '$')
			{
				main->is_env[va.k] = va.j;
				main->is_env_count++;
				va.k++;
			}
			va.i++;
		}
		va.j++;
		va.iterator = va.iterator->next;
	}
}

int		compare_and_search(t_list *list_to_search, char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (search_in_list(list_to_search, s, 0));
		i++;
	}
	return (-2);
}

void	search_words_list_env(t_main *main, t_list *l_search,
t_list *words_list)
{
	t_node	*iterator;
	int		to_search;
	int		position;

	srand(time(NULL));
	iterator = words_list->first->next;
	while (iterator != NULL)
	{
		main->flag_error = check_first_letter(iterator->element, 0);
		if (main->flag_error == 0)
		{
			to_search = compare_and_search(l_search, iterator->element);
			if (to_search == -1)
			{
				position = rand() % (l_search->size);
				push_after_n(l_search, iterator->element, position);
			}
			else if (to_search >= 0)
				modify_element(l_search, iterator->element, to_search);
		}
		iterator = iterator->next;
	}
}

void	env(t_list *list)
{
	t_node	*iterator;
	int		i;

	iterator = list->first;
	while (iterator != NULL)
	{
		i = 0;
		while (iterator->element[i] != '\0')
		{
			write(1, &iterator->element[i], 1);
			i++;
		}
		write(1, "\n", 1);
		iterator = iterator->next;
	}
}
