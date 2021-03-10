/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:16:58 by alromero          #+#    #+#             */
/*   Updated: 2021/02/17 10:18:37 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_without_inputs(t_arbol *tree)
{
	if (tree->type == 5)
		open(tree->valor, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (tree->type == 7)
		open(tree->valor, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	select_redir(t_arbol *tree, t_main *main, t_flags *flags)
{
	if (tree->type == 4)
		redir_out(tree, main, flags);
	else if (tree->type == 5)
		redir(tree, main, flags);
	else if (tree->type == 7)
		redir_concat(tree, main, flags);
}

void	exec_cmd_redir(t_arbol *tree,
		t_main *main, t_tree_vars *vars, t_flags *flags)
{
	if (vars->select_word >= 0)
		execute_builtins(main, flags->cmd, vars->select_word, tree);
	else
		search_command(main, flags->cmd);
}
