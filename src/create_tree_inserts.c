/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_inserts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:59:48 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 14:02:47 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_right_left(t_nodo *arbol,
t_nodo *nuevo, int first_type, int second_type)
{
	if (arbol->type == first_type || arbol->type == second_type)
	{
		if (arbol->izq != NULL)
			insert_right_left(arbol->izq, nuevo, first_type, second_type);
		else
			arbol->izq = nuevo;
	}
	else if (arbol->dcho != NULL)
		insert_right_left(arbol->dcho, nuevo, first_type, second_type);
	else if (arbol->izq == NULL)
		arbol->izq = nuevo;
}

void	insert(t_nodo *arbol, t_nodo *nuevo, int n, int type)
{
	if (n == 0)
	{
		if (arbol->type == type)
		{
			if (arbol->izq != NULL)
				insert(arbol->izq, nuevo, 0, type);
			else
				arbol->izq = nuevo;
		}
		else if (arbol->izq == NULL)
			arbol->izq = nuevo;
		else
			insert(arbol->izq, nuevo, 0, type);
	}
	else if (n == 1)
	{
		if (arbol->dcho == NULL)
			arbol->dcho = nuevo;
		else
			insert(arbol->dcho, nuevo, 0, type);
	}
}

void	insert_right(t_nodo *arbol, t_nodo *nuevo)
{
	if (arbol->dcho != NULL)
		insert_right(arbol->dcho, nuevo);
	else
		arbol->dcho = nuevo;
}

void	insert_redir(t_nodo *arbol, t_nodo *nuevo)
{
	if (arbol->type == 4 || arbol->type == 5 || arbol->type == 7)
	{
		if (arbol->izq != NULL)
			insert_redir(arbol->izq, nuevo);
		else
			arbol->izq = nuevo;
	}
	else if (arbol->dcho != NULL)
		insert_redir(arbol->dcho, nuevo);
	else if (arbol->dcho == NULL)
		arbol->dcho = nuevo;
}
