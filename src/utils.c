/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:51:15 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 09:53:35 by abarzila         ###   ########.fr       */
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

static char	*ft_strtrim_improved(char *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*result;

	i = 0;
	start = -1;
	end = -2;
	while (s1[i] && start == -1)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			start = i;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && end == -2)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			end = i;
		i--;
	}
	result = ft_substr(s1, start, (end - start) + 1);
	free(s1);
	return (result);
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

void	manage_deviate_first(int fd, int *pipe_fd, char **cmd_and_flags, char *path_cmd)
{
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(fd, pipe_fd, "dup2", 1);
	}
}
