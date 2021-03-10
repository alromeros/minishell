/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:03:09 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 14:05:02 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodo	*crear_nodo(t_nodo *padre, char *s, int type)
{
	t_nodo *nuevo_nodo;

	nuevo_nodo = (t_nodo*)malloc(sizeof(t_nodo));
	nuevo_nodo->dcho = NULL;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->padre = padre;
	nuevo_nodo->type = type;
	nuevo_nodo->valor = strdup(s);
	return (nuevo_nodo);
}

void	destruir_nodo(t_nodo *nodo)
{
	nodo->dcho = NULL;
	nodo->izq = NULL;
	free(nodo->valor);
	free(nodo);
}

void	print_tree(t_nodo *nodo, int level, int side)
{
	if (side == 2)
		printf("Level %d | %-10s | valor es '%-5s' | type es %d\n",
		level, "root", nodo->valor, nodo->type);
	else
		printf("Level %d | %-5s side | valor es '%-5s' | type es %d\n",
				level, side ? "Right" : "Left", nodo->valor, nodo->type);
	if (nodo->izq)
		print_tree(nodo->izq, level + 1, 0);
	if (nodo->dcho)
		print_tree(nodo->dcho, level + 1, 1);
}

int		errors_tree(char *s)
{
	char *error_text;

	error_text = "minishell: syntax error near unexpected token `";
	write(1, error_text, ft_strlen(error_text));
	write(1, s, ft_strlen(s));
	write(1, "'\n", 2);
	return (1);
}
