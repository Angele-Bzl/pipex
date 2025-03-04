/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:51:15 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/04 13:25:02 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	free_all(char **path, char **path_cmd, char **cmd_and_flags)
{
	int	i;

	if (path)
	{
		i = 0;
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	if (path_cmd)
	{
		i = 0;
		while (path_cmd[i])
		{
			free(path_cmd[i]);
			i++;
		}
		free(path_cmd);
	}
	if (cmd_and_flags)
	{
		i = 0;
		while (cmd_and_flags[i])
		{
			free(cmd_and_flags[i]);
			i++;
		}
		free(cmd_and_flags);
	}
}

// static void	free_almost_all(char **path, char **path_cmd, int good, char **cmd_and_flags)
// {
// 	int	i;

// 	if (path)
// 	{
// 		i = 0;
// 		while (path[i])
// 		{
// 			free(path[i]);
// 			i++;
// 		}
// 	}
// 	if (path_cmd)
// 	{
// 		i = 0;
// 		while (path_cmd[i])
// 		{
// 			if (i != good)
// 				free(path_cmd[i]);
// 			i++;
// 		}
// 	}
// 	if (cmd_and_flags)
// 	{
// 		i = 0;
// 		while (cmd_and_flags[i])
// 		{
// 			free(cmd_and_flags[i]);
// 			i++;
// 		}
// 	}
// }

static int	init_hypothetical_path(char **hypothetical_path_cmd, char **cmd_and_flags, char **path)
{
	char	*path_w_backslash;
	int		i;

	i = 0;
	while (path[i])
	{
		path_w_backslash = ft_strjoin(path[i], "/");
		if (!path_w_backslash)
		{
			free_all(path, hypothetical_path_cmd, cmd_and_flags);
			return (0);
		}
		hypothetical_path_cmd[i] = ft_strjoin(path_w_backslash, cmd_and_flags[0]);
		if (!hypothetical_path_cmd[i])
		{
			free_all(path, hypothetical_path_cmd, cmd_and_flags);
			free(path_w_backslash);
			return (0);
		}
		free(path_w_backslash);
		i++;
	}
	return (1);
}

static int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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
	path[0] = ft_strtrim(path[0], "PATH=");
	hypothetical_path_cmd = malloc(sizeof (char *) * tablen(path));
	if (!path || !hypothetical_path_cmd || !cmd_and_flags)
	{
		printf("1\n");
		free_all(path, hypothetical_path_cmd, cmd_and_flags);
		return (NULL);
	}
	if (init_hypothetical_path(hypothetical_path_cmd, cmd_and_flags, path) == 0)
	{
		printf("2\n");
		free_all(path, hypothetical_path_cmd, cmd_and_flags);
		return (NULL);
	}
	real_path = find_path_cmd(hypothetical_path_cmd, path);

	printf("real path : %s\n", real_path);

	int	i;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (real_path);
}

