/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:11:07 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 15:13:27 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_until_same_char(t_main *main, t_vars *m, char c)
{
	main->num_words++;
	m->cont = 0;
	m->j++;
	while (main->line[m->j] != c && main->line[m->j] != '\0')
	{
		m->j++;
		m->cont++;
	}
	m->j++;
}

void	count_until_diferent_char(t_main *main, t_vars *m, char c)
{
	main->num_words++;
	m->cont = 0;
	while (main->line[m->j] == c && main->line[m->j] != '\0')
	{
		m->j++;
		m->cont++;
	}
}

void	count_characters(t_main *main, t_vars *m)
{
	main->num_words++;
	m->cont = 0;
	while (ft_isspace(main->line[m->j])
	&& !(notflags(main->line[m->j])) && main->line[m->j] != '\0')
	{
		m->j++;
		m->cont++;
	}
}

void	num_words(t_main *main)
{
	t_vars m;

	m.j = 0;
	m.k = 0;
	main->num_words = 0;
	while (main->line[m.j] != '\0')
	{
		if (main->line[m.j] == '\"' && main->line[m.j + 1] != '\0')
			count_until_same_char(main, &m, '\"');
		else if (main->line[m.j] == '\'' && main->line[m.j + 1] != '\0')
			count_until_same_char(main, &m, '\'');
		else if (main->line[m.j] == '|')
			count_until_diferent_char(main, &m, '|');
		else if (main->line[m.j] == '>')
			count_until_diferent_char(main, &m, '>');
		else if (main->line[m.j] == '<')
			count_until_diferent_char(main, &m, '<');
		else if (main->line[m.j] == ';')
			count_until_diferent_char(main, &m, ';');
		else if (ft_isspace(main->line[m.j]))
			count_characters(main, &m);
		else
			m.j++;
	}
}
