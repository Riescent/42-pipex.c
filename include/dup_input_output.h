/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_input_output.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:48:12 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 15:06:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUP_INPUT_OUTPUT_H
# define DUP_INPUT_OUTPUT_H

# include <stdbool.h>

int	dup_output(char *out_file, bool is_append);
int	dup_input(bool is_here_doc, char **argv);

#endif
