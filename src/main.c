/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:47:32 by vfries            #+#    #+#             */
/*   Updated: 2023/02/13 01:21:53 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "error.h"
#include "dup_input_output.h"
#include "execution.h"

static int	check_input(int argc, char **argv, bool *is_here_doc);

int	main(int argc, char **argv, char **envp)
{
	t_list	*tokens;
	int		exit_code;
	int		dup_input_ret;
	bool	is_here_doc;

	if (check_input(argc, argv, &is_here_doc))
		return (0);
	tokens = get_tokens(argv, envp, is_here_doc);
	if (tokens == NULL)
	{
		print_error(NULL, "Failed to malloc tokens", get_error());
		return (1);
	}
	dup_input_ret = dup_input(is_here_doc, argv);
	if (dup_input_ret == 1)
		ft_lst_get_next_free_current(&tokens, &free_token);
	if (dup_input_ret != 2)
		exit_code = execute_commands(tokens, argv[argc - 1], envp, is_here_doc);
	else
		exit_code = 2;
	ft_lstclear(&tokens, &free_token);
	return (exit_code);
}

static int	check_input(int argc, char **argv, bool *is_here_doc)
{
	if (argc < 2)
		*is_here_doc = false;
	else
		*is_here_doc = ft_strcmp(argv[1], "here_doc") == 0;
	if (*is_here_doc && argc < 6)
	{
		ft_putstr_fd("Need 5 arguments\n", STDERR_FILENO);
		ft_putstr_fd("./pipex here_doc LIMITER CMD1 CMD2 OUT_FILE\n",
			STDERR_FILENO);
		ft_putstr_fd("<< LIMITER CMD1 | CMD2 > OUT_FILE>\n", STDERR_FILENO);
		return (1);
	}
	else if (argc < 5)
	{
		ft_putstr_fd("Need 4 arguments\n./pipex IN_FILE CMD1 CMD2 OUT_FILE\n",
			STDERR_FILENO);
		ft_putstr_fd("< IN_FILE CMD1 | CMD2 > OUT_FILE>\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
