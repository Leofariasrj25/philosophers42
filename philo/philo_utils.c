/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:17:09 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/01 19:02:25 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

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
