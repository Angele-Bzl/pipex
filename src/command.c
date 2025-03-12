/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:37:49 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/12 13:39:49 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static int	init_hyp_path(char **hyp_path, char **cmd_flags, char **env_path)
{
	char	*path_w_backslash;
	int		i;

	i = 0;
	while (env_path[i])
	{
		path_w_backslash = ft_strjoin(env_path[i], "/");
		if (!path_w_backslash)
		{
			free_tab(hyp_path);
			return (0);
		}
		hyp_path[i] = ft_strjoin(path_w_backslash, cmd_flags[0]);
		if (!hyp_path[i])
		{
			free(path_w_backslash);
			free_tab(hyp_path);
			return (0);
		}
		free(path_w_backslash);
		i++;
	}
	return (1);
}

static char	*check_if_cmd_exists(char **hypothetical_path_cmd, char **path)
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
	hypothetical_path_cmd = NULL;
	return (real_path);
}

static int	find_path_in_env(char **env)
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
	char	**env_path;
	char	**hypothetical_path_cmd;
	char	*real_path;

	env_path = ft_split(env[find_path_in_env(env)], ':');
	if (!env_path)
		return (NULL);
	env_path[0] = ft_strtrim_improved(env_path[0], "PATH=");
	if (!env_path[0])
		return (free_tab(env_path), NULL);
	hypothetical_path_cmd = malloc(sizeof (char *) * tablen(env_path));
	if (!hypothetical_path_cmd)
		return (free_tab(env_path), NULL);
	if (init_hyp_path(hypothetical_path_cmd, cmd_and_flags, env_path) == 0)
		return (free(env_path), NULL);
	real_path = check_if_cmd_exists(hypothetical_path_cmd, env_path);
	free_tab(env_path);
	return (real_path);
}
