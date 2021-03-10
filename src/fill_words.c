/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:28:53 by alromero          #+#    #+#             */
/*   Updated: 2021/02/17 10:19:56 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_until_same_char(t_main *main, t_vars *t, char c)
{
	if ((main->line[t->j] == '\"' || main->line[t->j] == '\''))
	{
		if (main->line[t->j - 1] && main->line[t->j - 1] == '=')
			main->flag_export = t->cont;
	}
	t->j++;
	t->k = 0;
	while (main->line[t->j] != c)
	{
		if (main->line[t->j] == ';')
			main->flag_colon = 1;
		if (c == '\'' && main->line[t->j] == '$')
			main->flag_quote = t->cont;
		main->words[t->cont][t->k] = main->line[t->j];
		t->k++;
		t->j++;
	}
	t->j++;
	main->words[t->cont][t->k] = '\0';
	push_back(main->words_list, main->words[t->cont]);
	t->cont++;
}

void	fill_until_diferent_char(t_main *main, t_vars *t, char c)
{
	char *error;

	error = "minishell: syntax error near unexpected token ";
	t->k = 0;
	while (main->line[t->j] == c && main->line[t->j] != '\0')
	{
		main->words[t->cont][t->k] = main->line[t->j];
		t->k++;
		t->j++;
	}
	main->words[t->cont][t->k] = '\0';
	if (c == ';' && t->k > 1)
	{
		write(1, error, ft_strlen(error));
		write(1, main->words[t->cont], ft_strlen(main->words[t->cont]));
		write(1, "\'\n", 2);
		main->flag_semi = 1;
	}
	push_back(main->words_list, main->words[t->cont]);
	t->cont++;
}

void	fill_word(t_main *main, t_vars *t)
{
	t->k = 0;
	while (ft_isspace(main->line[t->j]) &&
	!(notflags(main->line[t->j])) && main->line[t->j] != '\0')
	{
		main->words[t->cont][t->k] = main->line[t->j];
		t->k++;
		t->j++;
	}
	main->words[t->cont][t->k] = '\0';
	push_back(main->words_list, main->words[t->cont]);
	t->cont++;
}

void	init_t_vars(t_main *main, t_vars *t)
{
	main->words_list = new_list();
	t->k = 0;
	t->cont = 0;
	t->j = 0;
}

void	fill_words(t_main *main)
{
	t_vars t;

	init_t_vars(main, &t);
	while (main->line[t.j] != '\0')
	{
		if (main->line[t.j] == '\"' && main->line[t.j + 1] != '\0')
			fill_until_same_char(main, &t, '\"');
		else if (main->line[t.j] == '\'' && main->line[t.j + 1] != '\0')
			fill_until_same_char(main, &t, '\'');
		else if (main->line[t.j] == '>' && main->line[t.j] != '\0')
			fill_until_diferent_char(main, &t, '>');
		else if (main->line[t.j] == '<' && main->line[t.j] != '\0')
			fill_until_diferent_char(main, &t, '<');
		else if (main->line[t.j] == '|' && main->line[t.j] != '\0')
			fill_until_diferent_char(main, &t, '|');
		else if (main->line[t.j] == ';' && main->line[t.j] != '\0')
			fill_until_diferent_char(main, &t, ';');
		else if (main->flag_semi == 1)
			break ;
		else if (ft_isspace(main->line[t.j]) &&
		!(notflags(main->line[t.j])) && main->line[t.j] != '\0')
			fill_word(main, &t);
		else
			t.j++;
	}
}
