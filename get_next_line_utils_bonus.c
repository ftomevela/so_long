/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:51:37 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/25 15:28:18 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	to_find;

	i = 0;
	to_find = c;
	while (s[i] != '\0')
	{
		if (s[i] != to_find)
			i++;
		else
			return ((char *)&s[i]);
	}
	if (to_find == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num_elements * element_size + 1;
	ptr = malloc(total_size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, total_size);
	}
	return (ptr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= dstlen)
		return (dstsize += srclen);
	else
		srclen += dstlen;
	while (src[i] != '\0' && dstlen < dstsize -1 && dst != src)
	{
		dst[dstlen] = src[i];
		dstlen++;
		i++;
	}
	dst[dstlen] = '\0';
	return (srclen);
}

char	*ft_strjoin(char *s1, char *s2, int mode)
{
	int		lens1;
	int		lens2;
	char	*str;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!s1 || !s2)
		free_mode(s1, s2, mode);
	str = ft_calloc(lens1 + lens2 + 1, sizeof(char));
	if (!str)
		free_mode(s1, s2, mode);
	ft_strlcat(str, s1, lens1 + 1);
	ft_strlcat(str, s2, lens1 + lens2 + 1);
	free_mode(s1, s2, mode);
	return (str);
}
