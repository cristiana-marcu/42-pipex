/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:59:52 by cmarcu            #+#    #+#             */
/*   Updated: 2021/08/31 18:02:51 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path_line(char **envp)
{
	int		i;
	char	*str;

	i = 0;
	while (envp[i] != 0)
	{
		str = ft_strnstr(envp[i], "PATH=", 5);
		if (str)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_path(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**possible_paths;
	int		i;

	cmd_path = NULL;
	possible_paths = ft_split(envp[get_path_line(envp)], ':');
	i = 0;
	while (possible_paths[i])
	{
		possible_paths[i] = ft_strjoin(possible_paths[i], "/");
		possible_paths[i] = ft_strjoin(possible_paths[i], cmd);
		if (access(possible_paths[i], F_OK) == 0)
		{
			cmd_path = ft_strdup(possible_paths[i]);
			break ;
		}
		i++;
	}
	free(possible_paths);
	return (cmd_path);
}
