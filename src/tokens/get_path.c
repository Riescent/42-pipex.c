/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:57:18 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 13:06:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

static int	get_absolute_path(t_token *token, char **paths);

int	get_path(t_token *token, char **paths)
{
	if (paths == NULL)
	{
		token->path = ft_strdup(token->args[0]);
		return (token->path == NULL);
	}
	if (get_absolute_path(token, paths))
		return (1);
	if (token->path != NULL)
		return (0);
	token->path = ft_strdup(token->args[0]);
	return (token->path == NULL);
}

static int	get_absolute_path(t_token *token, char **paths)
{
	char	*join[3];
	int		i;

	join[1] = token->args[0];
	join[2] = NULL;
	i = 0;
	while (paths[i] != NULL)
	{
		join[0] = paths[i];
		token->path = ft_join_strs(join, "/");
		if (token->path == NULL)
			return (1);
		if (access(token->path, F_OK) == 0)
			return (0);
		free(token->path);
		i++;
	}
	token->path = NULL;
	return (0);
}
