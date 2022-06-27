/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 04:43:05 by yobenali          #+#    #+#             */
/*   Updated: 2022/06/26 21:46:38 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_mystrjoin(char *s1, char *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*tab;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	tab = (char *)ft_calloc(size + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (++i < ft_strlen(s1))
		tab[i] = s1[i];
	while (i < size)
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	return (tab);
}
