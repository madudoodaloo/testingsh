/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:13:48 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/20 01:29:31 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_set_temp_filename(char *filename)
{
	static char	*temp_filename = NULL;

	if (temp_filename)
		free(temp_filename);
	temp_filename = filename;
}

char	*generate_temp_filename(void)
{
	char		*filename;
	char		counter_str[20];
	static int	counter;

	counter = 0;
	counter++;
	int_to_str(counter, counter_str);
	filename = safe_malloc(256);
	if (!filename)
		return (NULL);
	ft_strcpy(filename, "/tmp/minishell_heredoc_");
	ft_strcat(filename, counter_str);
	return (filename);
}

int	create_temp_file(char *temp_filename)
{
	int	fd;

	fd = open(temp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error: Failed to create temporary file\n", 38);
		free(temp_filename);
		exit(1);
	}
	return (fd);
}

void	redirect_temp_file_to_stdin(char *temp_filename)
{
	int	fd;

	fd = open(temp_filename, O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error: Failed to open temporary file\n", 37);
		unlink(temp_filename);
		free(temp_filename);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_heredoc(t_exec * exec, char *delimiter)
{
	int		fd;
	char	*temp_filename;

	setup_signals();
	data->is_heredoc = 1;
	temp_filename = generate_temp_filename();
	if (!temp_filename)
	{
		write(STDERR_FILENO, "Error: Failed to allocate memory\n", 33);
		exit(1);
	}
	signal_handler_set_temp_filename(temp_filename);
	fd = create_temp_file(temp_filename);
	read_until_delimiter(fd, delimiter);
	close(fd);
	redirect_temp_file_to_stdin(temp_filename);
	unlink(temp_filename);
	free(temp_filename);
	data->is_heredoc = 0;
	setup_signals();
}
