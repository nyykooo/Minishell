/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/05 16:00:47 by brunhenr         ###   ########.fr       */
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

// BUILTINS
void	handle_cd(t_token **tokens, t_minishell *shell);

//ENVVAR_FTS
t_var	*find_envvar(t_var *envvar_list, char *name);
void	remove_envvar(t_var **envvar_list, t_var *envvar);
void	set_envvar(t_var **envvar_list, char *name, char *value);
char	*get_value(t_var *envvar_list, char *name);

#endif