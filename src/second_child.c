/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/19 11:55:20 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static char	*ft_strjoin_improved(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	*from_pipe;
	char	*path_cmd;

	from_pipe = NULL;
	if (close(pipe_fd[1]))
	{
		/*fail*/
	}
	//lire le resultat envoyé par pipe_fd[1]
	while (1)
	{
		from_pipe = ft_strjoin_improved(from_pipe, get_next_line(pipe_fd[0]));
		if (!from_pipe)
		{
			perror(errno);
			exit(EXIT_FAILURE);
		}
	}
	//verifier que la commande existe et la recuperer dans le bon path
	path_cmd = find_real_cmd(arg[2], env);
	if (!path_cmd)
	{
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//ouvrir le fichier av[3]
	//verifier qu'on a les droits sur le fichier
	if (access(arg[3], R_OK)) /*the access asked depends on the command*/
	{
		free(path_cmd);
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//executer la commande av[3] et stocker son resultat dans le fichier av[4]

	execve(arg[2], from_pipe, env);
    perror("execve failed");
}
