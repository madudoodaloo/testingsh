/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:29:52 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/20 02:23:10 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int prep_in_redir(t_exec *exec)
{
    int i;

    i = 0;
    while(i < exec[i].nbr_cmds) // value might be somewhere else
    {
        if(exec[i].redir_in != NULL)
        {
            //is_final_heredoc
            doc_loop(exec[i].redir_in, exec, i);
        }
        i++;
    }
    i = 0;
    while(i < exec[i].nbr_cmds)
    {
        open_infile_loop(, exec, /*index*/);
    }
}

int doc_loop (char **in_redirs, t_exec *exec, int k) // recebe da prep_in_redir e i de index de onde estou no arr do exec e k para char **
{
    int i = 0;
    while(in_redirs[i] != NULL)
    {
        if(!ft_strncmp(in_redirs[i], "app:", 4)) // append flag
        {
            safe_close(exec[k].heredoc_pipefd[0]); // qual fd
           if(run_doc(in_redirs[i] + 4, exec, k) < 0)
            return (-1);
        }
        i++;
    }
    if(!is_final_heredoc())
        close(exec[k].heredoc_pipefd[0]);
}

int open_infile_loop(char **in_redirs, t_exec *exec, int k)
{
    int i;
    int fd;

    i = 0;
    while(in_redirs[i] != NULL)
    {
        if (ft_strncmp(in_redirs[i], "app:", 4) != 0)
        if(/*return da nova func < 0*/)
            //fd = open(in_redirs[i] + 4, O_RDONLY);
            exec[k]->command_invalid = true;
    }
    if(exec[k].is_heredoc)
    safe_close(exec->in_fd);
}

int is_final_heredoc(char **in_redirs, t_exec *exec, int k)
{
    int i = 0;
    int last_heredoc_index = -1;
    while(in_redirs)

}


// rever : nome de funncao novo :
// 1- if(fd = open(in_redirs[i] + 4, O_RDONLY);)
// 2- verificar se nome esta vazio
// 3- verificar o return do open

// rever : is_final_heredoc -> checks if heredoc is last redir and updates is_heredoc bool
