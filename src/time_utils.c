/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:23:03 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 10:45:08 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 ** @brief          Return the elapsed time since EPOCH.
 **
 ** TODO Handle 'gettimeofday' errors cause they are triggerable from
 ** the user's side.
 **
 ** @return         The elapsed time since EPOCH in millisecond.
 */

unsigned long	ft_abs_time(void)
{
	struct timeval	time;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday (&time, NULL) == -1)
		write (2, "Error: GETTIMEOFDAY(2)\n", 28);
	s = time.tv_sec * 1000;
	u = time.tv_usec / 1000;
	return (s + u);
}

/*
 ** @brief          Return the time elapsed since simulation start.
 **
 ** @param[in]      philo the simulation's struct.
 ** @return         The time elapsed since simulation start in millisecond.
 */

unsigned long	ft_rel_time(unsigned long begin)
{
	unsigned long	abs_time;

	abs_time = ft_abs_time ();
	return (abs_time - begin);
}

/*
 ** @brief      Sleep in millisec.
 **
 ** By dividing my sleep into several parts I correct a little the imprecision
 ** of USLEEP(3) for the large values. We substract the residualthe rest of imprecision  .
 **
 ** @param[in]  msec the time in millisec
 **
 */

void	ft_msleep(unsigned long msec)
{
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
	usleep (msec * 50);
}
