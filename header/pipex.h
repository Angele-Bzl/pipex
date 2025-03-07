/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/07 12:08:02 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/printf_err/ft_printf_err.h"
# include <sys/wait.h>

/*utils.c*/
void	first_dup(int fd, int *pipe_fd, char **cmd_and_flags, char *path_cmd);
void	last_dup(int outfile, int *pipe_fd, char **cmd_flags, char *path_cmd);
char	*ft_strtrim_improved(char *s1, char const *set);
int		tablen(char **tab);
/*command*/
char	*find_real_cmd(char **env, char **cmd_and_flags);
void	manage_access(char **cmd_flags, char *path_cmd, int file, int *pipe_fd);
/*exit.c*/
void	free_all(char **path, char **hyp_path, char **cmd_flag, char *path_cmd);
void	close_all(int fd, int *pipe_fd, char *message, int exit_status);
void	leave_program(pid_t pid_1, pid_t pid_2, int *pipe_fd);
/*last_child.c*/
void	manage_cmd_last(int *pipe_fd, char **av, char **env);
/*first_parent.c*/
void	manage_cmd_first(int *pipe_fd, char **arg, char **env);

#endif
