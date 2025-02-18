/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/18 12:45:22 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/libft.h"

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/*utils.c*/
void	free_all(char *path, char *path_cmd, char **cmd_and_flags);
char	*real_cmd(char *cmd, char **env);
char	*extract_cmd(char *cmd_flag);
/*child.c*/
void	process_is_child(int *pipe_fd, char **av, char **env);
/*parent.c*/
void	process_is_parent(int *pipe_fd, char **arg, char **env);

#endif
