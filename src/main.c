/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:28:48 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:28:52 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	char		**line;
	t_scene		scene;
	t_vec		**v_matrix;
	int			**c_matrix;

	if (argc == 2)
		line = get_file(argv[1]);
	else
		line = get_file("scenes/subject_example3.rt");
	assign_scene(&scene, line);
	v_matrix = calculate_viewport_vectors(scene.camera);
	c_matrix = set_colour_matrix(v_matrix, scene);
	free2d_array((void **) line);
	render_image_on_mlx(c_matrix);
	free2d_array((void **) c_matrix);
}
