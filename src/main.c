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

int	main(int argc, char **v)
{
	char		**line;
	t_scene		scene;
	t_vec		**v_matrix;
	int			**c_matrix;
	int			l;

	l = 0;
	if (argc == 2)
	{
	l = strlen(v[1]);
		if (l < 4 || v[1][l - 1] != 't' || v[1][l - 2] != 'r'
				|| v[1][l - 3] != '.')
			exit(printf("Error: Invalid file extension\n"));
		line = get_file(v[1]);
	}
	else
		line = get_file("scenes/subject_example3.rt");
	assign_scene(&scene, line);
	v_matrix = calculate_viewport_vectors(scene.camera);
	c_matrix = set_colour_matrix(v_matrix, scene);
	free2d_array((void **) line);
	render_image_on_mlx(c_matrix);
	free2d_array((void **) c_matrix);
}
