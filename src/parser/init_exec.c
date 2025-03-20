/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:08:55 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/19 21:11:26 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//MARIO!!!!!
// rever: NOTA EXEC
// tenho de dar handle do cenário em que nãao há pipes - o exec tem de a mm mandar malloc the 1
int	count_cmds(t_token *tokens)
{
	int nbr_cmds;
	nbr_cmds = 1;
	if (!tokens)
		return (-1);
	while (tokens)
	{
		if (tokens->type == PIPE)
			nbr_cmds++;
		tokens = tokens->next;
	}
	return (nbr_cmds);
}

int	strlen_args(char **args)
{
	int i = 0;
	if (args)
	{
		while (args[i])
			i++;
		return i;
	}
}

char **add_prefix(t_token *token, char **args)
{
	char *str;
	char **ret;

	if (token->type == HERE_DOC || token->type == R_APP)
		str = ft_strjoin("APP", token->next->content);
	else
		str = ft_strjoin("STD", token->next->content);
	ret = add_to_matrix(str, args);
	free(str);
	return (ret);
}

char **add_to_matrix(char *content, char **args)
{
	int i;
	int new_i;
	char **new;
	i = 0;
	new_i = 0;
	if (!args)
	{
		new = safe_malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(content);
		new[1] = NULL;
	}
	else
	{
		i = strlen_args(args) + 1; //+1 is for the new str
		new = safe_malloc(sizeof(char *) * (i + 1)); //+1 is for null
		while (args[new_i])
			new[new_i] = ft_strdup(args[new_i++]);
		new[new_i] = ft_strdup(content);
		new[++new_i] = NULL;
	}
	free_matrix(args);
	return (new);
}

void tokens_to_exec(t_token *token, t_exec *exec, int nbr_cmds)
{
	int i;

	i = 0;
	while (token)
	{
		exec[i].nbr_cmds = nbr_cmds;
		if (token->type == CMD)
				exec[i].args = add_to_matrix(token->content, exec[i].args);
		else if (token->type == R_APP || token->type == R_OUT)
			exec[i].redir_out = add_prefix(token, exec[i].args);
		else if (token->type == R_IN || token->type == HERE_DOC)
			exec[i].redir_in = add_prefix(token, exec[i].args);
		if (token->type == CMD)
			token = token->next;
		else if (token->type == PIPE)
		{
			token = token->next;
			i++;
		}
		else
			token = token->next->next;
	}
}


t_exec *init_exec(t_token *tokens)
{
	t_exec	*exec;
	int nbr_cmds;

	if (!tokens)
		return (NULL);
	nbr_cmds = count_cmds(tokens); //CHECK IF SYNTAX IS TRULLY WORKING
	exec = (t_exec *)safe_malloc(sizeof(t_exec) * nbr_cmds);
	tokens_to_exec(tokens, exec, nbr_cmds);
	return (exec);
}


/* rever */
int	set_exec(void)
{
	t_token *tokens;

	tokens = msh()->tokens;
	msh()->exec = init_exec(tokens);
	if (msh()->exec == NULL)
		return (0);
	return (1);
}


