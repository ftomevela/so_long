/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:37:52 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/06/24 17:59:19 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_size(long int num)
{
	int	size;

	size = 0;
	if (num < 0)
		size++;
	while (num)
	{
		num = num / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	num;
	int		size;
	char	*str;
	char	caracter;

	if (n == 0)
		return (ft_strdup("0"));
	num = (long)n;
	size = ft_size(num);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	str[size] = '\0';
	while (num > 0)
	{
		caracter = '0' + (num % 10);
		str [--size] = caracter;
		num = num / 10;
	}
	return (str);
}

char	*free_mode(char *s1, char *s2, int mode)
{
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (NULL);
}

void	init_jump(t_var *var)
{
	var->is_jumping = 1;
	var->jump_progress = 0;
	var->jump_count = 1;
	var->jump_direction = 'N';
	var->jump_max_delay = 150;
	var->jump_delay = 0;
	apply_gravity(var);
}

void	show_on_terminal(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		write (1, &c[i], 1);
		i++;
	}
	write (1, "\n", 1);
}
