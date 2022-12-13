/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:50:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 21:56:03 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

#ifndef U_INT_MAX
# define U_INT_MAX 4294967295
#endif 

int	check_input_size(int argc);
int	get_input(int argc, char **argv, int *values);
int	check_input_values(int argc, char **argv, int *values);

int	get_input(int argc, char **argv, int *values)
{
	char	*err_msg;
	char	*usage;
	int		ret_code;

	usage = "{USAGE}: ./philo <nº of philosophers> <time to die> <time to eat> \
		<time to sleep> [nº of times every philo must eat]\n";
	if (check_input_size(argc))
	{
		err_msg = "{ERROR}: wrong number of arguments\n";
		put_err_str(err_msg);
		put_err_str(usage);
		return (1);
	}
	ret_code = check_input_values(argc, argv, values);
	if (ret_code == 2)
	{
		err_msg = "{ERROR}: arg(s) must be greater than zero\n";
		put_err_str(err_msg);
	}
	if (ret_code == 3)
	{
		err_msg = "{ERROR}: out of bounds integer value\n";
		put_err_str(err_msg);
	}
	return (ret_code);
}

int	check_input_values(int argc, char **argv, int *values)
{
	long long	number;
	int			i;

	i = 1;
	while (i < argc)
	{
		number = ft_atoll(argv[i]);
		if (number <= 0)
			return (2);
		else if (number > U_INT_MAX)
			return (3);
		else
			values[i - 1] = (unsigned int) number;
		i++;
	}
	return (0);
}

int	check_input_size(int argc)
{
	if (!((argc - 1) == 5 || (argc - 1) == 4))
		return (1);
	else
		return (0);
}
