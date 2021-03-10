/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_second_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:31 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 19:09:20 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = malloc(ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
    if (!s1 || !s2)
    {
        return 1;
    }
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(char *str, int c)
{
	unsigned int i;
	unsigned int leng;

	i = 0;
	if (!str)
		return (NULL);
	leng = ft_strlen(str);
	while (*str && *str != c)
	{
		i++;
		str++;
	}
	if (*str != c && i == leng)
		return (NULL);
	return (str);
}
