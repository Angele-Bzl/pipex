/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:20 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/07 11:37:36 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(char **path, char **hyp_path, char **cmd_flag, char *path_cmd)
{
	if (path)
		free_tab(path);
	if (hyp_path)
		free_tab(hyp_path);
	if (cmd_flag)
		free_tab(cmd_flag);
	if (path_cmd)
		free(path_cmd);
}

void	close_all(int fd, int *pipe_fd, char *message, int exit_status)
{
	if (message)
	{
		if (!ft_memcmp(message, "empty", 5))
			ft_putendl_fd("permission denied", STDERR_FILENO);
		else if (!ft_memcmp(message, "malloc", 6))
			ft_putendl_fd("Error\nmalloc failed", STDERR_FILENO);
		else if (!ft_memcmp(message, "execve", 6))
			ft_putendl_fd("Error\nexecve failed", STDERR_FILENO);
		else
			perror(message);
	}
	if (fd)
		close(fd);
	if (pipe_fd)
	{
		if (pipe_fd[0])
			close(pipe_fd[0]);
		if (pipe_fd[1])
			close(pipe_fd[1]);
	}
	exit(exit_status);
}
