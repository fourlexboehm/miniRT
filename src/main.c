/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:28:48 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/24 17:39:10 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	assign_light(t_scene *scene, char *line)
{
	int i;
	static int j = 0;

	if (!check_line(line + 1, 7))
		return(0);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->lights[j].pos);
	i += get_double(&line[i], &scene->lights[j].brightness);
	i += get_rgba(&line[i], &scene->lights[j].colour);
	j++;
	return (1);
}

static void	malloc_objs(t_scene *scene)
{
	ft_printf("allocatting memory for objs");
	scene->spheres = ft_calloc(sizeof(t_sp), scene->n_spheres + 1);
	scene->cylinders = ft_calloc(sizeof(t_cy), scene->n_cylinders + 1);
	scene->planes = ft_calloc(sizeof(t_pl), scene->n_planes + 1);
	scene->lights = ft_calloc(sizeof(t_L), scene->n_lights + 1);
	ft_printf("...done\n");
}

void	assign_scene(t_scene *scene, char **line)
{
	int		i;
	int		j;

	get_n_obs(line, scene);
	malloc_objs(scene);
	i = -1;
	j = 1;
	ft_printf("assigning objs...");
	while (line[++i])
	{
		if (line[i][0] == 'A')
			j *= assign_ambient_light(scene, line[i] + 1);
		else if (line[i][0] == 'C')
			j *= assign_camera(scene, line[i] + 1);
		else if (line[i][0] == 'c')
			j *= assign_cylinder(scene, line[i] + 2);
		else if (line[i][0] == 's')
			j *= assign_sphere(scene, line[i] + 2);
		else if (line[i][0] == 'p')
			j *= assign_plane(scene, line[i] + 2);
		else if (line[i][0] == 'L')
			j *= assign_light(scene, line[i] + 1);
	}
	if (j == 1)
		ft_printf("done\n");
	else
		exit(printf("parser detected a miss config of an object\n"));
}

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
	l = ft_strlen(v[1]);
		if (l < 4 || v[1][l - 1] != 't' || v[1][l - 2] != 'r'
				|| v[1][l - 3] != '.')
			exit(ft_printf("Error: Invalid file extension\n"));
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
