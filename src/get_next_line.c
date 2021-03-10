/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:38:23 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 14:40:46 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

int		getcharpls(char **line, char **aux, int n)
{
	char *temp;
	char *temp2;

	if (!n && !*aux)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((temp = ft_strchr(*aux, '\n')))
	{
		*temp = 0;
		*line = ft_strdup(*aux);
		temp2 = ft_strdup(++temp);
		free(*aux);
		*aux = temp2;
	}
	else
	{
		*line = ft_strdup(*aux);
		free(*aux);
		*aux = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(char **line)
{
	static char	*aux;
	char		buffer[512];
	int			n;
	char		*temp;

	if (!line)
		return (-1);
	while (ft_strchr(aux, '\n') == NULL)
	{
		n = read(0, buffer, 511);
		if (n < 0)
			return (-1);
		if (n == 0)
			break ;
		buffer[n] = 0;
		if (!aux)
			aux = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(aux, buffer);
			free(aux);
			aux = temp;
		}
	}
	return (getcharpls(line, &aux, n));
}
