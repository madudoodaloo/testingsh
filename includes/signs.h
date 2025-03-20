/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:26:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/20 01:24:24 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNS_H
# define SIGNS_H

# include "../includes/minishell.h"

/* signals.c */
void    init_signals(void);
void	handle_sigint(int sig);
void    set_parent_signals(void);
void    set_signals_to_ignore(void);
void    set_signals_to_default(void);

/*signals1.c*/
void	signal_handler(t_exec * exec, int signum);
void	handle_signals_and_cleanup(t_exec * exec);
void	setup_signals(void);
void	restore_parent_signals(void);
void	handle_child_exit_status(int status);

/*signals2.c*/
void	handle_ctrl_d(char *line);
//void	handle_sigint(t_exec * exec, char *temp_filename);
void	handle_sigquit(t_exec * exec);
void	handle_general_signals(t_exec *exec);

#endif
