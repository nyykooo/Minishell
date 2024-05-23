/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:43:58 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/23 13:59:14 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef	struct s_envvar
{
	char *content;
	struct s_envvar *next;
	struct s_envvar *prev;	
} t_envvar;

typedef struct s_token
{
	char *argument;
	int	cmd;
} t_token;


typedef struct s_minishell
{
	char		*input;
	int			n_cmd;
	t_envvar	*envvars;
	t_token		**tokens;
} t_minishell;


#endif