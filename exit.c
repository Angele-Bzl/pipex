/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:20 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/04 16:40:48 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_all(char **path, char **path_cmd, char **cmd_and_flags)
{
	int	i;

	if (path)
	{
		i = 0;
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	if (path_cmd)
	{
		i = 0;
		while (path_cmd[i])
		{
			free(path_cmd[i]);
			i++;
		}
		free(path_cmd);
	}
	if (cmd_and_flags)
	{
		i = 0;
		while (cmd_and_flags[i])
		{
			free(cmd_and_flags[i]);
			i++;
		}
		free(cmd_and_flags);
	}
}

void	close_pipe_and_exit(int *pipe_fd, char *message, int fail)
{
	if (message)
		perror(message);
	if (pipe_fd)
	{
		if (pipe_fd[0])
			close(pipe_fd[0]);
		if (pipe_fd[1])
			close(pipe_fd[1]);
	}
	if (fail)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	dup2_failed(int fd, int *pipe_fd, char **cmd_and_flags)
{
	int	i;

	i = 0;
	while(cmd_and_flags[i])
	{
		free(cmd_and_flags[i]);
		i++;
	}
	free(cmd_and_flags);
	close(fd);
	close_pipe_and_exit(pipe_fd, "dup2", 1);
}
