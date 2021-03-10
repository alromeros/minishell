/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:21:18 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 18:05:25 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_main *main)
{
	int		i;
	int		flag;
	t_node	*iterator;

	iterator = main->export->first;
	while (iterator != NULL)
	{
		write(1, "declare -x ", 11);
		flag = 0;
		i = 0;
		while (iterator->element[i] != '\0')
		{
			write(1, &iterator->element[i], 1);
			if (iterator->element[i] == '=')
			{
				write(1, "\"", 1);
				flag = 1;
			}
			i++;
		}
		if (flag == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		iterator = iterator->next;
	}
}

int		search_in_list(t_list *list, char *s, int i)
{
	char	*tmp;
	char	*tmp_to_cmp;
	t_node	*iterator;

	i = 0;
	tmp = piece_of_word(s, '=');
	iterator = list->first;
	while (iterator != NULL)
	{
		tmp_to_cmp = piece_of_word(iterator->element, '=');
		if (ft_strcmp(tmp, tmp_to_cmp) == 0)
		{
			free(tmp);
			free(tmp_to_cmp);
			return (i);
		}
		else
		{
			free(tmp_to_cmp);
			i++;
			iterator = iterator->next;
		}
	}
	free(tmp);
	return (-1);
}

int		check_first_letter(char *s, int flag)
{
	if (flag == 0)
	{
		if (s[0] == '=')
		{
			write(1, "export: \'", 9);
			write(1, s, ft_strlen(s));
			write(1, "\': not a valid identifier\n", 26);
			return (1);
		}
		else if (s[0] == '.')
		{
			write(1, "export: \'", 9);
			write(1, s, ft_strlen(s));
			write(1, "\': not a valid identifier\n", 26);
			return (1);
		}
		return (0);
	}
	else if (flag == 1)
	{
		if (s[0] == '=' || s[0] == '.')
			return (1);
		return (0);
	}
	return (0);
}

void	search_words_list_export(t_main *main, t_list *list_to_search,
t_list *words_list)
{
	t_node	*iterator;
	int		to_search;
	int		first_error;

	iterator = words_list->first->next;
	while (iterator != NULL)
	{
		first_error = check_first_letter(iterator->element, 1);
		main->status_pid = first_error * 256;
		if (first_error == 0)
		{
			to_search = search_in_list(list_to_search, iterator->element, 0);
			if (to_search == -1)
				push_back(list_to_search, iterator->element);
			else if (to_search >= 0)
				modify_element(list_to_search, iterator->element, to_search);
		}
		iterator = iterator->next;
	}
}

void	export(t_main *main, t_list *list)
{
	int		i;
	t_node	*iterator;

	if (main->flag_export > 0)
	{
		i = 0;
		iterator = list->first;
		while (i < (main->flag_export - 1))
		{
			iterator = iterator->next;
			i++;
		}
		free(iterator->element);
		//iterator->element = ft_strjoin(iterator->element,
		//iterator->next->element);
		pop_n_element(list, main->flag_export);
	}
	search_words_list_env(main, main->env, list);
	search_words_list_export(main, main->export, list);
	if (list->size == 1)
		print_export(main);
}
