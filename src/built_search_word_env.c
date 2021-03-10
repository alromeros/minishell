/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_search_word_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:54:24 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 13:55:14 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*piece_of_word(char *s, char c)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	ret = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
