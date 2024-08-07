/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:10:30 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/07 17:47:16 by ncampbel         ###   ########.fr       */
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
	bool			expanded;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_token
{
	char				*content;
	bool				dq;
	bool				sq;
	bool				dol;
	bool				equal;
	bool				expanded;
	enum e_types		type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_cmd
{
	char				*cmd;
	t_arg				*arguments;
	char				*path;
	char				*redirect_in;
	char				*redirect_out;
	char				*redirect_append;
	bool				exec;
	bool				pipe;
	bool				rappend;
	bool				lappend;
	int					here_doc_fd;
	bool				rtrunc;
	bool				input_file;
	enum e_types		type;
	struct s_minishell	*shell;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}	t_cmd;

typedef struct s_minishell
{
	char		*input;
	char		*error_msg;
	int			n_cmd;
	int			n_pipe;
	int			exit_status;
	t_var		*envvars;
	t_cmd		*commands;
	t_token		*tokens;
}	t_minishell;

#endif