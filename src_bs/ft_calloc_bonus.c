/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 06:16:04 by yobenali          #+#    #+#             */
/*   Updated: 2022/06/14 06:24:08 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*buf;

	i = 0;
	buf = (unsigned char *) b;
	while (i < len)
	{
		buf[i] = (unsigned char) c;
		i++;
	}
	return ((void *) buf);
}

void	ft_bzero(void	*s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	t_count;
	char	*ptr;

	t_count = count * size;
	ptr = malloc(t_count);
	if (!ptr)
		return (NULL);
	ft_bzero((void *)ptr, t_count);
	return ((void *)ptr);
}
