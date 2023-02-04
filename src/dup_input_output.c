/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:57:01 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 15:26:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include <fcntl.h>
#include <stdlib.h>

static int	get_here_doc(char *limiter);
static char	*get_input(void);
static int	dup_empty_stdin(void);

int	dup_output(char *out_file, bool is_append)
{
	int	fd;

	if (is_append)
		fd = open(out_file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		print_error(out_file, NULL, get_error());
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	dup_input(bool is_here_doc, char **argv)
{
	int	fd;

	if (is_here_doc)
		fd = get_here_doc(ft_strjoin(argv[2], "\n"));
	else
		fd = open(argv[1], O_RDONLY);
	if (fd == -1 && is_here_doc)
	{
		print_error(NULL, "here_doc failed", get_error());
		return (dup_empty_stdin());
	}
	if (fd == -1)
	{
		print_error(argv[1], NULL, get_error());
		return (dup_empty_stdin());
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	get_here_doc(char *limiter)
{
	char	*input;
	int		pipe_fd[2];

	if (limiter == NULL)
		return (-1);
	if (pipe(pipe_fd) == -1)
	{
		free(limiter);
		return (-1);
	}
	input = get_input();
	while (input != NULL && ft_strcmp(limiter, input) != 0)
	{
		ft_putstr_fd(input, pipe_fd[1]);
		free(input);
		input = get_input();
	}
	free(input);
	free(limiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static char	*get_input(void)
{
	ft_printf("> ");
	return (get_next_line(STDIN_FILENO));
}

static int	dup_empty_stdin(void)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		print_error("dup_empty_stdin()", "pipe() failed", get_error());
		return (2);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}
