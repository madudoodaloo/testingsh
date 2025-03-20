/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:26:33 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 23:55:46 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(t_exec * exec, int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		if (data->is_heredoc)
		{
			data->is_heredoc = 0;
			g_signal = SIGINT;
			close(STDIN_FILENO);
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	handle_signals_and_cleanup(t_exec * exec)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		if (data->is_heredoc)
		{
			free_all(data->strut);
			exit(130);
		}
		else
			write(1, "\n", 1);
	}
	else if (g_signal == SIGQUIT)
	{
		g_signal = 0;
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	rl_clear_signals();
}

void	restore_parent_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_child_exit_status(int status)
{
	int	signal;

	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			write(1, "\n", 1);
		else if (signal == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	}
}
