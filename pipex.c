/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:26:28 by cmarcu            #+#    #+#             */
/*   Updated: 2021/08/30 17:22:01 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex(int infile, int outfile, char **argv, char **envp)
{
	int end[2];
	pid_t child1;
	pid_t child2;
	int status;

	pipe(end);
	child1 = fork();
	if (child1 == -1)
	{
		return (perror("Fork: "));
	}
	else if (child1 == 0) //proceso hijo
	{
		//Cerrar extremo de lectura
		close(end[R]);

		//Duplicar el extremo de escritura para sustituir stdout dup2(pipefd[W], STDIN_FILENO)
		dup2(end[W], STDIN_FILENO);

		//Cerrar el extremo que acabamos de duplicar
		close(end[W]);

		//Ejecutar el comando
		execlp("/bin/ls", "ls", "-la", NULL);
	}
	else //proceso padre
	{
		//Cerrar extremo de escritura del hijo
		close(end[W]);

		//Crear otro hijo porque vamos a ejecutar otro exe
		child2 = fork();

		if (child2 == -1)
		{
			printf("Fork didn´t work");
		}
		else if (child2 == 0) //proceso hijo
		{
			//Abrir archivo y redireccionar salida estandar al archivo
			dup2(end[R], STDIN_FILENO);
			close(end[R]);
			dup2(outfile, STDOUT_FILENO);

			//Ejecutar comando
			execlp("usr/bin/wc", "wc", NULL);
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
	int infile;
	int outfile;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (-1);
	if (argc != 5)
		return (-1);
	pipex(infile, outfile, argv, envp);


	/*else
		printf("Wrong formatting");*/
}
