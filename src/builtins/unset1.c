/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:41:04 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/18 02:11:29 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_from_array(char **array, int index)
{
	if (!array || !array[index])
		return ;
	free(array[index]);
	while (array[index + 1])
	{
		array[index] = array[index + 1];
		index++;
	}
	array[index] = NULL;
}

void	unset_env_var(char **envp, char **export, const char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp_nochr(var, envp[i], '=') == 0 || ft_strcmp(var,
				envp[i]) == 0)
		{
			remove_from_array(envp, i);
			break ;
		}
		i++;
	}
	i = 0;
	while (export[i])
	{
		if (ft_strcmp_nochr(var, export[i], '=') == 0 || ft_strcmp(var,
				export[i]) == 0)
		{
			remove_from_array(export, i);
			break ;
		}
		i++;
	}
}

void	exec_unset(char **envp, char **export, char **args, int *exit_status)
{
	int	i;

	if (!args || !envp || !export)
		return ;
	i = 1;
	while (args[i])
	{
		unset_env_var(envp, export, args[i]);
		i++;
	}
	*exit_status = 0;
}

int	input_size(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

void	read_unset(char **envp, char **export, char **cmds, int *exit_status)
{
	int		i;
	int		len;
	char	*buffer;

	i = 1;
	len = input_size(cmds);
	while (i < len)
	{
		buffer = ft_strdup(cmds[i]);
		unset_env_var(envp, export, buffer);
		free(buffer);
		i++;
	}
	*exit_status = 0;
}
