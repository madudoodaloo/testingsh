/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:34:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 00:53:57 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process_logic(char **args, char **env)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	restore_parent_signals();
	handle_redirections(args, &in_fd, &out_fd);
	execute_command(args, in_fd, out_fd, env);
}

void	execute_with_redirections(char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_process_logic(args, env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		handle_child_exit_status(status);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}
