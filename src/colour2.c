/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:48:34 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:38:26 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * adds scalar to rgba. clamps rgba values to 0 - 255 using int.
 * used for lighting
 */
void	light_rgba(t_rgba *colour, double scalar)
{
	int	r;
	int	g;
	int	b;

	r = colour->r + scalar;
	g = colour->g + scalar;
	b = colour->b + scalar;
	if (r > 255)
		colour->r = 255;
	else if (r < 0)
		colour->r = 0;
	else
		colour->r = r;
	if (g > 255)
		colour->g = 255;
	else if (g < 0)
		colour->g = 0;
	else
		colour->g = g;
	if (b > 255)
		colour->b = 255;
	else if (b < 0)
		colour->b = 0;
	else
		colour->b = b;
}
