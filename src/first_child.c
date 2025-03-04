/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/04 16:44:46 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		fd;
	int		i;

	if (close(pipe_fd[0]) == -1)
		close_pipe_and_exit(pipe_fd, "pipe", 1);
	fd = open(arg[1], O_RDONLY);
	if (fd == -1)
		close_pipe_and_exit(pipe_fd, "open", 1);
	cmd_and_flags = ft_split(arg[2], ' ');
	if (!cmd_and_flags)
		close_pipe_and_exit(pipe_fd, "command", 1);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		i = 0;
		while(cmd_and_flags[i])
		{
			free(cmd_and_flags[i]);
			i++;
		}
		free(cmd_and_flags);
		close(fd);
		close_pipe_and_exit(pipe_fd, "command", 1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		dup2_failed(fd, pipe_fd, cmd_and_flags);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		dup2_failed(fd, pipe_fd, cmd_and_flags);
	execve(path_cmd, cmd_and_flags, env);
	/*il faut free et close et tout aussi*/
    perror("(first child) execve failed");
}
