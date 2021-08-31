/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:26:28 by cmarcu            #+#    #+#             */
/*   Updated: 2021/08/31 18:04:05 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(int infile, int end[], char **argv, char **envp)
{
	char	**argv_cmd1;
	char	*path;

	argv_cmd1 = ft_split(argv[2], ' ');
	close(end[R]);
	dup2(infile, STDIN_FILENO);
	dup2(end[W], STDOUT_FILENO);
	close(infile);
	path = get_path(argv_cmd1[0], envp);
	execve(path, argv_cmd1, envp);
	perror("Error");
}

void	child_two(int outfile, int end[], char **argv, char **envp)
{
	char	**argv_cmd2;
	char	*path;

	argv_cmd2 = ft_split(argv[3], ' ');
	dup2(end[R], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(end[W]);
	close(outfile);
	//Look for path
	path = get_path(argv_cmd2[0], envp);
	//Ejecutar comando
	execve(path, argv_cmd2, envp);
	perror("Error");
}

void	pipex(int infile, int outfile, char **argv, char **envp)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	pipe(end);
	child1 = fork();
	if (child1 == -1)
		return (perror("Fork: "));
	else if (child1 == 0) //proceso hijo
		child_one(infile, end, argv, envp);
	else //proceso padre
	{
		close(end[W]);
		child2 = fork();
		if (child2 == -1)
			return (perror("Fork: "));
		else if (child2 == 0) //proceso hijo
			child_two(outfile, end, argv, envp);
		else //padre
			close(end[R]);
	}
	wait(&status);
	wait(&status);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
	{
		perror("Error: ");
		return (-1);
	}
	if (argc != 5)
	{
		printf("Wrong formatting");
		return (-1);
	}
	pipex(infile, outfile, argv, envp);
	//system("leaks pipex");
}
