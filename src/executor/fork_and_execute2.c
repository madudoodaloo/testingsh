/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_execute2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:25:57 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 15:23:52 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_pipe_and_execute(t_exec *exec, int *input_fd, char **env)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		handle_error("pipe");
	fork_and_execute_command(exec->cmd, exec, env);
	close(pipefd[1]);
	*input_fd = pipefd[0];
}

void	wait_for_children(t_exec *exec)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (exec)
	{
		waitpid(exec->pid, &status, 0);
		if (exec->pid > 0)
			// handle_child_exit_status(status);
			// if (WIFSIGNALED(status))
			// {
			// 	if (status == 130)
			// 	{
			// 		g_exec.status = 130;
			// 		ft_putstr(1, "\n");
			// 	}
			// 	else if (status == 131)
			// 		g_exec.status = 131;
			// }
			// if (WIFEXITED(status))
			// 	g_exec.status = WEXITSTATUS(status);
			exec = exec->next;
	}
}

void	execute_multiple_pipes(t_exec *exec, char **env)
{
	int		input_fd;
	int		i;
	t_exec	*head;

	head = exec;
	input_fd = STDIN_FILENO;
	i = 0;
	while (exec && exec->next)
	{
		setup_pipe_and_execute(exec, &input_fd, env);
		exec = exec->next;
	}
	fork_and_execute_command(exec->cmd, exec, env);
	// close(input_fd);	rever IF THERE IS ONLY ONE COMMAND NO PIPE IS MADE AND THIS CLOSES STDIN 
	wait_for_children(exec);
}
