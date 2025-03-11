/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:20 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/10 15:48:38 by abarzila         ###   ########.fr       */
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

static int	start_wait(pid_t pid_1, pid_t pid_2, int *pipe_fd)
{
	int	status;

	if (waitpid(pid_1, &status, 0) == -1)
		close_all(0, pipe_fd, "wait", EXIT_FAILURE);
	if (waitpid(pid_2, &status, 0) == -1)
		close_all(0, pipe_fd, "wait", EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

void	leave_program(pid_t pid_1, pid_t pid_2, int *pipe_fd)
{
	int		exit_status;

	exit_status = start_wait(pid_1, pid_2, pipe_fd);
	close_all(0, pipe_fd, NULL, exit_status);
}
