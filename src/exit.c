/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:20 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 09:36:29 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_all(char **path, char **hyp_path_cmd, char **cmd_and_flags, char *path_cmd)
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
	if (hyp_path_cmd)
	{
		i = 0;
		while (hyp_path_cmd[i])
		{
			free(hyp_path_cmd[i]);
			i++;
		}
		free(hyp_path_cmd);
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
	if (path_cmd)
		free(path_cmd);
}

void	close_fd_and_pipe_and_exit(int fd, int *pipe_fd, char *message, int fail)
{
	if (message)
		perror(message);
	if (fd)
		close(fd);
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
