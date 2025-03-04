/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/04 10:53:00 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		file_out;

	cmd_and_flags = ft_split(arg[3], ' ');
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		perror("command failed");
		exit(EXIT_FAILURE);
	}
	if (access(path_cmd, X_OK))
	{
		free(path_cmd);
		perror("access failed");
		exit(EXIT_FAILURE);
	}
	file_out = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (file_out == -1)
	{
		perror("open pid_2");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup pid_2");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(file_out, STDOUT_FILENO) == -1)
	{
		perror("dup pid_2");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	execve(path_cmd, cmd_and_flags, env);
	perror("(last child) execve failed");
}
