/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:04:54 by yobenali          #+#    #+#             */
/*   Updated: 2022/06/24 22:31:24 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(t_data *pipex)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	while (pipex->p_cmd[i])
	{
		tmp = ft_strjoin(pipex->p_cmd[i], "/");
		cmd = ft_strjoin(tmp, pipex->cmd_av[0]);
		free(tmp);
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	sc_child(t_data *pipex, char **argv, char **env)
{
	dup2(pipex->fd[0], 0);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	dup2(pipex->outfile, 1);
	close(pipex->outfile);
	pipex->cmd_av = ft_split(argv[3], ' ');
	if (access(pipex->cmd_av[0], X_OK) == 0)
		pipex->cmd = strdup(pipex->cmd_av[0]);
	else
		pipex->cmd = get_cmd(pipex);
	if (!pipex->cmd)
	{
		free(pipex->cmd_av);
		exit(write(2, "Error command not found\n", 25));
	}
	if (execve(pipex->cmd, pipex->cmd_av, env) == -1)
		exit (write (2, "execve failed\n", 14));
}

void	st_child(t_data *pipex, char **argv, char **env)
{
	dup2(pipex->fd[1], 1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	dup2(pipex->infile, 0);
	pipex->cmd_av = ft_split(argv[2], ' ');
	if (access(pipex->cmd_av[0], X_OK) == 0)
		pipex->cmd = ft_strdup(pipex->cmd_av[0]);
	else
		pipex->cmd = get_cmd(pipex);
	if (!pipex->cmd)
	{
		free(pipex->cmd_av);
		exit(write(2, "Error command not found\n", 25));
	}
	if (execve(pipex->cmd, pipex->cmd_av, env) == -1)
		exit (write (2, "execve failed\n", 14));
}

void	ft_init(t_data *pipex, char **argv, char **env)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		perror("infile :");
	pipex->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		perror("outfile :");
	if (pipe(pipex->fd) < 0)
		exit(write(2, "pipe failed\n", 12));
	while (ft_strncmp("PATH", *env, 4))
		env++;
	pipex->path = *env + 5;
	pipex->p_cmd = ft_split(pipex->path, ':');
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		st_child(pipex, argv, env);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		sc_child(pipex, argv, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	pipex;

	if (argc != 5)
		exit (write (2, "wrong number of argument\n", 25));
	ft_init(&pipex, argv, env);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
