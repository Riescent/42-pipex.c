/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:47:32 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 14:52:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "error.h"
#include "dup_input_output.h"
#include "execution.h"

///
// static void	print_token(t_list *tokens);///
///

static int	check_input(int argc, char **argv, bool *is_here_doc);

int	main(int argc, char **argv, char **envp)
{
	t_list	*tokens;
	int		exit_code;
	bool	is_here_doc;

	if (check_input(argc, argv, &is_here_doc))
		return (1);
	tokens = get_tokens(argv, envp, is_here_doc);
	if (tokens == NULL)
	{
		print_error(NULL, "Failed to malloc tokens", get_error());
		return (2);
	}
	if (dup_input(is_here_doc, argv))
		ft_lst_get_next_free_current(&tokens, &free_token);
	exit_code = execute_commands(tokens, argv[argc - 1], envp, is_here_doc);
	ft_lstclear(&tokens, &free_token);
	return (exit_code);
}

static int	check_input(int argc, char **argv, bool *is_here_doc)
{
	if (argc < 2)
		*is_here_doc = false;
	else
		*is_here_doc = ft_strcmp(argv[1], "HERE_DOC") == 0;
	if (*is_here_doc && argc < 6)
	{
		ft_printf("Need 5 arguments\n");
		ft_printf("./pipex HERE_DOC LIMITER CMD1 CMD2 OUT_FILE\n");
		ft_printf("<< LIMITER CMD1 | CMD2 > OUT_FILE>\n");
		return (1);
	}
	else if (argc < 5)
	{
		ft_printf("Need 4 arguments\n./pipex IN_FILE CMD1 CMD2 OUT_FILE\n");
		ft_printf("< IN_FILE CMD1 | CMD2 > OUT_FILE>\n");
		return (1);
	}
	return (0);
}



// static void	print_token(t_list *tokens)
// {
// 	int	i = 0;
// 	for (; tokens != NULL; tokens = tokens->next)
// 	{
// 		ft_printf("CMD%d path -> %s\n", i, ((t_token *)tokens->content)->path);
// 		if ((t_token *)tokens->content)
// 		{
// 			ft_printf("CMD%d args -> {", i);
// 			for (int j = 0; ((t_token *)tokens->content)->args[j]; j++)
// 				ft_printf("%s, ", ((t_token *)tokens->content)->args[j]);
// 			ft_printf("(null)}\n");
// 		}
// 		else
// 			ft_printf("CMD%d args -> NULL", i);
// 		i++;
// 	}
// }
