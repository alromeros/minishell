/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:56:29 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 15:10:58 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

char	*ft_strjoin_new(char const *s1, char const *s2)
{
	size_t	strlen;
	char	*new;
	int		x;
	int		y;

	if ((!s1) || (!s2))
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = (char*)malloc(sizeof(char) * (strlen + 1))))
		return (NULL);
	x = 0;
	while (s1[x] != '\0')
	{
		new[x] = s1[x];
		x++;
	}
	y = 0;
	while (s2[y] != '\0')
	{
		new[x] = s2[y];
		y++;
		x++;
	}
	new[x] = '\0';
	return (new);
}

int		ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == ' '
	|| c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (1);
}

int		notflags(char c)
{
	if (c != '\"' && c != '\'' && c != '>'
	&& c != '<' && c != '|' && c != ';')
		return (0);
	return (1);
}
