/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:06:53 by yobenali          #+#    #+#             */
/*   Updated: 2022/06/26 23:29:17 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_free(char **str, int i)
{
	while (str[i])
		free(str[i++]);
	free(str);
}

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
		tmp = ft_mystrjoin(pipex->p_cmd[i], "/");
		cmd = ft_mystrjoin(tmp, pipex->cmd_av[0]);
		free(tmp);
		if (!access(cmd, X_OK))
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	return (ptr);
}
