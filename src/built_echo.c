/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:14:29 by alromero          #+#    #+#             */
/*   Updated: 2021/03/10 17:40:15 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_word_since(char *s, char c)
{
	int		i;
	int		cont;
	char	*tmp;

	i = 0;
	cont = 0;
	while (s[i] != c)
		i++;
	i++;
	while (s[i] != '\0')
	{
		i++;
		cont++;
	}
	tmp = (char *)malloc(sizeof(char) * cont + 1);
	i -= cont;
	cont = 0;
	while (s[i] != '\0')
		tmp[cont++] = s[i++];
	tmp[cont] = '\0';
	return (tmp);
}

int		search_in_env(t_main *main, char *s)
{
	char	*tmp;
	char	*tmp_env;
	t_node	*iterator;

	tmp = create_word_since(s, '$');
	iterator = main->env->first;
	while (iterator != NULL)
	{
		tmp_env = piece_of_word(iterator->element, '=');
		if (ft_strcmp(tmp, tmp_env) == 0)
		{
			free(tmp_env);
			tmp_env = ft_strdup(iterator->element);
			print_since_c(tmp_env, '=');
            free(tmp);
			free(tmp_env);
			return (1);
		}
		else
		{
			free(tmp_env);
			iterator = iterator->next;
		}
	}
    free(tmp);
	return (0);
}

int		print_echo_env(t_main *main, t_node *iterator, int pos)
{
	int	is_env;
	char	*tmp;

	tmp = ft_strdup(iterator->element);
	is_env = check_word(tmp);
	if (is_env == 1)
	{
		check_word_env(main, tmp, pos);
		if (main->env->size == 2 && ft_strlen(get_element(main->env, 1)) == 1)
			write(1, "$", 1);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

void	write_words(t_main *main, t_node *iterator, int flag)
{
	int i;

	main->flag_n = 0;
	i = 1;
	while (iterator != NULL)
	{
		if (ft_strcmp(iterator->element, "-n") == 0 && main->flag_n == 0)
			main->flag_n = 0;
		else if (ft_strcmp(iterator->element, "$?") == 0)
			printf("%d\n", main->status_pid / 256);
		else
		{
			main->flag_n = 1;
			flag = print_echo_env(main, iterator, i);
			if (flag == 0)
				print_echo(iterator->element);
			if (iterator->next != NULL)
				write(1, " ", 1);
		}
		if (iterator != NULL)
		{
			iterator = iterator->next;
			i++;
		}
	}
}

void	echo(t_main *main, t_list *list)
{
	int		flag;
	t_node	*iterator;

	flag = 0;
	if (list->size == 1)
		write(1, "\n", 1);
	else
	{
		iterator = list->first->next;
		if (ft_strcmp(iterator->element, "-n") == 0)
			iterator = iterator->next;
		write_words(main, iterator, flag);
		if (ft_strcmp(get_element(list, 1), "-n") != 0 &&
		ft_strcmp(get_element(list, 1), "$?") != 0)
			write(1, "\n", 1);
	}
}
