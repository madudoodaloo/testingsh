/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:47:08 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 15:18:14 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_or_update_env_var(char ***env, const char *var)
{
	char	*equals;
	int		name_len;
	int		index;

	equals = ft_strchr(var, '=');
	if (equals)
		name_len = equals - var;
	else
		name_len = ft_strlen(var);
	index = find_var_index(*env, var, name_len);
	if (index != -1)
	{
		free((*env)[index]);
		(*env)[index] = ft_strdup(var);
		if (!(*env)[index])
		{
			perror("strdup failed");
			exit(1);
		}
	}
	else
		add_new_var(env, var);
}

char	**get_matrix_env(t_env *env)
{
	t_env	*temp;
	char	**matrix_env;
	int		env_size;
	int		i;

	temp = env;
	env_size = 0;
	while (temp)
	{
		env_size++;
		temp = temp->next;
	}
	matrix_env = (char **)safe_malloc((env_size + 1) * sizeof(char *));
	temp = env;
	i = 0;
	while (temp && !matrix_env)
	{
		matrix_env[i] = ft_strdup(temp->var);
		i++;
		temp = temp->next;
	}
	matrix_env[i] = NULL;
	return (matrix_env);
}

void	print_sorted_env(t_env *env, int fd)
{
	char	**temp_env;
	int		env_size;
	int		i;
	int		j;

	temp_env = get_matrix_env(env);
	env_size = 0;
	while (temp_env[env_size])
		env_size++;
	i = 0;
	while (i < env_size - 1)
	{
		j = i + 1;
		while (j < env_size)
		{
			if (ft_strcmp(temp_env[i], temp_env[j]) > 0)
				ft_swap(&temp_env[i], &temp_env[j]);
			j++;
		}
		i++;
	}
	i = -1;
	while (temp_env[++i])
		format_export_var(temp_env[i]);
	free_matrix(temp_env);
}

void	export_command(char **args, t_env *env, int fd)
{
	int	i;

	if (!args[1])
		print_sorted_env(, fd);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!parse_export(args[i]))
				printf("export: '%s': not a valid identifier\n", args[i]);
			else
			{
				add_or_update_env_var(env, args[i]);
				print_sorted_env(*env, fd);
			}
			i++;
		}
	}
}

char	**init_export_array(char **env)
{
	int		i;
	char	**export;

	i = 0;
	while (env[i])
		i++;
	export = (char **)safe_malloc((i + 1) * sizeof(char *));
	if (!export)
		return (NULL);
	i = 0;
	while (env[i])
	{
		export[i] = ft_strdup(env[i]);
		if (!export[i])
		{
			while (i > 0)
				free(export[--i]);
			free(export);
			return (NULL);
		}
		i++;
	}
	export[i] = NULL;
	return (export);
}
