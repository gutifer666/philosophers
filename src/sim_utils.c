/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:38:03 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 10:39:13 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 ** @brief      Log each philosopher's life cycle actions into the terminal.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  a the philo's action
 */

void	ft_print(t_philo *philo, char const *const a)
{
	pthread_mutex_lock (&philo->data->mutex[PRINT]);
	if (*a == 'd' || (!ft_check_died (philo) && !ft_check_done (philo)))
		printf("%lu %d %s\n", ft_rel_time(philo->data->simbegin), philo->id, a);
	pthread_mutex_unlock (&philo->data->mutex[PRINT]);
}

/*
 ** @brief      Officialise the first death.
 **
 ** @param[in]  data the simulator's struct.
 */

void	ft_died(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DIED]);
	data->died = TRUE;
	pthread_mutex_unlock (&data->mutex[DIED]);
}

/*
 ** @brief      Officialise the end of the dinner.
 **
 ** All the philosophers ate at least 'must_eat' times.
 **
 ** @param[in]  data the simulator's struct.
 */

void	ft_done(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock (&data->mutex[DONE]);
}

/*
 ** @brief      Check a death occured.
 **
 ** @param[in]  data the simulator's struct.
 */

int	ft_check_died(t_philo *philo)
{
	pthread_mutex_lock (&philo->data->mutex[DIED]);
	if (philo->data->died)
	{
		pthread_mutex_unlock (&philo->data->mutex[DIED]);
		return (TRUE);
	}
	pthread_mutex_unlock (&philo->data->mutex[DIED]);
	return (FALSE);
}

/*
 ** @brief      Check if the dinner is done.
 **
 ** All the philosophers ate at least 'must_eat' times.
 **
 ** @param[in]  data the simulator's struct.
 */

int	ft_check_done(t_philo *philo)
{
	pthread_mutex_lock (&philo->data->mutex[DONE]);
	if (philo->data->done)
	{
		pthread_mutex_unlock (&philo->data->mutex[DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock (&philo->data->mutex[DONE]);
	return (FALSE);
}