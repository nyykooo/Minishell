/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/23 22:27:59 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONC_H
# define FUNCTIONC_H

# include "structures.h"

void	analyze_input(char *input, t_envvar **envvar_list);

char **parsing_hub(char *input);
int	input_manager(char **input);
char **token_manager(char *input);

#endif