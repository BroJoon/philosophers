/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:07:41 by hyungjki          #+#    #+#             */
/*   Updated: 2021/06/28 11:07:44 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

int		is_philo_death(void)
{
	int				i;
	unsigned int	j;

	i = 0;
	j = get_timestamp();
	while (i < g_info->philo_count)
	{
		if ((int)(j - g_info->philos[i].last_eat) > \
		g_info->time_to_die)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int		is_must_eat(void)
{
	int				i;

	i = 0;
	while (i < g_info->philo_count)
	{
		if (g_info->philos[i].time_eat < g_info->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_thread(void *arg)
{
	int				n;

	(void)arg;
	while (1)
	{
		if ((n = is_philo_death()) != -1)
		{
			g_info->end = 1;
			print_log(n, LOG_DIE);
			break ;
		}
		if (g_info->must_eat != -1 && is_must_eat())
		{
			g_info->end = 1;
			break ;
		}
		usleep(200);
	}
	usleep(2000);
	return (0);
}

void	ft_sleep(int milis)
{
	unsigned long	start_time;

	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < (unsigned long)milis &&
		!(g_info->end))
	{
		usleep(50);
	}
}
