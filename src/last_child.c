/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 09:53:04 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		file_out;

	cmd_and_flags = ft_split(arg[3], ' ');
	if (!cmd_and_flags)
		close_fd_and_pipe_and_exit(0, pipe_fd, "malloc", 1);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		free_all(NULL, NULL, cmd_and_flags, NULL);
		close_fd_and_pipe_and_exit(0, pipe_fd, "command", 1);
	}
	if (access(path_cmd, X_OK))
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(0, pipe_fd, "access", 1);
	}
	file_out = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(0, pipe_fd, "fd", 1);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(file_out, STDOUT_FILENO) == -1)
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(0, pipe_fd, "dup2", 1);
	}
	execve(path_cmd, cmd_and_flags, env);
	free_all(NULL, NULL, cmd_and_flags, path_cmd);
	close_fd_and_pipe_and_exit(file_out, pipe_fd, "execve", 1);
}
