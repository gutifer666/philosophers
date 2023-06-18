/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:43:05 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 10:43:49 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 ** @brief      Destroy all the mutexes.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 */

static void	ft_destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy (&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy (&data->mutex[i++]);
}

/*
 ** @brief      Check if all philos ate at least 'must_eat' times.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 ** @return     True or false.
 */

static int	ft_are_done(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->must_eat == -1)
		return (FALSE);
	i = -1;
	done = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_lock (&philo->data->mutex[MEALS]);
		meals_count = philo[i].meals_counter;
		pthread_mutex_unlock (&philo->data->mutex[MEALS]);
		if (meals_count >= data->must_eat)
			if (++done == data->philo_nb - 1)
				return (TRUE);
		usleep (50);
	}
	return (FALSE);
}

/*
 ** @brief      Continuously check the simulation's termination conditions.
 **
 ** If one death occurs.
 ** If all the philosophers ate at least 'must_eat' times.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 ** @return     0 if everything went well.
 */

static int	ft_monitor(t_philo *philo, t_data *data)
{
	int				i;
	unsigned long	l_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock (&data->mutex[MEALS]);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock (&data->mutex[MEALS]);
		if (l_meal && ft_are_done (philo, data))
		{
			ft_done (data);
			break ;
		}
		if (l_meal && ft_abs_time () - l_meal > (unsigned long)data->time_die)
		{
			ft_died (data);
			ft_print (&philo[i], "died");
			break ;
		}
		i = (i + 1) % data->philo_nb;
		usleep (200);
	}
	return (SUCCESS);
}

/*
 ** @brief      Threads manager.
 **
 ** Generate, manage and destroy the simulation required threads.
 **
 ** TODO
 ** Protect 'pthread_create' cause there is a malloc behind.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 ** @return     0 if everything went well, otherwise 1.
 */

int	ft_simulator(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*th;

	th = malloc (sizeof (pthread_t) * (size_t)data->philo_nb);
	if (th == NULL)
		return (FAILURE);
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_create (&th[i], 0, ft_simulation, (void *)&philo[i]))
		{
			while (i--)
				pthread_join (th[i], NULL);
			return ((void)free (th), FAILURE);
		}
	}
	if (ft_monitor (philo, data) != SUCCESS)
		return ((void)ft_destroy_mutexes (philo, data), (void)free (th),
			FAILURE);
	i = -1;
	while (++i < data->philo_nb)
		if (pthread_join (th[i], NULL))
			return (FAILURE);
	return ((void)ft_destroy_mutexes (philo, data), (void)free (th), SUCCESS);
}