/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:05:50 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 15:09:26 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_until_same_char(t_main *main, t_vars *s, char c)
{
	s->j++;
	while (main->line[s->j] != c)
	{
		s->cont++;
		s->j++;
	}
	s->j++;
	main->words[s->k] = (char*)malloc(sizeof(char) * (s->cont + 1));
	s->cont = 0;
	s->k++;
}

void	malloc_until_diferent_char(t_main *main, t_vars *s, char c)
{
	while (main->line[s->j] == c && main->line[s->j] != '\0')
	{
		s->cont++;
		s->j++;
	}
	main->words[s->k] = (char*)malloc(sizeof(char) * (s->cont + 1));
	s->cont = 0;
	s->k++;
}

void	malloc_characters(t_main *main, t_vars *s)
{
	while (!(notflags(main->line[s->j]))
	&& ft_isspace(main->line[s->j]) && main->line[s->j] != '\0')
	{
		s->cont++;
		s->j++;
	}
	main->words[s->k] = (char*)malloc(sizeof(char) * (s->cont + 1));
	s->cont = 0;
	s->k++;
}

void	initialize_vars(t_vars *s)
{
	s->cont = 0;
	s->k = 0;
	s->j = 0;
}

void	malloc_words(t_main *main)
{
	t_vars s;

	num_words(main);
	initialize_vars(&s);
	main->words = (char**)malloc(sizeof(char*) * main->num_words + 1);
	while (main->line[s.j] != '\0')
	{
		if (!(notflags(main->line[s.j])) && ft_isspace(main->line[s.j]))
			malloc_characters(main, &s);
		if (main->line[s.j] == '\"' && main->line[s.j + 1] != '\0')
			malloc_until_same_char(main, &s, '\"');
		if (main->line[s.j] == '\'' && main->line[s.j + 1] != '\0')
			malloc_until_same_char(main, &s, '\'');
		if (main->line[s.j] == '>')
			malloc_until_diferent_char(main, &s, '>');
		if (main->line[s.j] == '<')
			malloc_until_diferent_char(main, &s, '<');
		if (main->line[s.j] == ';')
			malloc_until_diferent_char(main, &s, ';');
		if (main->line[s.j] == '|')
			malloc_until_diferent_char(main, &s, '|');
		if (main->line[s.j] == ' ')
			s.j++;
	}
}
