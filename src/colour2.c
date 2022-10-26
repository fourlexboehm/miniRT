/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:48:34 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/26 12:49:38 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

/**
 * adds scalar to rgba. clamps rgba values to 0 - 255 using int.
 * used for lighting
 */
t_rgba	light_rgba(t_rgba colour, double scalar)
{
	t_rgba	new;
	int		r;
	int		g;
	int		b;

	r = colour.r + scalar;
	g = colour.g + scalar;
	b = colour.b + scalar;
	new.r = max(min(r, 255), 0);
	new.g = max(min(g, 255), 0);
	new.b = max(min(b, 255), 0);
	return (new);
}

t_rgba	color_mixer(t_rgba c1, t_rgba c2)
{
	t_rgba	new;
	int		r;
	int		g;
	int		b;

	r = min((c1.r + c2.r), 255);
	g = min((c1.g + c2.g), 255);
	b = min((c1.b + c2.b), 255);
	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}
