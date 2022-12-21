/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:01:50 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/21 18:21:44 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

static int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	check_signal(const char *str, int *i)
{
	int	signal;

	signal = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			signal *= -1;
		*i = *i + 1;
	}
	return (signal);
}

long long	*clean_ret(long long *ret)
{
	free(ret);
	return (NULL);
}

long long	*ft_atoll(const char *str)
{
	long long	res;
	int			signal;
	int			i;
	long long	*ret;

	ret = NULL;
	res = 0;
	signal = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	signal = check_signal(str, &i);
	if (str[i] != '\0' || is_digit(str[i]))
		ret = malloc(sizeof(long long));
	else
		return (NULL);
	while (is_digit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' || !ret)
		return (clean_ret(ret));
	*ret = res * signal;
	return (ret);
}
