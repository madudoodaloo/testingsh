/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:19:12 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/20 02:14:26 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    clean_cmdline(void)
{
	t_msh	*m;

	m = msh();
	if (!m)
		return ;
	if (m->line)
		free(m->line);
	if (m->tokens)
	{
		free_tokens(m->tokens);
		m->tokens = NULL;
	}
	if (m->exec)
	{
		free_exec(m->exec);
		m->exec = NULL;
	}
}

void	msh_loop(char **envp)
{
    init_all(envp);
    while (1)
    {
        msh()->line = readline("minishell$");
        if (!msh()->line)
        {
            ft_put_str_fd("exit\n", 2);
            break ;
        }
        if (msh()->line && *msh()->line)
        {
            add_history(msh()->line);
            if (parser())
                   printf("siga crlh\n");//start_execution();
            else
                msh()->exit_status = 2;
        }
        clean_cmdline();
    }
    free_and_exit();
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
	{
		init_signals();
		msh_loop(envp);
	}
	else
		printf("Cmdline to launch: ./minishell\n");
	return (0);
}
