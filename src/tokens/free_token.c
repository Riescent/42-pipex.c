/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:03:19 by vfries            #+#    #+#             */
/*   Updated: 2023/02/13 00:44:49 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

void	free_token(void	*token_void)
{
	t_token	*token;

	if (token_void == NULL)
		return ;
	token = token_void;
	ft_free_split(token->args);
	free(token->path);
	free(token);
}
