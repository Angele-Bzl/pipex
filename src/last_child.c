/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 15:49:41 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		outfile;

	cmd_and_flags = ft_split(arg[3], ' ');
	if (!cmd_and_flags)
		close_fd_and_pipe_and_exit(0, pipe_fd, "malloc", 127);
	path_cmd = find_real_cmd(env, cmd_and_flags);

	if (!path_cmd)
	{
		free_all(NULL, NULL, cmd_and_flags, NULL);
		close_fd_and_pipe_and_exit(0, pipe_fd, "command", EXIT_FAILURE);
	}
	if (access(path_cmd, X_OK))
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(0, pipe_fd, "access", 127);
	}
	outfile = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		// printf("path : %s\n", path_cmd);
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		// if (path_cmd)
		// {
		// 	// printf("path still exist\n");
		// 	// printf("path : %s\n", path_cmd);

		// }
		close_fd_and_pipe_and_exit(0, pipe_fd, "fd", EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(0, pipe_fd, "dup2", 127);
	}
	execve(path_cmd, cmd_and_flags, env);
	free_all(NULL, NULL, cmd_and_flags, path_cmd);
	close_fd_and_pipe_and_exit(outfile, pipe_fd, "execve", 127);
}
