/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:24:18 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/14 15:30:12 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	emptycmd(const char *str)
{
	return (!str || str[0] == '\0');
}

void	ft_exec_cmd(char *argv, char **envar)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
	{
		free_cmd(cmd);
		ft_putstr_fd("\033[31mError: Command is empty or invalid.\n\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	path = get_path(cmd[0], envar);
	if (!path)
		invalid_path(cmd);
	if (execve(path, cmd, envar) == -1)
	{
		perror("Error: Failed execve.");
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
}

void	parent_process(char **argv, char **envar, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("\033[31mError: Opening imput file.");
		exit (EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("\033[31mError: Duplicating fd[0] for STDIN.");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("\033[31mError: Duplicating outfile for STDIN.");
		exit(EXIT_FAILURE);
	}
	close(outfile);
	close(fd[1]);
	ft_exec_cmd(argv[3], envar);
}

void	child_process(char **argv, char **envar, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0644);
	if (infile == -1)
	{
		perror("\033[31mError: opening imput file");
		exit (EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("\033[31mError: Duplicating fd[1] for STDOUT");
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file_in for STDIN");
		exit(EXIT_FAILURE);
	}
	close(infile);
	close(fd[0]);
	ft_exec_cmd(argv[2], envar);
}

int	main(int argc, char **argv, char **envar)
{
	int		fd[2];
	pid_t	chld_pid;

	if (argc != 5)
	{
		print_usage();
		exit(1);
	}
	if (emptycmd(argv[2]) || emptycmd(argv[3]))
		return (print_usage(), 1);
	if (pipe(fd) == -1)
		errorexit();
	chld_pid = fork();
	if (chld_pid == -1)
		errorexit();
	if (chld_pid == 0)
		child_process(argv, envar, fd);
	else
	{
		waitpid(chld_pid, NULL, WNOHANG);
		parent_process(argv, envar, fd);
	}
	return (0);
}
