/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:49:10 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/17 11:52:23 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_is_numeric(char const *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_check_args(int ac, char const *const *av)
{
	if (ac < 5)
	{
		write (2, "Error: Too few arguments.\n", 26);
		return (0);
	}
	if (ac > 6)
	{
		write (2, "Error: Too many arguments.\n", 27);
		return (0);
	}
	while (ac-- > 1)
	{
		if (ft_is_numeric (av[ac]) == 0)
		{
			write (2, "Error: Invalid character.\n", 26);
			return (0);
		}
		if (ft_atol (av[ac]) > INT_MAX || ft_atol (av[ac]) < 0)
		{
			write (2, "Error: Out of range value.\n", 27);
			return (0);
		}
	}
	return (1);
}