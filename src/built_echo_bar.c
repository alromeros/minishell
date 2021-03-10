/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:03:51 by alromero          #+#    #+#             */
/*   Updated: 2021/02/22 12:04:02 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_words(t_main *main, t_vars *v_bar, char *s, int length)
{
	v_bar->first_part = (char *)malloc(sizeof(char) *
	v_bar->i + 1);
	v_bar->last_part = (char *)malloc(sizeof(char) *
	(length - v_bar->i));
	while (v_bar->j < v_bar->i)
	{
		v_bar->first_part[v_bar->j] = s[v_bar->j];
		v_bar->j++;
	}
	v_bar->j++;
	v_bar->first_part[v_bar->j] = '\0';
	v_bar->i = 0;
	if (s[v_bar->j] == '$')
		main->flag_bar = 1;
	while (s[v_bar->j])
		v_bar->last_part[v_bar->i++] = s[v_bar->j++];
	v_bar->last_part[v_bar->i] = '\0';
}

int		is_bar(t_main *main, char *s)
{
	t_vars	v_bar;
	int		length;

	v_bar.i = 0;
	v_bar.j = 0;
	main->flag_bar = 0;
	length = ft_strlen(s);
	while (s[v_bar.i] && s[v_bar.i] != 92)
		v_bar.i++;
	if (s[v_bar.i] == '\0')
		return (1);
	c_words(main, &v_bar, s, length);
	search_word_in_env(main, v_bar.first_part);
	if (main->flag_bar == 0)
		write(1, "\\", 1);
	write(1, v_bar.last_part, ft_strlen(v_bar.last_part));
	free(v_bar.first_part);
	free(v_bar.last_part);
	return (0);
}
