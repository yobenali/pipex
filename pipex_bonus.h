/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:56:10 by yobenali          #+#    #+#             */
/*   Updated: 2022/06/25 01:05:47 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		infile;
	int		outfile;
	char	*path;
	char	**p_cmd;
	char	**cmd_av;
	char	*cmd;
	char	**str;
	int		cmd_index;
	int		num_cmd;
	int		index;
	int		fd[2];
	pid_t	pid;
}	t_data;

void	*ft_calloc(size_t count, size_t size);
void	ft_err(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		check_args(int ac, char **argv);
int		ft_cal(int ac, char **av);
char	*get_cmd(t_data *pipex);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);

#endif
//