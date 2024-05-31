/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/30 09:23:09 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONC_H
# define FUNCTIONC_H

# include "structures.h"

void	analyze_input(char *input, t_minishell *shell);

t_token **parsing_hub(char *input);
int	input_manager(char **input);
t_token **token_manager(char *input);

// FREE_ERROR_EXIT
void	free_shell(t_minishell *shell);
void	free_tokens(t_token **tokens);
void	free_array(char **array);

#endif