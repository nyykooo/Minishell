/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:43:58 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/05 15:01:27 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef	struct s_var
{
	char *content;
	bool env;
	struct s_var *next;
	struct s_var *prev;	
} t_var;

typedef struct s_token
{
	char	**argument;
	char	*cmd;
} t_token;


typedef struct s_minishell
{
	char		*input;
	int			n_cmd;
	t_var		*envvars;
	t_token		**tokens;
} t_minishell;


#endif