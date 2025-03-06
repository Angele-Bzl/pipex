/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/06 14:51:39 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		infile;

	close(pipe_fd[0]);
	infile = open(arg[1], O_RDONLY);
	if (infile == -1)
		close_all_exit(infile, pipe_fd, arg[1], EXIT_FAILURE);
	if (ft_strlen(arg[2]) == 0)
		close_all_exit(infile, pipe_fd, "empty", EXIT_FAILURE);
	cmd_and_flags = ft_split(arg[2], ' ');
	if (!cmd_and_flags)
		close_all_exit(infile, pipe_fd, "malloc", EXIT_FAILURE);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		free_all(NULL, NULL, cmd_and_flags, NULL);
		ft_printf_err("%s: command not found\n", arg[2]);
		close_all_exit(infile, pipe_fd, NULL, EXIT_FAILURE);
	}
	manage_access(cmd_and_flags, path_cmd, infile, pipe_fd);
	first_dup(infile, pipe_fd, cmd_and_flags, path_cmd);

	close(pipe_fd[1]);
	close(infile);
	close(0);

	execve(path_cmd, cmd_and_flags, env);
	free_all(NULL, NULL, cmd_and_flags, path_cmd);
	close_all_exit(infile, pipe_fd, "execve", EXIT_FAILURE);
}
