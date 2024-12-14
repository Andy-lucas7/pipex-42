/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:24:39 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/13 19:30:05 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"

/*      Functions for print errors      */
int		emptycmd(const char *str);
void	print_usage(void);
void	errorexit(void);

/*            Processes             */
void	ft_exec_cmd(char *argv, char **envar);
void	parent_process(char **argv, char **envar, int *fd);
void	child_process(char **argv, char **envar, int *fd);

/*                   Utils                   */
char	*get_path(char *cmd, char **envar);
void	invalid_path(char **cmd);
void	free_cmd(char **cmd);
void	errorexit(void);
void	print_usage(void);

#endif