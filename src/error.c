/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/14 01:37:18 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <string.h>
#include <errno.h>

void	print_error(char *command, char *context, char *error)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (command != NULL)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (context != NULL)
	{
		ft_putstr_fd(context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error != NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

char	*get_error(void)
{
	return (strerror(errno));
}

int	execution_error(const t_token *command)
{
	if (command->args[0] == NULL)
	{
		print_error(NULL, NULL, "permission denied:");
		return (127);
	}
	else if (ft_strchr(command->args[0], '/') == NULL)
	{
		print_error(command->args[0], NULL, "command not found");
		return (127);
	}
	else if (access(command->path, X_OK))
	{
		print_error(command->path, NULL, get_error());
		return (126);
	}
	else
	{
		print_error(command->path, NULL, get_error());
		return (-1);
	}
}
