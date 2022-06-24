/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:55:57 by yobenali          #+#    #+#             */
/*   Updated: 2022/06/24 22:49:53 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_args(int ac, char **argv)
{
	int	i;

	i = 0;
	if (ac <= 1)
		return (2);
	else if (!ft_strncmp("here_doc", argv[1], 9))
		return (6);
	else
		return (5);
}

void	ft_in_out(t_data *pipex, int fd[2] , int infile, char **env)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		close(fd[0]);
		if (dup2(infile, 0) < 0)
			exit(write(2, "Error dup2 failed\n", 19));
		close(infile);
		if (av[pipex->cmd_index + 2] == NULL)
		{
			if (dup2(pipex->outfile, 1) < 0)
				exit(write(2, "Error dup2 failed\n", 19));
			close(pipex->outfile);
		}
		else
		{
			if (dup2(fd[1], 1) < 0)
				exit(write(2, "Error dup2 failed\n", 19));
			close(fd[1]);
		}
		if (execve(pipex->cmd, pipex->cmd_av, env) == -1)
			exit(write(2, "execve failed\n", 15));
	}
}

int	ft_cal(int ac, char **av)
{
	int	i;

	i = check_args(ac, av);
	if (i == 6)
		return (4);
	return (3);
}

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

void	ft_check_cmd(t_data *pipex, char **av)
{
	pipex->cmd_av = ft_split(av[pipex->cmd_index], ' ');
	if (!pipex->cmd_av)
		return ;
	if (access(pipex->cmd_av[0], X_OK) == 0)
		pipex->cmd = strdup(pipex->cmd_av[0]);
	else
		pipex->cmd = get_cmd(pipex);
	if (!pipex->cmd)
	{
		free(pipex->cmd_av);
		exit(write(2, "Error command not found\n", 25));
	}
}

void	ft_multi_pipe(t_data *pipex, int infile, char **av, char **env)
{
	int		fd[2];

	if (pipex->index >= pipex->num_cmd)
		return ;
	ft_check_cmd(pipex, av);
	// pipex->cmd_av = ft_split(av[pipex->cmd_index], ' ');
	// if (!pipex->cmd_av)
	// 	return ;
	// if (access(pipex->cmd_av[0], X_OK) == 0)
	// 	pipex->cmd = strdup(pipex->cmd_av[0]);
	// else
	// 	pipex->cmd = get_cmd(pipex);
	// if (!pipex->cmd)
	// {
	// 	free(pipex->cmd_av);
	// 	exit(write(2, "Error command not found\n", 25));
	// }
	if (av[pipex->cmd_index + 2] != NULL )
	{
		if (pipe(fd) < 0)
			exit(write(2, "pipe failed\n", 13));
	}
	ft_in_out(pipex, fd, infile, env);
	// pipex->pid = fork();
	// if (pipex->pid == 0)
	// {
	// 	close(fd[0]);
	// 	if (dup2(infile, 0) < 0)
	// 		exit(write(2, "Error dup2 failed\n", 19));
	// 	close(infile);
	// 	if (av[pipex->cmd_index + 2] == NULL)
	// 	{
	// 		if (dup2(pipex->outfile, 1) < 0)
	// 			exit(write(2, "Error dup2 failed\n", 19));
	// 		close(pipex->outfile);
	// 	}
	// 	else
	// 	{
	// 		if (dup2(fd[1], 1) < 0)
	// 			exit(write(2, "Error dup2 failed\n", 19));
	// 		close(fd[1]);
	// 	}
	// 	if (execve(pipex->cmd, pipex->cmd_av, env) == -1)
	// 		exit(write(2, "execve failed\n", 15));
	// }
	close(infile);
	if (av[pipex->cmd_index + 2] != NULL )
		close(fd[1]);
	else
		close(pipex->outfile);
	pipex->index++;
	pipex->cmd_index++;
	ft_multi_pipe(pipex, fd[0], av, env);
	close(fd[0]);
}

void	ft_init(t_data *pipex, int ac, char **argv, char **env)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		exit(write(2, "Error infile\n", 13));
	pipex->outfile = open(argv[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		exit(write(2, "Error outfile\n", 14));
	while (ft_strncmp("PATH", *env, 4))
		env++;
	pipex->path = *env + 5;
	pipex->p_cmd = ft_split(pipex->path, ':');
	pipex->num_cmd = ac - ft_cal(ac, argv);
	pipex->cmd_index = ft_cal(ac, argv) - 1;
	pipex->index = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	pipex;

	if (argc < check_args(argc, argv))
		exit(write(2, "Error\n", 6));
	ft_init(&pipex, argc, argv, env);
	ft_multi_pipe(&pipex, pipex.infile, argv, env);
	while (1)
	{
		if (waitpid(-1, NULL, 0) < 0)
			break ;
	}
	return (0);
}
