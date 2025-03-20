/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:01:00 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/19 15:12:42 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/minishell.h"

/* cd */ /* REVER: find_env_value */
char	*find_env_value(char **env, const char *var);
// static int	change_dir(const char *path);
void	change_directory(char **env, const char *path);
void	cd_command(char **env, char **args);

/* env1 */
char	*create_env_entry(const char *key, const char *value);
char	**allocate_env(char **envp);
int		process_env_variable(char *env_var, char **env, int i);
char	**init_env_array(char **envp);

/* env2 */
int		find_env_key_index(char **env, const char *key);
char	**update_env_var(char *arg, char **env, int idx);
char	**expand_env(char **env, char *new_entry);
void	set_or_add_env_value(char **env, const char *key, const char *value);
char	**general_manage_env(t_env *env, int action, char **envp);

/* pwd */
void	my_pwd(int fd);

/* echo */
int		is_flag_n(char *str);
void	print_args(char **args, int start_index);
void	run_echo(char **args);

/* exit */
int		exit_format_error(char *cmd);
int		normalize_exit_code(int code);
void	exit_error(char *arg);
void	exec_exit(char **args);

/* export1 */
int		is_valid_var_char(char c, int is_first_char);
int		parse_export(char *str);
void	format_export_var(const char *var);
int		find_var_index(char **env, const char *var, int name_len);
void	add_new_var(char ***env, const char *var);

/* export2 */
void	add_or_update_env_var(char ***env, const char *var);
void	print_sorted_env(char **env, int fd);
void	export_command(char **args, char ***env, int fd);
char	**init_export_array(char **env);

/* unset1 */
void	remove_from_array(char **array, int index);
void	unset_env_var(char **envp, char **export, const char *var);
void	exec_unset(char **envp, char **export, char **args, int *exit_status);
int		input_size(char **array);
void	read_unset(char **envp, char **export, char **cmds, int *exit_status);

/* unset2 */
int		ft_strcmp_nochr(const char *s1, const char *s2, char delim);

#endif
