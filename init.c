/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:54:39 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/17 12:24:13 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init_philo(t_philo **philo, t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc (sizeof (pthread_mutex_t) * ((size_t)data->philo_nb));
	if (fork == NULL)
		return (0);
	i = 0;
	while (i < data->philo_nb)
		pthread_mutex_init (&fork[i++], NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].last_meal = data->simbegin;
		(*philo)[i].meals_counter = 0;
		(*philo)[i].lfork = i;
		if (i - 1 < 0)
			(*philo)[i].rfork = data->philo_nb - 1;
		else
			(*philo)[i].rfork = i - 1;
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		i++;
	}
	return (1);
}

int	ft_init_data_mutexes(t_data **data)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = malloc (sizeof (pthread_mutex_t) * ((size_t)(*data)->philo_nb));
	if (mutex == NULL)
		return (0);
	i = 0;
	while (i < (size_t)(*data)->philo_nb)
		pthread_mutex_init (&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (1);
}

int	ft_init_data(t_data **data, int ac, char const *const *av)
{
	(*data)->simbegin = ft_abs_time ();
	(*data)->philo_nb = (int)ft_atol (av[1]);
	(*data)->time_die = (int)ft_atol (av[2]);
	(*data)->time_eat = (int)ft_atol (av[3]);
	(*data)->time_slp = (int)ft_atol (av[4]);
	(*data)->time_thk = 0;
	if (((*data)->philo_nb % 2) && ((*data)->time_eat > (*data)->time_slp))
		(*data)->time_thk = 1 + ((*data)->time_eat - (*data)->time_slp);
	if (ac == 5)
		(*data)->must_eat = -1;
	if (ac == 6)
		(*data)->must_eat = (int)ft_atol (av[5]);
	(*data)->done = 0;
	(*data)->died = 0;
	if (ft_init_data_mutexes (data))
		return (0);
	return (1);
}

int	ft_init(t_philo **philo, t_data **data, int ac, char const *const *av)
{
	*data = (t_data *)malloc (sizeof (t_data));
	if (*data == NULL)
		return (0);
	(*data)->mutex = NULL;
	if (ft_init_data (data, ac, av) != 1)
		return (0);
	*philo = (t_philo *)malloc (sizeof (t_philo) * (size_t)(*data)->philo_nb);
	if (*philo == NULL)
		return (0);
	(*philo)->fork = NULL;
	if (ft_init_philo (philo, *data) != 1)
		return (0);
	return (1);
}