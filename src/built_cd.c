/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:49:51 by alromero          #+#    #+#             */
/*   Updated: 2021/03/10 18:04:13 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	adding_oldpwd(t_list *list_to_search,
char *oldpwd)
{
	int		to_search;

	to_search = search_in_list(list_to_search, oldpwd, 0);
	if (to_search == -1)
		push_back(list_to_search, oldpwd);
	else if (to_search >= 0)
		modify_element(list_to_search, oldpwd, to_search);
}

char	*ft_get_env(char *s)
{
	int		i;
	int		c;
	char	*ret;

	i = 0;
    c = 0;  
	while (s[i])
	{
		if (s[i] == '=')
			c = i;
		i++;
	}
	if (!i || !(ret = (char *)malloc(sizeof(char) * (i - c))))
        return NULL;
	c++;
	i = 0;
	while (s[c])
		ret[i++] = s[c++];
	ret[i] = '\0';
	return (ret);
}

char	*get_oldpwd(t_main *main, char *s)
{
	t_node	*iterator;
	char	*tmp;
	char	*tmp_env;

	iterator = main->env->first;
	while (iterator != NULL)
	{
		tmp = piece_of_word(iterator->element, '=');
		if (ft_strcmp(tmp, s) == 0)
		{
			tmp_env = ft_get_env(iterator->element);
			free(tmp);
			return (tmp_env);
		}
		else
		{
			free(tmp);
			iterator = iterator->next;
		}
	}
	return (NULL);
}

void	last_route(t_main *main)
{
	char *new_pwd;

	new_pwd = get_oldpwd(main, "oldpwd");
	if (new_pwd != NULL)
	{
		chdir(new_pwd);
		write(1, new_pwd, ft_strlen(new_pwd));
		write(1, "\n", 1);
		free(new_pwd);
	}
	else
		write(1, "cd: OLDPWD not set\n", 20);
}

void	cd(t_main *main, t_list *list)
{
	char where_iam[1024];
    char whoami[1024];
    char *userPath;
	char *oldpwd;

	getcwd(where_iam, -1);
	oldpwd = ft_strjoin("oldpwd=", where_iam);
	if (list->size == 1 || !(ft_strcmp(get_element(list, 1), "~")))
    {
        getlogin_r(whoami, 1024);
        if (ft_strcmp("root", whoami))
        {
            userPath = ft_strjoin("/home/", whoami);
		    chdir(userPath);
            free(userPath);
        }
        else
            chdir("/");
    }
	else if (!(ft_strcmp(get_element(list, 1), "..")))
		chdir("..");
	else if (!(ft_strcmp(get_element(list, 1), "-")))
		last_route(main);
	else if (chdir(get_element(list, 1)) != 0)
	{
		perror(get_element(list, 1));
		main->status_pid = 256;
	}
	adding_oldpwd(main->env, oldpwd);
	free(oldpwd);
}
