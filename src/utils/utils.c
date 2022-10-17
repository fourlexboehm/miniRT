/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:33:35 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:33:42 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//todo make sure this works right
void	get_sign(const char **str, int *neg)
{
	if (*(*str) == '-')
	{
		(*neg) = -1;
		++(*str);
	}
	else if (*(*str) == '+')
		++(*str);
}

static double	get_decimal(const char *str)
{
	double	decimal;
	double	weight;

	decimal = 0;
	weight = 1;
	while (*++str && *str != ',' && !ft_isspace(*str))
	{
		decimal *= 10;
		decimal += *str - '0';
		weight *= 10;
	}
	decimal /= weight;
	return (decimal);
}

double	ft_atof(const char *str)
{
	int		neg;
	double	value;
	double	decimal;

	neg = 1;
	while (ft_isspace(*str))
		str++;
	get_sign(&str, &neg);
	value = 0;
	while (*str != '.' && *str != ',' && !ft_isspace(*str))
	{
		if (!*str)
			return (neg * value);
		value *= 10;
		value += *str - '0';
		str++;
	}
	if (*str != '.')
		return (value * neg);
	decimal = get_decimal(str);
	return ((value + decimal) * neg);
}
