/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:40:50 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 15:17:56 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (strcmp(current->var_name, var_name) == 0)
			return (current->var_value);
		current = current->next;
	}
	return (NULL);
}

void	update_env_value(t_env *env, const char *var_name,
		const char *new_value)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (strcmp(current->var_name, var_name) == 0)
		{
			free(current->var_value);
			current->var_value = strdup(new_value);
			return ;
		}
		current = current->next;
	}
}

static int	change_dir(const char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd: chdir() error");
		return (-1);
	}
	return (0);
}

static const char	*get_target_path(t_msh *msh, const char *path)
{
	if (!path)
	{
		path = get_env_value(msh->env, "HOME");
		if (!path)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (NULL);
		}
	}
	else if (strcmp(path, "-") == 0)
	{
		path = get_env_value(msh->env, "OLDPWD");
		if (!path)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
	}
	return (path);
}

static void	update_pwd_vars(t_msh *msh, const char *old_pwd,
		const char *new_pwd)
{
	update_env_value(msh->env, "OLDPWD", old_pwd);
	update_env_value(msh->env, "PWD", new_pwd);
}

static void	print_directory_change(const char *old_pwd, const char *new_pwd,
		const char *path)
{
	if (strcmp(path, "-") == 0)
		printf("%s\n", new_pwd);
	printf("Changed directory from %s to %s\n", old_pwd, new_pwd);
}

void	change_directory(t_msh *msh, const char *path)
{
	char	old_pwd[4096];
	char	new_pwd[4096];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("cd: getcwd() error");
		return ;
	}
	path = get_target_path(msh, path);
	if (!path)
		return ;
	if (change_dir(path) == -1)
		return ;
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("cd: getcwd() error");
		return ;
	}
	update_pwd_vars(msh, old_pwd, new_pwd);
	print_directory_change(old_pwd, new_pwd, path);
}

void	cd_command(t_msh *msh, char **args)
{
	const char	*path;

	if (args[1] && args[2])
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return ;
	}
	if (args[1] != NULL)
		path = args[1];
	else
		path = NULL;
	change_directory(msh, path);
}

/* helpers */
static void	update_pwd_vars(t_msh *msh, const char *old_pwd,
		const char *new_pwd)
{
	update_env_value(msh->env, "OLDPWD", old_pwd);
	update_env_value(msh->env, "PWD", new_pwd);
}

static const char	*get_target_path(t_msh *msh, const char *path)
{
	if (!path)
	{
		path = get_env_value(msh->env, "HOME");
		if (!path)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (NULL);
		}
	}
	else if (strcmp(path, "-") == 0)
	{
		path = get_env_value(msh->env, "OLDPWD");
		if (!path)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
	}
	return (path);
}

static void	print_directory_change(const char *old_pwd, const char *new_pwd,
		const char *path)
{
	if (strcmp(path, "-") == 0)
		printf("%s\n", new_pwd);
	printf("Changed directory from %s to %s\n", old_pwd, new_pwd);
}
