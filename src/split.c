/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:42:15 by cpalazon          #+#    #+#             */
/*   Updated: 2021/03/10 17:30:55 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int		count_words(char *s, char c)
{
	int		count;

	count = 0;
    if (!s)
    {
        return 0;
    }
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*malloc_word(char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	*ft_protect(char **tab, int i)
{
	while (i < 0)
	{
		free(tab[i--]);
		free(tab);
	}
	return (NULL);
}

void	while_split(t_main *main, char *copy_line, char c)
{
	int i;

	i = 0;
    if (!copy_line)
    {
        return;
    }
	while (*copy_line)
	{
		while (*copy_line && *copy_line == c)
			copy_line++;
		if (*copy_line && *copy_line != c)
		{
			if (!(main->split[i] = malloc_word(copy_line, c)))
				ft_protect(main->split, i);
			i++;
			while (*copy_line && *copy_line != c)
				copy_line++;
		}
	}
}

void	split(t_main *main)
{
	int		words;
	int		i;
	char	c;
	char	*copy_line;

	copy_line = main->line;
	c = ';';
	if (!main->line)
		main->line = NULL;
	words = count_words(main->line, c);
	main->num_words_split = words;
	if (!(main->split = (char **)malloc(sizeof(char*) * (words + 1))))
		main->split = NULL;
	i = 0;
	while_split(main, copy_line, c);
    if (main->split)
	    main->split[i] = NULL;
}
