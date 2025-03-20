/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/20 02:19:48 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD 1
# define PIPE 2
# define R_OUT 3
# define R_APP 4
# define R_IN 5
# define HERE_DOC 6

// rever 1: se ainda vai ser preciso dps da ft_dup_env - Environment variables
// rever 2: EXPANSÃO DE VARIÁVEIS NO HEREDOC
// rever 3: projetgemos leaks de memoria antes de matar os processos no heredoc (?)

typedef struct s_exec
{
	char			**redir_in;
	char			**redir_out;
	char			**args;
	int				heredoc_pipefd[2];
	int 			nbr_cmds; // pipes - 1
	int				pipe_fd[2];
	int 			in_fd;  // vai ler
	int 			out_fd; // vai escrever
	bool			is_heredoc;
	char 			**envp; // manter a t_env e arranjar uma função
	bool			cmd_invalid;
}					t_exec;

typedef struct s_env
{
	char			*var;
	char			*var_name;
	char			*var_value;
	int				valid;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*content;
	int				type;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// rever: criar uma ft que transforma linked list em char **
typedef struct s_msh
{
	char			*line;
	char			*home;
	char			*pwd;
	t_env			*env;
	t_token			*tokens;
	t_exec			*exec;
	int				exit_status;
}					t_msh;

typedef enum e_temp_op
{
	TEMP_DOLLAR = -1,
	TEMP_PIPE = -2,
	TEMP_IN = -3,
	TEMP_OUT = -4,
}					t_temp_op;

t_msh				*msh(void);

# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "heredoc.h"
# include "parser.h"
# include "signs.h"
# include "utils.h"

#endif
