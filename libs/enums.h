/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:26:29 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/26 13:28:00 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_negative_markers
{
	N_SPACE = -32,
	N_DQUOTE = -34,
	N_SQUOTE = -39,
	N_EQUAL = -61,
	N_DOLLAR = -36,
};

enum e_markers
{
	PIPE = 124,
	LRED = 60,
	RRED = 62,
	DQUOTE = 34,
	SQUOTE = 39,
};

enum e_types
{
	T_EMPTY = 0,
	T_COMMAND,
	T_ARG,
	T_EQUAL,
	T_RTRUNC,
	T_RAPEND,
	T_LTRUNC,
	T_LAPEND,
	T_PIPE
};

#endif