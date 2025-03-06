/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:20:45 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/06 10:07:09 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static int	init_hyp_path(char **hyp_path, char **cmd_and_flags, char **path)
{
	char	*path_w_backslash;
	int		i;

	i = 0;
	while (path[i])
	{
		path_w_backslash = ft_strjoin(path[i], "/");
		if (!path_w_backslash)
		{
			free_all(path, hyp_path, cmd_and_flags, NULL);
			return (0);
		}
		hyp_path[i] = ft_strjoin(path_w_backslash, cmd_and_flags[0]);
		if (!hyp_path[i])
		{
			free_all(path, hyp_path, cmd_and_flags, NULL);
			free(path_w_backslash);
			return (0);
		}
		free(path_w_backslash);
		i++;
	}
	return (1);
}

static char	*find_path_cmd(char **hypothetical_path_cmd, char **path)
{
	int		i;
	char	*real_path;

	i = 0;
	real_path = NULL;
	while (path[i])
	{
		if (!access(hypothetical_path_cmd[i], X_OK))
		{
			real_path = ft_strdup(hypothetical_path_cmd[i]);
		}
		free(hypothetical_path_cmd[i]);
		i++;
	}
	free(hypothetical_path_cmd);
	return (real_path);
}

static int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

char	*find_real_cmd(char **env, char **cmd_and_flags)
{
	char	**path;
	char	**hypothetical_path_cmd;
	char	*real_path;

	path = ft_split(env[find_path(env)], ':');
	path[0] = ft_strtrim_improved(path[0], "PATH=");
	hypothetical_path_cmd = malloc(sizeof (char *) * tablen(path));
	if (!path || !hypothetical_path_cmd || !cmd_and_flags)
	{
		free_all(path, hypothetical_path_cmd, cmd_and_flags, NULL);
		return (NULL);
	}
	if (init_hyp_path(hypothetical_path_cmd, cmd_and_flags, path) == 0)
	{
		free_all(path, hypothetical_path_cmd, cmd_and_flags, NULL);
		return (NULL);
	}
	real_path = find_path_cmd(hypothetical_path_cmd, path);
	free_all(path, NULL, NULL, NULL);
	return (real_path);
}

// int	path(char *arg, char **env, char **cmd_and_flags, char *path_cmd)
// {
// 	if (ft_strlen(arg) == 0)
// 		return (EXIT_FAILURE);
// 	cmd_and_flags = ft_split(arg, ' ');
// 	if (!cmd_and_flags)
// 		return (127);
// 	path_cmd = find_real_cmd(env, cmd_and_flags);
// 	if (!path_cmd)
// 	{
// 		free_all(NULL, NULL, cmd_and_flags, NULL);
// 		return (127);
// 	}
// 	if (access(path_cmd, X_OK))
// 	{
// 		free_all(NULL, NULL, cmd_and_flags, path_cmd);
// 		return (127);
// 	}
// 	return (0);
// }
