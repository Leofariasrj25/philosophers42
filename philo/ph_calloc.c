/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:38:32 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 21:53:33 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <string.h>

void	*ph_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}

int	test_alloc(void *ptr)
{
	if (!ptr)
	{
		put_err_str("{ERROR}: malloc malfunction");
		return (-1);
	}
	return (0);
}

int	thread_start(pthread_t *thread, void *(f)(void *), void *param)
{
	if (!thread || pthread_create(thread, NULL, f, param) != 0)
	{
		put_err_str("{ERROR}: Could not start thread");
		return (-1);
	}
	return (0);
}

int	mutex_start(pthread_mutex_t *mutex)
{
	if (!mutex || pthread_mutex_init(mutex, NULL) != 0)
	{
		put_err_str("{ERROR}: mutex initialization failed");
		return (-1);
	}	
	return (0);
}
