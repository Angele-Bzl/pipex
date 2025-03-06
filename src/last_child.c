/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/06 12:23:52 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		outfile;

	outfile = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		close_all(0, pipe_fd, arg[4], EXIT_FAILURE);
	if (ft_strlen(arg[3]) == 0)
		close_all(0, pipe_fd, "empty", EXIT_FAILURE);
	cmd_and_flags = ft_split(arg[3], ' ');
	if (!cmd_and_flags)
		close_all(0, pipe_fd, "malloc", 127);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		free_all(NULL, NULL, cmd_and_flags, NULL);
		ft_printf_err("%s: command not found\n", arg[3]);
		close_all(outfile, pipe_fd, "path", 127);
	}
	manage_access(cmd_and_flags, path_cmd, outfile, pipe_fd);
	last_dup(outfile, pipe_fd, cmd_and_flags, path_cmd);
	execve(path_cmd, cmd_and_flags, env);
	free_all(NULL, NULL, cmd_and_flags, path_cmd);
	close_all(outfile, pipe_fd, "execve", 127);
}
