/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:43:58 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/24 10:36:08 by ncampbel         ###   ########.fr       */
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
	bool			dq;	// if the argument has a double quote
	bool			sq; // if the argument has a single quote
	bool			dol; // if the argument has a dollar sign
	bool			equal; // if the argument has an equal sign
	bool			expanded; // if the argument has been expanded (no space between prev and current argument)
	struct s_arg	*next;
	struct s_arg	*prev;
} t_arg;


// use this struct to store the tokens and differ them by type to implement yuris function

typedef struct s_token
{
	char				*content; // token content
	bool				dq;	// if the argument has a double quote
	bool				sq; // if the argument has a single quote
	bool				dol; // if the argument has a dollar sign
	bool				equal; // if the argument has an equal sign
	bool				expanded; // if the argument has been expanded (no space between prev and current argument)
	enum e_types		type; //e_num type
	struct s_token 		*next;
	struct s_token 		*prev;
} t_token;


// pensar na ideia de incluir o shell dentro do cmd para facilitar a expansão de variaveis e argumentos do comando

typedef struct s_cmd
{
	char				*cmd; // command
	t_arg				*arguments; // array of arguments
	char				*path; // path to the command
	bool				exec; // if the command is an executable
	bool				pipe; // if the command is a pipe
	bool				rappend; // if the command is a right append
	bool				lappend; // if the command is a left append
	bool				rtrunc; // if the command is a right trunc
	bool				ltrunc; // if the command is a left trunc
	enum e_types		type; // type of command
	struct s_minishell	*shell; // pointer to shell structure
	struct s_cmd		*next;
	struct s_cmd		*prev; // prev and next will help to deal with pipes and redirects, aswell it will allow us to expand things correctly
} t_cmd;


// tokens -> cmds -> args
// t_cmd->cmd = cmd / t_cmd->args = until next cmd

typedef struct s_minishell
{
	char		*input;
	int			n_cmd; // number of commands
	int			n_pipe; // number of pipes
	int			exit_status; // status of the last command
	t_var		*envvars;
	t_cmd		*commands; // array of commands | work with linked list is easier then arrays (insert and expand commands)
	t_token		*tokens; // whole input tokenized
} t_minishell;

#endif