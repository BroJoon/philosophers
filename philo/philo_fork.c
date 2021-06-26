/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 07:21:22 by hyungjki          #+#    #+#             */
/*   Updated: 2021/06/26 20:13:44 by hyungjki         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		init_mutexs(int fork_count)
{
	int	i;

	i = 0;
	if (!(g_info->mutexes = malloc(sizeof(pthread_mutex_t) * fork_count)))
	{
		free(g_info->philos);
		return (1);
	}
	while (i < fork_count)
	{
		pthread_mutex_init(&g_info->mutexes[i], NULL);
		i++;
	}
	return (0);
}

void	pickup_fork(int n, int k, int philo)
{
	pthread_mutex_lock(&g_info->mutexes[n]);
	if (!g_info->end)
		print_log(philo, LOG_FORK);
	pthread_mutex_lock(&g_info->mutexes[k]);
	if (!g_info->end)
		print_log(philo, LOG_FORK);
}

void	return_fork(int n, int k, t_philo *philo)
{
	philo->time_eat++;
	pthread_mutex_unlock(&g_info->mutexes[n]);
	pthread_mutex_unlock(&g_info->mutexes[k]);
}

void	destroy_mutexs(int fork_count)
{
	int	i;

	i = 0;
	while (i < fork_count)
	{
		pthread_mutex_destroy(&g_info->mutexes[i]);
		i++;
	}
	free(g_info->mutexes);
	free(g_info->philos);
}
