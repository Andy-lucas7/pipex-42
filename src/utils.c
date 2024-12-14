/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:41:40 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/14 15:59:08 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char *cmd, char **envar)
{
	int		i;
	char	*path;
	char	*part_path;
	char	**paths;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (envar[i] && ft_strnstr(envar[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envar[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_cmd(paths);
	return (NULL);
}

void	invalid_path(char **cmd)
{
	if (cmd && cmd[0])
	{
		ft_putstr_fd("\033[1;31mError: Command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\033[0m", 2);
		ft_putchar_fd('\n', 2);
	}
	free_cmd(cmd);
	exit(127);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}

void	errorexit(void)
{
	perror("\033[1;31mError!\n\033[0m");
	ft_putstr_fd("\033[31mUsage: ./pipex <file1> <cmd1> <cmd2> <file2>\n\033[0m",
		1);
	exit(EXIT_FAILURE);
}

void	print_usage(void)
{
	ft_putstr_fd("\033[1;31mError: Incorrect number of arguments.\n", 2);
	ft_putstr_fd("\033[0;31mUsage: ./pipex <file1> <cmd1> <cmd2> <file2>\n\033[0m",
		1);
}
