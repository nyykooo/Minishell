/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:43:58 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 14:02:52 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_var
{
	char			*content;
	bool			env;
	bool			exp;
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;	
}	t_var;

typedef struct s_arg
{
	char			*arg;
	bool			dq;
	bool			sq;
	bool			dol;
	bool			equal;
	struct s_arg	*next;
}	t_arg;


typedef struct s_token
{
	char	*content; // token content
	int		type; //e_num type
} t_token;


typedef struct s_cmd
{
	char	*cmd; // command
	t_arg	**args; // array of arguments
	char	**(*make_array)(t_cmd *); // function to turn everything in a char ** to the execve 2nd argument
	bool	exec; // if the command is an executable
	bool	pipe; // if the command is a pipe
	bool	redirect; // if the command is a redirect
} t_cmd;


// tokens -> cmds -> args
// t_cmd->cmd = cmd / t_cmd->args = until next cmd

typedef struct s_minishell
{
	char		*input;
	int			n_cmd; // number of commands
	t_var		*envvars;
	t_cmd		**commands; // array of commands
	t_token		**tokens; // whole input tokenized
} t_minishell;

#endif