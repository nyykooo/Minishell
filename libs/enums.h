/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:26:29 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/17 17:42:34 by ncampbel         ###   ########.fr       */
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
	N_PIPE = -124,
	N_LRED = -60,
	N_RRED = -62,
};

enum e_types
{
	T_EMPTY = 0,
	T_COMMAND = 1,
	T_ARG = 2,
	T_RTRUNC = 3,
	T_RAPEND = 4,
	T_LTRUNC = 5,
	T_LAPEND = 6,
	T_PIPE = 7,
};

#endif