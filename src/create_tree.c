/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:08:02 by alromero          #+#    #+#             */
/*   Updated: 2021/02/19 11:48:03 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tipo_de_nodo(char *s, int flag, int falg_semi)
{
	if ((strcmp(s, ";") == 0) && falg_semi == 0)
		return (1);
	else if (strcmp(s, "|") == 0)
		return (2);
	else if (strcmp(s, ">") == 0)
		return (5);
	else if (strcmp(s, "<") == 0)
		return (4);
	else if (strcmp(s, ">>") == 0)
		return (7);
	else if (flag == 0)
		return (3);
	else
		return (6);
}

int		search_flag_redir(t_node *iterator, int f_s)
{
	int flag_pipe;
	int flag_redir;
	int flag_anypipe;

	flag_redir = 0;
	flag_pipe = 0;
	flag_anypipe = 0;
	while (iterator != NULL)
	{
		if (tipo_de_nodo(iterator->element, 0, f_s) == 2)
			flag_anypipe = 1;
		if (tipo_de_nodo(iterator->element, 0, f_s) == 2 && flag_redir == 0)
			flag_pipe = 1;
		if ((tipo_de_nodo(iterator->element, 0, f_s) == 5 ||
		tipo_de_nodo(iterator->element, 0, f_s) == 7 ||
		tipo_de_nodo(iterator->element, 0, f_s) == 4)
		&& flag_pipe == 0)
			flag_redir = 1;
		iterator = iterator->next;
	}
	if (flag_redir == 1 && flag_anypipe == 0)
		return (0);
	else if (flag_redir == 1)
		return (1);
	return (0);
}

int		null_tree(t_nodo **arbol, t_tree_vars *vars)
{
	if (vars->type == 1 || vars->type == 2)
	{
		if (errors_tree(vars->iterator->element) == 1)
			return (1);
	}
	else if (vars->type == 3)
		vars->flag_word = 1;
	else if (vars->type == 4 || vars->type == 5 || vars->type == 7)
	{
		if (vars->iterator->next)
		{
			vars->iterator = vars->iterator->next;
			free(vars->nuevo->valor);
			vars->nuevo->valor = ft_strdup(vars->iterator->element);
		}
		else
		{
			errors_tree("newline");
			return (1);
		}
	}
	*arbol = vars->nuevo;
	return (0);
}

int		locate_type(t_nodo **arbol, t_tree_vars *vars)
{
	if (vars->type == 1)
		return (its_a_semicolon(&(*arbol), vars));
	else if (vars->type == 2)
		return (its_a_pipe(&(*arbol), vars));
	else if (vars->type == 4)
		return (its_a_redir_input(&(*arbol), vars));
	else if (vars->type == 5)
		return (its_a_redir_input(&(*arbol), vars));
	else if (vars->type == 7)
		return (its_a_redir_input(&(*arbol), vars));
	else
		its_a_word(&(*arbol), vars);
	return (0);
}

int		create_tree(t_nodo **arbol, t_tree_vars *vars, t_list *list)
{
	vars->flag_word = 0;
	vars->i = 0;
	vars->iterator = list->first;
	vars->flag_redir = search_flag_redir(vars->iterator, vars->f_s);
	vars->iterator = list->first;
	while (vars->iterator != NULL)
	{
		vars->type = tipo_de_nodo(vars->iterator->element, vars->flag_word,
				vars->f_s);
		vars->nuevo = crear_nodo(vars->nuevo,
		vars->iterator->element, vars->type);
		if (*arbol == NULL)
		{
			if (null_tree(&(*arbol), vars) == 1)
				return (1);
		}
		else if (locate_type(&(*arbol), vars) == 1)
			return (1);
		if (vars->iterator != NULL)
			vars->iterator = vars->iterator->next;
	}
	return (0);
}
