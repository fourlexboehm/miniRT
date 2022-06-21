#include "../includes/minirt.h"

static double	get_decimal(const char *str)
{
	double	decimal;
	double	weight;

	decimal = 0;
	weight = 1;
	while (*++str)
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
	if (*str == '-')
	{
		neg = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	value = 0;
	while (*str != '.')
	{
		if (!*str)
			return (neg * value);
		value *= 10;
		value += *str - '0';
		str++;
	}
	decimal = get_decimal(str);
	return ((value + decimal) * neg);
}
