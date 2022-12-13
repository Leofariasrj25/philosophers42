/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:01:50 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 21:58:46 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long long	ft_atoll(char *str)
{
	long long	number;
	int			i;
	int			signal;

	if (!str)
		return (0);
	i = 0;
	signal = 1;
	number = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal = -1;
	}
	while (is_digit(str[i]))
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (number * signal);
}
