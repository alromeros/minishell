/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:55:21 by alromero          #+#    #+#             */
/*   Updated: 2021/02/17 10:16:39 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_errors_unset(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '.' || s[i] == '=')
		{
			write(1, "unset: `", 8);
			write(1, s, ft_strlen(s));
			write(1, ": not a valid identifier\n", 28);
			return (1);
		}
		i++;
	}
	return (0);
}

int		compare_words_unset(t_list *list, char *s)
{
	t_node	*iterator;
	char	*to_compare;
	int		unset;

	unset = 0;
	iterator = list->first;
	while (iterator != NULL)
	{
		to_compare = piece_of_word(iterator->element, '=');
		if (ft_strcmp(s, to_compare) == 0)
		{
			free(to_compare);
			return (unset);
		}
		free(to_compare);
		unset++;
		iterator = iterator->next;
	}
	return (-1);
}

void	unset(t_main *main, t_list *list)
{
	t_node	*iterator;
	int		unset_export;
	int		unset_env;

	iterator = list->first->next;
	while (iterator != NULL)
	{
		if (check_errors_unset(iterator->element) == 0)
		{
			unset_env = compare_words_unset(main->env, iterator->element);
			unset_export = compare_words_unset(main->export, iterator->element);
			if (unset_export >= 0)
				pop_n_element(main->export, unset_export);
			if (unset_env >= 0)
				pop_n_element(main->env, unset_env);
		}
		iterator = iterator->next;
	}
}
