/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/04 14:23:59 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include <string.h>
# include <errno.h>

void	print_error(char *command, char *context, char *error);
char	*get_name(t_list *token);
char	*get_error(void);

#endif
