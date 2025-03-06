/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/06 10:06:59 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		fd;

	close(pipe_fd[0]);
	fd = open(arg[1], O_RDONLY);
	if (fd == -1)
		close_fd_and_pipe_and_exit(fd, pipe_fd, "open", EXIT_FAILURE);
	if (ft_strlen(arg[2]) == 0)
		close_fd_and_pipe_and_exit(fd, pipe_fd, "command", EXIT_FAILURE);
	cmd_and_flags = ft_split(arg[2], ' ');
	if (!cmd_and_flags)
		close_fd_and_pipe_and_exit(fd, pipe_fd, "malloc", EXIT_FAILURE);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		free_all(NULL, NULL, cmd_and_flags, NULL);
		close_fd_and_pipe_and_exit(fd, pipe_fd, "command", EXIT_FAILURE);
	}
	if (access(path_cmd, X_OK))
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(0, pipe_fd, "access", EXIT_FAILURE);
	}
	manage_deviate_first(fd, pipe_fd, cmd_and_flags, path_cmd);
	execve(path_cmd, cmd_and_flags, env);
	free_all(NULL, NULL, cmd_and_flags, path_cmd);
	close_fd_and_pipe_and_exit(fd, pipe_fd, "execve", EXIT_FAILURE);
}
