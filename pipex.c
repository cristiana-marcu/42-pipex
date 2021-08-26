/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: RAMON <RAMON@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:10:25 by RAMON             #+#    #+#             */
/*   Updated: 2021/08/25 17:09:52 by RAMON            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    /*fd[0] is for reading
    fd[1] is for writing*/
    int pipefd[2];
    pid_t pid;

    if (argc == 5)
    {
        pipe(pipefd);
        pid = fork();
        if (pid < 0)
            printf("Fork didn't work");
        else if (pid == 0) //child process = left of the pipe
        {
            printf("I'm the child process");
        }
        else //parent process = right of the pipe
            pintf("I'm the parent process");
    }
    printf("Read File Descriptor Value: %d\n", pipefd[0]);
    printf("Write File Descriptor Value: %d\n", pipefd[1]);
    return (0);
}

//TODO: dado dos archivos ./pipex infile outfile, leer lo que hay en infile y escribirlo en outfile
