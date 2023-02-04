/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 01:41:37 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 11:52:53 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_args(char *arg);
static char	*add_word(char *arg, char **ret, int ret_index);
static int	get_word_size(char *arg);

char	**get_args(char *arg)
{
	char	**ret;
	int		arg_count;
	int		i;

	arg_count = count_args(arg);
	ret = malloc(sizeof(char *) * (arg_count + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (++i < arg_count)
	{
		arg = ft_skip_char(arg, ' ');
		arg = add_word(arg, ret, i);
		if (ret[i] == NULL)
		{
			ft_free_split(ret);
			return (NULL);
		}
	}
	ret[arg_count] = NULL;
	return (ret);
}

static int	count_args(char *arg)
{
	int	count;

	count = 0;
	while (*arg)
	{
		arg = ft_skip_char(arg, ' ');
		if (*arg)
			count++;
		arg += get_word_size(arg);
	}
	return (count);
}

static char	*add_word(char *arg, char **ret, int ret_index)
{
	int		size;
	char	*new_word;

	size = get_word_size(arg);
	new_word = malloc(sizeof(char) * ++size);
	if (new_word != NULL)
		ft_strlcpy(new_word, arg, size);
	ret[ret_index] = new_word;
	return (arg + size - 1);
}

static int	get_word_size(char *arg)
{
	int		size;
	bool	is_in_double_quote;
	bool	is_in_simple_quote;

	size = 0;
	is_in_double_quote = false;
	is_in_simple_quote = false;
	while (arg[size] != '\0')
	{
		if (arg[size] == '\"' && is_in_simple_quote == false)
			ft_reverse_bool(&is_in_double_quote);
		else if (arg[size] == '\'' && is_in_double_quote == false)
			ft_reverse_bool(&is_in_simple_quote);
		else if (arg[size] == ' '
			&& is_in_double_quote == false && is_in_simple_quote == false)
			break ;
		size++;
	}
	return (size);
}
