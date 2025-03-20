/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:58:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 20:54:03 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/minishell.h"


/* in ou out (?) no execute_builtins.c*/
/* execute_builtins.c */
int		execute_builtin(t_msh *msh, char **args, char ***export, int fd);

/* fork_and_execute1.c */
void	handle_error(const char *message);
void	redirect_input(t_exec *exec);
void	redirect_output(t_exec *exec);
void	fork_and_execute_command(char **args, t_exec *exec, char **env);

/* fork_and_execute2.c */
void	setup_pipe_and_execute(char **args, int *input_fd, char **env);
void	wait_for_children(int num_commands);
void	execute_multiple_pipes(char ***commands, int num_commands, char **env);

/* init_exec.c */

/* *in_fd é pointer e
não pode ser substituido pelo exec->in_fd nas redireções.c todas */
/* redirections1.c */
void	handle_input_redirection(char **args, int *in_fd, int i);
void	handle_output_redirection(char **args, int *out_fd, int i);
void	handle_append_redirection(char **args, int *out_fd, int i);
void	handle_redirections(char **args, int *in_fd, int *out_fd);
void	execute_command(char **args, t_exec *exec, char **env);

/* redirections2.c */
void	child_process_logic(char **args, char **env);
void	execute_with_redirections(char **args, char **env);

#endif
