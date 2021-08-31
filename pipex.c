/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:26:28 by cmarcu            #+#    #+#             */
/*   Updated: 2021/08/31 16:26:14 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex(int infile, int outfile, char **argv, char **envp)
{
	int end[2];
	pid_t child1;
	pid_t child2;
	int status;

	char	**argv_cmd1;
	char	**argv_cmd2;

	argv_cmd1 = ft_split(argv[2], ' ');
	argv_cmd2 = ft_split(argv[3], ' ');
	pipe(end);
	child1 = fork();
	if (child1 == -1)
		return (perror("Fork: "));
	else if (child1 == 0) //proceso hijo
	{
		close(end[R]);

		dup2(infile, STDIN_FILENO);
		dup2(end[W], STDOUT_FILENO);
		close(infile);

		//Ejecutar el comando
		execve("/bin/ls", argv_cmd1, envp);
		perror("Error");
	}
	else //proceso padre
	{
		close(end[W]);

		child2 = fork();
		if (child2 == -1)
			return (perror("Fork: "));
		else if (child2 == 0) //proceso hijo
		{
			dup2(end[R], STDIN_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(end[W]);
			close(outfile);

			//Ejecutar comando
			execve("/usr/bin/wc", argv_cmd2, envp);
			perror("Error");
		}
		else //padre
		{
			close(end[R]);
		}
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
	//Look for command paths


	/*int i = 0;
	while (argv_cmd1[i] != NULL)
	{
		printf("%s\n", argv_cmd1[i]);
		i++;
	}*/



	pipex(infile, outfile, argv, envp);
	//system("leaks pipex");
}
