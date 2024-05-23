/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:11 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/23 22:28:40 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "libft/libft.h" // to include the libft library
# include "functions.h" // to include functions in the project
# include "structures.h" // to include structures in the project
# include <sys/types.h> // to use the MACRO WIFEXITED
# include <sys/wait.h> // to use the MACRO UNTRACED
# include <signal.h> // to use the signal function
# include <errno.h> // to use the errno variable
# include <string.h> // to use the strerror function
# include <fcntl.h> // to use the open function
# include <sys/stat.h> // to use the stat function
# include <dirent.h> // to use the opendir function
# include "enums.h" // to include enums in the project

#endif