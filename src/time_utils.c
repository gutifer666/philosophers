/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:23:03 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 21:11:04 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** @brief  Devuelve el tiempo transcurrido desde el EPOCH.
**
** TODO Manejar los errores de 'gettimeofday' ya que pueden ser desencadenados desde
** el lado del usuario.
**
** @return El tiempo transcurrido desde el EPOCH en milisegundos.
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
** @brief     Devuelve el tiempo transcurrido desde el inicio de la simulación.
**
** @param[in] philo la estructura de la simulación.
** @return    El tiempo transcurrido desde el inicio de la simulación en milisegundos.
*/

unsigned long	ft_rel_time(unsigned long begin)
{
	unsigned long	abs_time;

	abs_time = ft_abs_time ();
	return (abs_time - begin);
}

/*
** @brief     Dormir en milisegundos.
**
** Dividiendo mi pausa en varias partes, corrijo un poco la imprecisión de USLEEP(3) para valores grandes. Restamos el residuo, el resto de imprecisión.
**
** @param[in] msec el tiempo en milisegundos.
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
