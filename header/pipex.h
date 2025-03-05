/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 09:53:47 by abarzila         ###   ########.fr       */
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
void	manage_deviate_first(int fd, int *pipe_fd, char **cmd_and_flags, char *path_cmd);
/*exit.c*/
void	free_all(char **path, char **hyp_path_cmd, char **cmd_and_flags, char *path_cmd);
void	close_fd_and_pipe_and_exit(int fd, int *pipe_fd, char *message, int fail);
/*last_child.c*/
void	manage_cmd_last(int *pipe_fd, char **av, char **env);
/*first_parent.c*/
void	manage_cmd_first(int *pipe_fd, char **arg, char **env);

#endif
