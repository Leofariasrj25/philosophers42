/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:02:42 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/18 19:46:33 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void	print_status(t_philo *philosopher, char *status, int code)
{
	long	timestamp;

	pthread_mutex_lock(philosopher->print_mutex);
	timestamp = get_timestamp_ms(philosopher->matrix_start);
	pthread_mutex_lock(philosopher->banquet->dinner_mutex);
	if (code == PHILO_DEAD && philosopher->banquet->is_over == 0)
	{	
		philosopher->banquet->is_over = 1;
		printf("[%ld] %ld %s\n", timestamp, philosopher->philo_id, status);
	}
	if (code != PHILO_DEAD && philosopher->banquet->is_over == 0)
		printf("[%ld] %ld %s\n", timestamp, philosopher->philo_id, status);
	pthread_mutex_unlock(philosopher->banquet->dinner_mutex);
	pthread_mutex_unlock(philosopher->print_mutex);
}

void	put_str_fd(int fd, char *str)
{
	int	len;

	if (!str)
		return ;
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

void	put_err_str(char *str)
{
	if (!str)
		return ;
	put_str_fd(2, str);
}
