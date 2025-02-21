/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/21 11:32:45 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

// static char	*ft_strjoin_improved(char *s1, char const *s2)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	if (!s2)
// 		return (NULL);
// 	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	free(s1);
// 	// printf("gnl %s\n", str);
// 	return (str);
// }

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		file_out;

	// if (close(pipe_fd[1]) == -1)
	// {
	// 	perror("(last child) pipe");
	// 	exit(EXIT_FAILURE);
	// }
	cmd_and_flags = ft_split(arg[2], ' ');
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
