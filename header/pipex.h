/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/04 16:41:53 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/printf_err/ft_printf_err.h"

# include <sys/wait.h>
# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

/*utils.c*/
char	*find_real_cmd(char **env, char **cmd_and_flags);
/*exit.c*/
void	free_all(char **path, char **path_cmd, char **cmd_and_flags);
void	close_pipe_and_exit(int *pipe_fd, char *message, int fail);
void	dup2_failed(int fd, int *pipe_fd, char **cmd_and_flags);
/*last_child.c*/
void	manage_cmd_last(int *pipe_fd, char **av, char **env);
/*first_parent.c*/
void	manage_cmd_first(int *pipe_fd, char **arg, char **env);

#endif
