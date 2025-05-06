/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:18:12 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/18 08:56:38 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

void	close_perror_exit(int *pipe_fd, int fd, char *message, pid_t *pid)
{
	if (pipe_fd)
	{
		if (pipe_fd[0])
			close(pipe_fd[0]);
		if (pipe_fd[1])
			close(pipe_fd[1]);
	}
	if (fd)
		close(fd);
	if (pid)
		free(pid);
	perror(message);
	exit(EXIT_FAILURE);
}

void	putendl_exit(char *message, int exit_status, pid_t *pid)
{
	ft_putendl_fd(message, STDERR_FILENO);
	if (pid)
		free(pid);
	exit(exit_status);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	i++;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
	return (NULL);
}

char	*ft_strtrim_improved(char *s1, char const *set)
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
