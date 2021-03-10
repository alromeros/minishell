/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:58:12 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 12:58:43 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**second_split(t_vars *va, char *s, char c)
{
	char	**split;
	int		i;

	va->num_words = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * va->num_words + 1);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			split[i] = malloc_word(s, c);
			i++;
			while (*s != c && *s)
				s++;
		}
	}
	split[i] = NULL;
	return (split);
}

char	*strjoin_with_c(char *s1, char *s2, char c)
{
	int		i;
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	dst[i++] = c;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
