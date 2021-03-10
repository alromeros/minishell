/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_selector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:05:29 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 14:07:54 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		its_a_pipe(t_nodo **arbol, t_tree_vars *vars)
{
	if (vars->iterator->next == NULL)
		return (errors_tree("|"));
	if ((*arbol)->type == 1)
		its_a_pipe(&(*arbol)->dcho, vars);
	else
	{
		vars->temp = *arbol;
		*arbol = vars->nuevo;
		(*arbol)->izq = vars->temp;
		(*arbol)->dcho = NULL;
	}
	vars->flag_word = 0;
	return (0);
}

int		its_a_semicolon(t_nodo **arbol, t_tree_vars *vars)
{
	if (vars->iterator->next == NULL)
		return (0);
	vars->temp = *arbol;
	*arbol = vars->nuevo;
	(*arbol)->izq = vars->temp;
	(*arbol)->dcho = NULL;
	vars->flag_word = 0;
	return (0);
}

int		its_a_redir_input(t_nodo **arbol, t_tree_vars *vars)
{
	if (vars->iterator->next == NULL)
		return (errors_tree("newline"));
	else
	{
		vars->iterator = vars->iterator->next;
		free(vars->nuevo->valor);
		vars->nuevo->valor = strdup(vars->iterator->element);
		if ((*arbol)->dcho == NULL)
			(*arbol)->dcho = vars->nuevo;
		else
			insert_redir((*arbol)->dcho, vars->nuevo);
	}
	return (0);
}

void	its_a_word(t_nodo **arbol, t_tree_vars *vars)
{
	if (vars->type == 3)
	{
		if ((*arbol)->izq != NULL)
		{
			if ((*arbol)->dcho == NULL)
				(*arbol)->dcho = vars->nuevo;
			else
				insert_right((*arbol)->dcho, vars->nuevo);
		}
		else
			(*arbol)->izq = vars->nuevo;
		vars->flag_word = 1;
	}
	else if (vars->type == 6)
	{
		if ((*arbol)->dcho != NULL)
			insert_right_left((*arbol), vars->nuevo, 3, 6);
		else if ((*arbol)->izq == NULL)
			((*arbol)->izq = vars->nuevo);
		else
			insert((*arbol)->izq, vars->nuevo, 0, vars->type);
	}
}
