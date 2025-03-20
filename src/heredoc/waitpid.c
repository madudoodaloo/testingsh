/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:36:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/19 20:50:18 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_waitpid(int pid)
{
    int status;
    
    while(waitpid(pid, &status, 0)) // se waitpid deu errro
    {
        if(errno == EINTR) // se foi syscal error
            continue;
        perror("waitpid");
        msh()->exit = 1; // changed to proper name afterwards
        return;
    }
    if(WIFEXITED(status))
        msh()->exit = WEXITSTATUS(status);
    else if(WIFSIGNALED)
        msh()->exit = 128 + WTERMSIG;
    else
        msh()->exit = 1;
}
