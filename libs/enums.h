/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:26:29 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/13 11:30:19 by ncampbel         ###   ########.fr       */
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

enum e_types
{
	T_COMMAND = 0,
	T_ARG = 1,
	T_PIPE = 2,
	T_REDIRECT = 3,
};

#endif