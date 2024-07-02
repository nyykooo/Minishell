/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:56:44 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/28 17:10:51 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// use function to open file and later close it
// O_WRONLY: write only
// O_CREAT: create file if it doesn't exist (feature to include)
// O_TRUNC: truncate file to 0 length (> or < operator)
// O_APPEND: append to file (>> operator)
// which permissions should be given to the file? (0777 -> octal to represent permissions, in decimal 511)

int main(int ac, char **av, char **envp)
{
	int fd;
	int	i;

	if (ac != 2)
		return (0);
	if (strcmp(av[1], ">") == 0 || strcmp(av[1], "<") == 0)
		fd = open("redirect.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (strcmp(av[1], ">>") == 0)
		fd = open("redirect.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		return (0);
	dup2(fd, 1);
	close(fd);
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}