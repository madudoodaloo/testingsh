/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:01:56 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/20 01:00:03 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../includes/minishell.h"

/* free_1.c */
void	free_var(t_env *var);
void	free_matrix(char **matrix);
void	free_tokens(t_token *tokens);
void	free_env(t_env *env);
void	free_exec(t_exec *exec);

/* free_2.c */
void	free_and_exit(void);

/* heredoc_utils.c */
void	int_to_str(int num, char *str);

/* libft_utils1 */
void	ft_swap(char **a, char **b);
void	ft_swap_char(char *a, char *b);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);

/* libft_utils2 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);

/* libft_utils3.c */
int		ft_isoperator(char *str, int i);
int		ft_isspace(char c);
int		ft_isalpha(char c);
int		ft_isdigit(char c);
int		ft_isquote(char c);

/* libft_utils4.c */
int		ft_strcmp(const char *s1, const char *s2);
void	ft_put_str_fd(char *str, int fd);
int		ft_atoi(char *str);
char	*ft_strjoin(const char *s1, const char *s2);

/* libft_utils5.c */
char	*ft_itoa(int n);

/* malloc.c */
void	*ft_memset(void *s, int c, size_t n);
void	*safe_malloc(size_t size);

/* utils_builtins.c */
void	print_error(void);
void	my_strcpy(char *dest, const char *src);
void	my_strcat(char *dest, const char *src);
int		ft_isalnum(int c);

/* utils_str.c */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);

/* delete.c */
void print_msh(t_msh *msh);
//void	print_exec_struct(t_exec *exec);
char	**copy_matrix(char **src);

#endif
