/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:18:12 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/11 14:19:04 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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