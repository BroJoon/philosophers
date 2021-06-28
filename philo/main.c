/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:06:55 by hyungjki          #+#    #+#             */
/*   Updated: 2021/06/28 11:11:16 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_info *g_info;

int		until(t_philo *philo)
{
	int		count;
	int		right;
	int		left;

	if (g_info->end)
		return (0);
	count = g_info->philo_count;
	right = (philo->num - 1 == -1) ? count - 1 : philo->num - 1;
	left = (philo->num + 1 == count) ? 0 : philo->num + 1;
	if (g_info->philos[right].last_eat < philo->last_eat)
		return (1);
	else if (g_info->philos[left].last_eat < philo->last_eat)
		return (1);
	return (0);
}

void	*philo_thread(void *arg)
{
	int			lf;
	int			rf;
	t_philo		*philo;

	philo = arg;
	lf = (philo->num % 2 ? philo->num : philo->num + 1) % g_info->philo_count;
	rf = (philo->num % 2 ? philo->num + 1 : philo->num) % g_info->philo_count;
	if (philo->num % 2 == 1)
		usleep(200);
	philo->last_eat = get_timestamp();
	while (!g_info->end)
	{
		pickup_fork(lf, rf, philo->num);
		if (g_info->end)
			return (NULL);
		print_log(philo->num, LOG_EAT);
		philo->last_eat = get_timestamp();
		return_fork(lf, rf, philo);
		if (g_info->end)
			return (NULL);
		print_log(philo->num, LOG_SLEEP);
		while (until(philo))
			usleep(50);
	}
	return (NULL);
}

int		set_philos(void)
{
	int				i;
	unsigned long	t;

	if (!(g_info->philos = malloc(sizeof(t_philo) * g_info->philo_count)))
		return (1);
	i = -1;
	t = init_timestamp();
	while (++i < g_info->philo_count)
	{
		g_info->philos[i].time_eat = 0;
		g_info->philos[i].last_eat = t;
		g_info->philos[i].num = i;
	}
	return (0);
}

int		philo(int i)
{
	pthread_t	*tids;
	pthread_t	monitor_tid;

	if (set_philos())
		return (1);
	if (init_mutexs(g_info->philo_count))
		return (1);
	if (!(tids = malloc(sizeof(pthread_t) * (g_info->philo_count + 1))))
	{
		free(g_info->philos);
		free(g_info->mutexes);
		return (1);
	}
	g_info->start_time = init_timestamp();
	while (++i < g_info->philo_count)
	{
		pthread_create(&tids[i], NULL, philo_thread, &g_info->philos[i]);
		pthread_detach(tids[i]);
	}
	pthread_create(&monitor_tid, NULL, monitor_thread, NULL);
	pthread_join(monitor_tid, NULL);
	destroy_mutexs(g_info->philo_count);
	free(tids);
	return (0);
}

int		main(int argc, char **argv)
{
	int i;

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
	i = philo(-1);
	free(g_info);
	return (i);
}
