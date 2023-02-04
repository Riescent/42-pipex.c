/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:41 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 13:07:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "libft.h"

typedef struct s_token
{
	char	*path;
	char	**args;
}	t_token;

void	free_token(void	*token_void);

char	**get_args(char *arg);

int		get_path(t_token *token, char **paths);

t_list	*get_tokens(char **argv, char **envp);

#endif
