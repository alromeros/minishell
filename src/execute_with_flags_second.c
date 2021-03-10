/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_flags_second.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:17:03 by alromero          #+#    #+#             */
/*   Updated: 2021/02/05 13:21:19 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_and_pid(t_flags *flags)
{
	flags->p_read = 0;
	flags->p_write = 1;
	flags->pipe_n = (int*)malloc(sizeof(int) * 2);
	if (pipe(flags->pipe_n) == -1)
	{
		perror("pipe");
		exit(1);
	}
	flags->pid_right = fork();
	if ((flags->pid_right) == -1)
	{
		perror("fork");
		exit(1);
	}
}

void	redir_out(t_arbol *tree, t_main *main, t_flags *flags)
{
	if ((flags->redir = open(tree->valor, O_RDONLY, 0644)) == -1)
	{
		write(1, "Minishell: ", 11);
		write(1, tree->valor, ft_strlen(tree->valor));
		write(1, ": No such file or directory\n", 28);
		return ;
	}
	if (tree->izq != NULL)
	{
		dup2(flags->redir, STDIN_FILENO);
		select_redir(tree->izq, main, flags);
		close(flags->redir);
	}
	dup2(flags->redir, STDIN_FILENO);
}

void	redir_concat(t_arbol *tree, t_main *main, t_flags *flags)
{
	flags->redir = open(tree->valor, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tree->izq != NULL)
	{
		select_redir(tree->izq, main, flags);
		close(flags->redir);
	}
	dup2(flags->redir, STDOUT_FILENO);
}

void	redir(t_arbol *tree, t_main *main, t_flags *flags)
{
	flags->redir = open(tree->valor, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (tree->izq != NULL)
	{
		select_redir(tree->izq, main, flags);
		close(flags->redir);
	}
	dup2(flags->redir, STDOUT_FILENO);
}

void	execute_flag_command(t_arbol *tree,
t_main *main, t_tree_vars *vars, t_flags *flags)
{
	if (tree->dcho != NULL)
		select_redir(tree->dcho, main, flags);
	exec_cmd_redir(tree, main, vars, flags);
}
