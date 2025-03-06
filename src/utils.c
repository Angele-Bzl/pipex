/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:51:15 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/06 10:11:46 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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


/*faire manage deviate last*///////////////////////////


void	manage_deviate_first(int fd, int *pipe_fd, char **cmd_and_flags, char *path_cmd)
{
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		free_all(NULL, NULL, cmd_and_flags, path_cmd);
		close_fd_and_pipe_and_exit(fd, pipe_fd, "dup2", EXIT_FAILURE);
	}
}
