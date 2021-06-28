/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:10:42 by hyungjki          #+#    #+#             */
/*   Updated: 2021/06/28 11:10:44 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_sem(int fork_count)
{
	sem_unlink("forks");
	g_info->sem_forks = sem_open("forks", O_CREAT, S_IRWXU, fork_count);
	sem_unlink("lock");
	g_info->sem_lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
}

void	pickup_fork(int philo)
{
	sem_wait(g_info->sem_lock);
	sem_wait(g_info->sem_forks);
	print_log(philo, LOG_FORK);
	sem_wait(g_info->sem_forks);
	print_log(philo, LOG_FORK);
	sem_post(g_info->sem_lock);
}

void	return_fork(void)
{
	sem_post(g_info->sem_forks);
	sem_post(g_info->sem_forks);
}

void	destroy_sem(void)
{
	sem_close(g_info->sem_forks);
	sem_close(g_info->sem_lock);
	sem_close(g_info->sem_end);
	sem_close(g_info->sem_stop);
}

void	ft_sleep(int milis)
{
	unsigned long	start_time;

	start_time = get_timestamp();
	while (get_timestamp() - start_time < (unsigned long)milis)
		usleep(50);
}
