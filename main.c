/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:33:47 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/17 11:53:14 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_clear_memory(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free (data->mutex);
	if (data)
		free (data);
	if (philo && philo->fork)
		free (philo->fork);
	if (philo)
		free (philo);
}

static int	ft_edgecases(int ac, char const *const *av)
{
	if ((ac == 6 && ft_atol (av[5]) == 0))
		return (1);
	if (ft_atol (av[1]) == 0)
		return (1);
	return (0);
}

int main(int    ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (ft_check_args (ac, av) != 1)
		return ((void)ft_clear_memory (philo, data), EXIT_FAILURE);
	if (ft_edgecases (ac, av))
		return ((void)ft_clear_memory (philo, data), EXIT_SUCCESS);
	if (ft_init (&philo, &data, ac, av) != 1)
		return ((void)ft_clear_memory (philo, data), EXIT_FAILURE);
	if (ft_simulator (philo, data) != 1)
		return ((void)ft_clear_memory (philo, data), EXIT_FAILURE);
	return ((void)ft_clear_memory (philo, data), EXIT_SUCCESS);
}
