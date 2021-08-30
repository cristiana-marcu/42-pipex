/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:41:01 by cmarcu            #+#    #+#             */
/*   Updated: 2021/08/30 18:03:36 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define W 1
# define R 0

void pipex(int infile, int outfile, char **argv, char **envp); //, char **argv, char **envp

#endif
