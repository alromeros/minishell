/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:19:54 by alromero          #+#    #+#             */
/*   Updated: 2021/03/09 19:32:36 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags *flags)
{
	flags->pid_left = fork();
	if (flags->pid_left < 0)
	{
		perror("pid left failed\n");
		exit(1);
	}
	if (flags->pid_left == 0)
	{
		flags->cmd = create_command_list(tree->izq, vars);
		dup2(flags->pipe_n[flags->p_write], STDOUT_FILENO);
		close(flags->pipe_n[flags->p_read]);
		vars->select_word = compare_command(tree->izq->valor, main);
		execute_flag_command(tree->izq, main, vars, flags);
		exit(EXIT_SUCCESS);
	}
	close(flags->pipe_n[flags->p_read]);
	close(flags->pipe_n[flags->p_write]);
	waitpid(flags->pid_left, &flags->status, 0);
	waitpid(flags->pid_right, &flags->status, 0);
}

void	last_command(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags *flags)
{
	flags->cmd = create_command_list(tree->dcho, vars);
	close(flags->pipe_n[flags->p_write]);
	dup2(flags->pipe_n[flags->p_read], STDIN_FILENO);
	close(flags->pipe_n[flags->p_read]);
	vars->select_word = compare_command(tree->dcho->valor, main);
	if (tree->dcho->dcho != NULL)
		execute_flag_command(tree->dcho, main, vars, flags);
	else
		execute_flag_command(tree, main, vars, flags);
	exit(EXIT_SUCCESS);
}

void	execute_pipe(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags flags)
{
	init_pipe_and_pid(&flags);
	if (flags.pid_right == 0)
	{
		if (flags.conductor != 1)
			dup2(flags.conductor, STDOUT_FILENO);
		last_command(tree, vars, main, &flags);
	}
	if (flags.conductor != STDOUT_FILENO)
		close(flags.conductor);
	if (tree->izq->type == 3)
		first_command(tree, vars, main, &flags);
	else
	{
		close(flags.pipe_n[flags.p_read]);
		flags.conductor = flags.pipe_n[flags.p_write];
		execute_pipe(tree->izq, vars, main, flags);
		waitpid(flags.pid_right, &flags.status, 0);
	}
	free(flags.pipe_n);
}

void	create_word_pid(t_arbol *tree, t_tree_vars *vars,
t_main *main, t_flags flags)
{
	flags.pid = fork();
	if (flags.pid == 0)
	{
		flags.cmd = create_command_list(tree, vars);
		vars->select_word = compare_command(tree->valor, main);
		execute_flag_command(tree, main, vars, &flags);
		exit(EXIT_SUCCESS);
	}
	else if (flags.pid < 0)
	{
		perror("pid");
		exit(1);
	}
	else
		waitpid(flags.pid, &flags.status, 0);
}

void	execute_with_flags(t_arbol *tree, t_tree_vars *vars, t_main *main)
{
	t_flags flags;
    flags.pipe_n = 0;
	flags.status = 0;
	flags.p_write = 0;
	flags.p_read = 0;
	flags.redir = 0;
	flags.redir_before = 0;
	flags.conductor = 0;
	flags.pid_right = 0;
	flags.pid_left = 0;
	flags.pid = 0;
	flags.cmd = 0;

	flags.p_read = 0;
	if (tree->type == 1)
	{
		execute_with_flags(tree->izq, vars, main);
		execute_with_flags(tree->dcho, vars, main);
	}
	else if (tree->type == 2)
	{
		flags.conductor = 1;
		execute_pipe(tree, vars, main, flags);
	}
	else if (tree->type == 5 || tree->type == 4 ||
	tree->type == 7)
		redir_without_inputs(tree);
	else
		execute_words(tree, vars, main, flags);
}
