/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:47:32 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 13:10:32 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*tokens;
	// int		exit_code;

	if (argc != 5)
	{
		ft_printf("Need 4 arguments\n./pipex IN_FILE CMD1 CMD2 OUT_FILE\n");
		ft_printf("< IN_FILE CMD1 | CMD2 > OUT_FILE>\n");
		return (1);
	}
	tokens = get_tokens(argv, envp);
	int	i = 0;
	for (t_list *cursor = tokens; cursor != NULL; cursor = cursor->next)
	{
		ft_printf("CMD%d path -> %s\n", i, ((t_token *)cursor->content)->path);
		if ((t_token *)cursor->content)
		{
			ft_printf("CMD%d args -> {", i);
			for (int j = 0; ((t_token *)cursor->content)->args[j]; j++)
				ft_printf("%s, ", ((t_token *)cursor->content)->args[j]);
			ft_printf("(null)}\n");
		}
		else
			ft_printf("CMD%d args -> NULL", i);
		i++;
	}
	// exit_code = execute_command(tokens, argv[1], argv[argc - 1]);
	ft_lstclear(&tokens, &free_token);
	// return (exit_code);
}
