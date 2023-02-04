/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:22:54 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:11:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_io.h"
#include <unistd.h>

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	write(STDOUT_FD, s, ft_strlen(s));
}
