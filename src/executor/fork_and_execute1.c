/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_execute1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:05:44 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 15:21:10 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// rever se tenho que dar free a alguma merda
void	handle_error(const char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(1);
}

void	redirect_input(t_exec *exec)
{
	if (exec->in_fd != STDIN_FILENO)
	{
		if (dup2(exec->in_fd, STDIN_FILENO) == -1)
			handle_error("dup2");
		close(exec->in_fd);
	}
}

void	redirect_output(t_exec *exec)
{
	if (exec->out_fd != STDOUT_FILENO)
	{
		if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
			handle_error("dup2");
		close(exec->out_fd);
	}
}

void	fork_and_execute_command(char **args, t_exec *exec, char **env)
{
	pid_t	pid;

	exec->pid = fork();
	if (exec->pid == 0)
	{
		execute_command(args, exec, env);
		exit(0);
	}
	else if (exec->pid < 0)
		handle_error("fork");
}
