/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:14:48 by vfries            #+#    #+#             */
/*   Updated: 2023/02/13 23:04:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "error.h"
#include "dup_input_output.h"
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_tokens
{
	t_list	*all_tokens;
	t_list	*current_tokens;
}	t_tokens;

static int		execute_pipes(t_tokens tokens, char *out_file, char **envp,
					bool is_append);
static int		execute_command_no_pipe(t_tokens tokens, char **envp);
static pid_t	execute_piped_command(t_tokens tokens, char **envp);
static void		run_command(t_tokens tokens, char **envp);

int	execute_commands(t_list *tokens, char *out_file, char **envp,
		bool is_append)
{
	int			tmp;
	pid_t		pid;
	t_tokens	tokens_param;

	tokens_param.all_tokens = tokens;
	tokens_param.current_tokens = tokens;
	pid = fork();
	if (pid == 0)
	{
		tmp = execute_pipes(tokens_param, out_file, envp, is_append);
		ft_lstclear(&tokens, &free_token);
		exit(tmp);
	}
	waitpid(pid, &tmp, 0);
	return (WEXITSTATUS(tmp));
}

static int	execute_pipes(t_tokens tokens, char *out_file, char **envp,
				bool is_append)
{
	int		ret;
	pid_t	pid;

	if (tokens.current_tokens->next == NULL)
	{
		if (dup_output(out_file, is_append))
			return (1);
		else
			return (execute_command_no_pipe(tokens,
					envp));
	}
	pid = execute_piped_command(tokens, envp);
	tokens.current_tokens = tokens.current_tokens->next;
	ret = execute_pipes(tokens, out_file, envp, is_append);
	close(STDIN_FILENO);
	if (pid != -1)
		waitpid(pid, NULL, 0);
	return (ret);
}

static int	execute_command_no_pipe(t_tokens tokens, char **envp)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork() failed", NULL, get_error());
		return (-1);
	}
	if (pid == 0)
		run_command(tokens, envp);
	waitpid(pid, &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}

static pid_t	execute_piped_command(t_tokens tokens, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		print_error("pipe() failed", NULL, get_error());
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		print_error("fork() failed", NULL, get_error());
	}
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		run_command(tokens, envp);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (pid);
}

static void	run_command(t_tokens tokens, char **envp)
{
	int				exit_code;
	const t_token	*command = tokens.current_tokens->content;

	execve(command->path, command->args, envp);
	exit_code = execution_error(command);
	ft_lstclear(&tokens.all_tokens, &free_token);
	exit(exit_code);
}
