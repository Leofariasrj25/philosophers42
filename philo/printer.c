/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:02:42 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/14 19:51:52 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void	print_status(t_philo *philosopher, char *status)
{
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher->print_mutex);
	timestamp = getcurrtime_ms() - philosopher->matrix_start;
	printf("[%ld] %ld %s\n", timestamp, philosopher->philo_id, status);
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
