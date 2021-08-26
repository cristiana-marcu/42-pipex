/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:26:28 by cmarcu            #+#    #+#             */
/*   Updated: 2021/08/26 16:34:25 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int pipefd[2];
	pid_t pid;
	int out_file;
	int status;

	argc = 3;
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
	{
		printf("Fork didn´t work");
	}
	else if (pid == 0) //proceso hijo
	{
		//Cerrar extremo de lectura
		close(pipefd[R_END]);

		//Duplicar el extremo de escritura para sustituir stdout dup2(pipefd[W], STDIN_FILENO)
		dup2(pipefd[W_END], STDIN_FILENO);

		//Cerrar el extremo que acabamos de duplicar
		close(pipefd[W_END]);

		//Ejecutar el comando
		execlp("/bin/ls", "ls", "-la", NULL);
	}
	else //proceso padre
	{
		//Cerrar extremo de escritura del hijo
		close(pipefd[W_END]);

		//Crear otro hijo porque vamos a ejecutar otro exe
		pid = fork();

		if (pid == 0) //proceso hijo
		{
			//Abrir archivo y redireccionar salida estandar al archivo
			out_file = open(argv[3], O_WRONLY);
			dup2(pipefd[R_END], STDIN_FILENO);
			close(pipefd[R_END]);
			dup2(out_file, STDOUT_FILENO);

			//Ejecutar comando
			execlp("usr/bin/wc", "wc", NULL);
		}
		else //padre
		{
			close(pipefd[R_END]);
		}
	}
	wait(&status);
	wait(&status);
}
