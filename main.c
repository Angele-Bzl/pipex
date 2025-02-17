/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/17 09:12:13 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	pipe_fd[2];
	pid_t	pid;
	char **arguments;
	int	i;

	if (ac != 4)
	{
		return (1);
	}
    if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
	{
		perror("fork");
        exit(EXIT_FAILURE);
    }
	if (pid == 0)
	{
		process_is_child(pipe_fd);
		// close(pipe_fd[1]);
		// while (read(pipe_fd[0], &buf, 1))
		// 	write(1, &buf, 1);
		// close(pipe_fd[0]);
        // exit(EXIT_SUCCESS);
	}
	else
	{
		arguments = malloc(sizeof(char*) * ac - 1);
		i = 0;
		while (i < ac - 1)
		{
			arguments[i] = ft_strdup(av[i + 1]);
			i++;
		}
		process_is_parent(pipe_fd, arguments);
		// close(pipe_fd[0]);
		// write(pipe_fd[1], av[1], strlen(av[1]));
		// wait(NULL);
        // exit(EXIT_SUCCESS);
	}
	return (0);
}
