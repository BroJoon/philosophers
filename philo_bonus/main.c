/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 07:54:19 by hyungjki          #+#    #+#             */
/*   Updated: 2021/06/27 01:22:28 by hyungjki         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

t_info *g_info;

void	*philo_thread_monitor(void *arg)
{
	t_philo *philo;
	int		flag;

	flag = 0;
	philo = arg;
	while (!is_philo_death(philo))
	{
		if (!flag)
			flag = is_must_eat(philo);
		usleep(50);
	}
	return (NULL);
}

void	*philo_thread(t_philo *philo)
{
	pthread_t tid;

	pthread_create(&tid, NULL, philo_thread_monitor, philo);
	pthread_detach(tid);
	philo->last_eat = get_timestamp();
	while (1)
	{
		pickup_fork(philo->num);
		print_log(philo->num, LOG_EAT);
		ft_sleep(g_info->time_to_eat);
		philo->last_eat = get_timestamp();
		philo->time_eat++;
		return_fork();
		print_log(philo->num, LOG_SLEEP);
		ft_sleep(g_info->time_to_sleep);
		print_log(philo->num, LOG_THINK);
		usleep(200);
	}
	return (0);
}

void	set_philos(void)
{
	int				i;
	unsigned long	t;

	i = -1;
	if (!(g_info->philos = malloc(sizeof(t_philo) * g_info->philo_count)))
		exit(1);
	t = init_timestamp();
	while (++i < g_info->philo_count)
	{
		g_info->philos[i].last_eat = t;
		g_info->philos[i].time_eat = 0;
		g_info->philos[i].num = i;
	}
}

void	philo(void)
{
	pid_t		*pids;
	int			i;

	init_monitor();
	if (!(pids = malloc(sizeof(pid_t) * (g_info->philo_count + 3))))
		exit(1);
	init_sem(g_info->philo_count);
	i = -1;
	set_philos();
	g_info->start_time = init_timestamp();
	while (++i < g_info->philo_count)
	{
		if ((pids[i] = fork()) == 0)
		{
			philo_thread(&g_info->philos[i]);
			exit(1);
		}
	}
	monitor_thread(pids);
	destroy_sem();
	free(g_info->philos);
	free(pids);
}

int		main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong arguments!\n");
		return (1);
	}
	if (!(g_info = malloc(sizeof(t_info))))
		return (1);
	memset(g_info, 0, sizeof(t_info));
	g_info->philo_count = ft_atoi(argv[1]);
	g_info->must_eat = argc == 6 ? ft_atoi(argv[5]) : -1;
	if (g_info->philo_count < 1 || ((argc == 6) && g_info->must_eat < 1))
	{
		printf("Error: wrong arguments!\n");
		free(g_info);
		return (1);
	}
	g_info->time_to_die = ft_atoi(argv[2]);
	g_info->time_to_eat = ft_atoi(argv[3]);
	g_info->time_to_sleep = ft_atoi(argv[4]);
	philo();
	free(g_info);
	return (0);
}
