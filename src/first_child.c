/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 16:43:41 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		fd;

	if (close(pipe_fd[0]) == -1)
	{
		perror("(first child) pipe");
		exit(EXIT_FAILURE);
	}
	fd = open(arg[1], O_RDONLY);
	if (fd == -1)
	{
		perror("(first child) open failed");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}


	cmd_and_flags = ft_split(arg[2], ' ');
	path_cmd = ft_strjoin(find_real_cmd(env, cmd_and_flags), "\0");
	
	ft_printf_err("path : %s\n", path_cmd);

	if (!path_cmd)
	{
		close(fd);
		perror("(first child) command failed");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup pid_1");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup pid_1");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	execve(path_cmd, cmd_and_flags, env);
    perror("(first child) execve failed");
}
