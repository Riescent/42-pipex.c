/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:14:48 by vfries            #+#    #+#             */
/*   Updated: 2023/02/13 00:13:06 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "error.h"
#include "dup_input_output.h"
#include <stdlib.h>
#include <sys/wait.h>

static int		execute_pipes(t_list *tokens, char *out_file, char **envp,
					bool is_append);
static int		execute_command_no_pipe(t_token *command, char **envp);
static pid_t	execute_piped_command(t_token *command, char **envp);
static void		run_command(t_token *command, char **envp);

int	execute_commands(t_list *tokens, char *out_file, char **envp,
		bool is_append)
{
	int		tmp;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(execute_pipes(tokens, out_file, envp, is_append));
	waitpid(pid, &tmp, 0);
	return (WEXITSTATUS(tmp));
}

static int	execute_pipes(t_list *tokens, char *out_file, char **envp,
				bool is_append)
{
	int		ret;
	pid_t	pid;

	if (tokens->next == NULL)
	{
		if (dup_output(out_file, is_append))
			return (1);
		else
			return (execute_command_no_pipe(tokens->content, envp));
	}
	pid = execute_piped_command(tokens->content, envp);
	ret = execute_pipes(tokens->next, out_file, envp, is_append);
	close(STDIN_FILENO);
	if (pid != -1)
		waitpid(pid, NULL, 0);
	return (ret);
}

static int	execute_command_no_pipe(t_token *command, char **envp)
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
		run_command(command, envp);
	waitpid(pid, &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}

static pid_t	execute_piped_command(t_token *command, char **envp)
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
		run_command(command, envp);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (pid);
}

static void	run_command(t_token *command, char **envp)
{
	bool	is_command;

	execve(command->path, command->args, envp);
	is_command = ft_strrchr(command->args[0], '/') == NULL;
	if (is_command)
	{
		print_error(command->args[0], NULL, "command not found");
		exit(127);
	}
	if (access(command->path, X_OK))
	{
		print_error(command->path, NULL, get_error());
		exit(126);
	}
	print_error(command->path, NULL, get_error());
	exit(-1);
}
