/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:31:12 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:31:16 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
*	Setting all the vectors from the two vertical borders from the vectors
*	of the 4 corners.
 *	first calculate the difference between the two corners
 *	then divide by the number of pixels to get the difference per pixel
 *	then add the difference to the first corner to get the final vector
*/
static void	set_cam_vertical_borders(t_vec **matrix)
{
	int		ctr;
	int		max_x;
	int		max_y;
	t_vec	diff_left;
	t_vec	diff_right;

	ctr = 1;
	max_x = WIN_WIDTH - 1;
	max_y = WIN_HEIGHT - 1;
	diff_left = sub_vec(matrix[0][max_y], matrix[0][0]);
	diff_right = sub_vec(matrix[max_x][max_y], matrix[max_x][0]);
	while (ctr < WIN_HEIGHT)
	{
		matrix[0][ctr] = add_vec(matrix[0][0], scale_vec(
					diff_left, (double)ctr / (double)(max_y)));
		matrix[max_x][ctr] = add_vec(matrix[max_x][0],
				scale_vec(diff_right, (double)ctr / (double)(max_y)));
		ctr++;
	}
}

/*
*	Setting all the other vectors knowing the vectors of the margins
*	(right and left).
*/
static void	set_cam_middle(t_vec **matrix)
{
	int		ctr_x;
	int		ctr_y;
	int		max_x;
	t_vec	diff;

	ctr_y = 0;
	max_x = WIN_WIDTH - 1;
	while (ctr_y < WIN_HEIGHT)
	{
		ctr_x = -1;
		diff = sub_vec(matrix[max_x][ctr_y], matrix[0][ctr_y]);
		while (++ctr_x < max_x)
			matrix[ctr_x][ctr_y] = add_vec(matrix[0][ctr_y],
					scale_vec(diff, (double)ctr_x / (max_x)));
		ctr_y++;
	}
}

/**
 * @brief Sets the camera matrix.
 * This matrix is used to project the scene	to the viewport.
 * @param corn	The corners of the scene.
 * @return 		The camera matrix.
 */
t_vec	**set_cam_vectors(t_corners corn)
{
	t_vec	**matrix;
	int		ctr;

	matrix = ft_calloc(sizeof(t_vec *), WIN_WIDTH + 1);
	ctr = 0;
	while (ctr < WIN_WIDTH)
	{
		matrix[ctr] = ft_calloc(sizeof(t_vec), WIN_HEIGHT + 1);
		ctr++;
	}
	matrix[0][0] = corn.tl;
	matrix[WIN_WIDTH - 1][0] = corn.tr;
	matrix[0][WIN_HEIGHT - 1] = corn.bl;
	matrix[WIN_WIDTH - 1][WIN_HEIGHT - 1] = corn.br;
	set_cam_vertical_borders(matrix);
	set_cam_middle(matrix);
	return (matrix);
}
