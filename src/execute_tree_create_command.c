/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree_create_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:11:45 by alromero          #+#    #+#             */
/*   Updated: 2021/01/29 14:12:57 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_command(t_arbol *tree, t_tree_vars *vars, t_list *new)
{
	push_back(new, tree->valor);
	if (tree->izq != NULL)
		create_command(tree->izq, vars, new);
	return (new);
}

t_list	*create_command_list(t_arbol *tree, t_tree_vars *vars)
{
	t_list *new;

	new = new_list();
	push_back(new, tree->valor);
	if (tree->izq != NULL)
		create_command(tree->izq, vars, new);
	return (new);
}

void	execute_words(t_arbol *tree, t_tree_vars *vars, t_main *main,
t_flags flags)
{
	if (tree->dcho != NULL)
	{
		if (tree->dcho->type == 5 || tree->dcho->type == 4
		|| tree->dcho->type == 7)
			create_word_pid(tree, vars, main, flags);
	}
	else
		execute_no_flags(tree, vars, main);
}
