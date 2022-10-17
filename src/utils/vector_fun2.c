/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fun2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:31:32 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:47:04 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * returns dot product of two vectors
 */
double	dot(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/**
 * returns length SQUARED product of a vector
 */
double	length_squared(t_vec const v3)
{
	return (v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
}

/**
 * returns length product of a vector
 */
double	length(t_vec const v3)
{
	return (sqrt(length_squared(v3)));
}

t_vec	new_vector3(double x, double y, double z)
{
	t_vec	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}

/**
 * returns distance between two vectors
 */
double get_distance(t_vec v1, t_vec v2)
{
	return(sqrt((pow(v2.x - v1.x, 2) + 
		pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2))));
}
