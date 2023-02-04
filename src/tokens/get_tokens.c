/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:00 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 13:03:22 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

static int		get_paths(char ***paths, char **envp);
static int		add_token(t_list **tokens, char *command, char **paths);
static t_token	*init_token(char *command, char **paths);

t_list	*get_tokens(char **argv, char **envp)
{
	t_list	*tokens;
	int		i;
	char	**paths;

	if (get_paths(&paths, envp))
		return (NULL);
	tokens = NULL;
	i = 2;
	while (argv[i + 1] != NULL)
	{
		if (add_token(&tokens, argv[i], paths))
		{
			ft_lstclear(&tokens, &free_token);
			break ;
		}
		i++;
	}
	ft_free_split(paths);
	return (ft_lst_reverse(&tokens));
}

static int	get_paths(char ***paths, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
	{
		*paths = NULL;
		return (0);
	}
	*paths = ft_split(envp[i], ':');
	if (*paths == NULL)
		return (1);
	return (0);
}

static int	add_token(t_list **tokens, char *command, char **paths)
{
	t_token	*new_token;
	t_list	*new_node;

	new_token = init_token(command, paths);
	new_node = ft_lstnew(new_token);
	if (new_node == NULL || new_token == NULL)
	{
		free(new_token);
		free(new_node);
		return (1);
	}
	ft_lstadd_front(tokens, new_node);
	return (0);
}

static t_token	*init_token(char *command, char **paths)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->args = get_args(command);
	if (new_token->args == NULL)
	{
		free(new_token);
		return (NULL);
	}
	if (get_path(new_token, paths))
	{
		ft_free_split(new_token->args);
		free(new_token);
		return (NULL);
	}
	return (new_token);
}
