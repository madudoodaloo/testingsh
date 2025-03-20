/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:48 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 23:51:54 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_msh *msh, char **args, char ***export, int fd)
{
	if (fd == -1)
		fd = STDOUT_FILENO;
	if (ft_strcmp(args[0], "cd") == 0)
		cd_command(get_matrix_env(msh->env), args);
	else if (ft_strcmp(args[0], "export") == 0)
		export_command(args, get_matrix_env(msh->env), fd);
	else if (ft_strcmp(args[0], "unset") == 0)
		exec_unset(get_matrix_env(msh->env), *export, args, msh->exit_status);
	else if (ft_strcmp(args[0], "exit") == 0)
		exec_exit(args);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(get_matrix_env(msh->env), fd);
	else if (ft_strcmp(args[0], "pwd") == 0)
		my_pwd(fd);
	else if (ft_strcmp(args[0], "echo") == 0)
		run_echo(args);
	else
		return (0);
	return (1);
}
