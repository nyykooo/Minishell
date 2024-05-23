/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:11 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/23 11:03:59 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/wait.h> // to use the MACRO UNTRACED

typedef struct s_envvar
{
	char			*content;
	struct s_envvar	*next;
	struct s_envvar	*prev;	
}	t_envvar;

typedef struct s_token
{
	char	*input;
	int		cmd;
}	t_token;

typedef struct s_minishell
{
	t_envvar	*envvars;
	t_token		*parse;
}	t_minishell;

char	**mega_parsing(char *input);
void	analyze_input(char *input, t_envvar **envvar_list);

#endif