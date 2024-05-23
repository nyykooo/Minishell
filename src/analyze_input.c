#include "../libs/headers.h"
#include <string.h>
#include <stdlib.h>

static char	*get_command_path(char	*command)
{
	char	*path;
	char	**dirs;
	char	*possible_path;
	int		i;

	path = getenv("PATH");
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		possible_path = malloc(strlen(dirs[i]) + strlen(command) + 2);
		strcpy(possible_path, dirs[i]);
		strcat(possible_path, "/");
		strcat(possible_path, command);
		if (access(possible_path, X_OK) == 0)
		{
			free(dirs);
			return (possible_path);
		}
		free(possible_path);
		i++;
	}
	free(dirs);
	return (NULL);
}

static void	handle_cd(char **commands)
{
	if (chdir(commands[1]) == -1)
		write (2, "cd: no such file or directory\n", 30);
}

static void	handle_exit(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		free(commands[i++]);
	free(commands);
	exit(0);
}

static void	handle_command(char **commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		command_path = get_command_path(commands[0]);
		if (command_path == NULL)
		{
			perror ("minishell");
			exit (EXIT_FAILURE);
		}
		if (execve(command_path, commands, NULL) == -1)
		{
			perror("minishell");
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror ("minishell");
	else
		waitpid (pid, &status, WUNTRACED);
}

void	analyze_input(char *input)
{
	char	**commands;
	char *temp;
	int		i;

	i = 0;
	if (!input)
		return ;
	temp = input;
	// commands = ft_split(input, ' ');
	commands = parsing_hub(temp);
	if (ft_strcmp(commands[0], "cd") == 0)
		handle_cd(commands);
	else if (ft_strcmp(commands[0], "exit") == 0)
		handle_exit(commands);
	else if (commands[0] != NULL)
		handle_command(commands);
	while (commands[i] != NULL)
		free(commands[i++]);
	free(commands);
	return ;
}
