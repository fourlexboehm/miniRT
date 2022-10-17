/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:35:08 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:35:10 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	assign_ambient_light(t_scene *scene, char *line)
{
	int			j;

	j = 1;
	ft_printf("	assign_ambient_light");
	while (ft_isspace(line[j]))
		j++;
	scene->ambient_light.ambient = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->ambient_light.colour.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->ambient_light.colour.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->ambient_light.colour.b = ft_atoi(&line[j]);
	ft_printf("...done\n");
}

void	assign_more_camera(t_scene *scene, const char *line, int j)
{
	while (ft_isspace(line[j]))
		j++;
	scene->camera.dir.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->camera.dir.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->camera.dir.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->camera.fov = ft_atof(&line[j]);
}

void	assign_camera(t_scene *scene, char *line)
{
	int			j;

	j = 1;
	ft_printf("	assign_camera");
	while (ft_isspace(line[j]))
		j++;
	scene->camera.pos.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->camera.pos.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->camera.pos.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	assign_more_camera(scene, line, j);
	ft_printf("...done\n");
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

	get_n_obs(line, scene);
	malloc_objs(scene);
	i = -1;
	ft_printf("assigning objs\n");
	while (line[++i])
	{
		if (line[i][0] == 'A')
			assign_ambient_light(scene, line[i]);
		if (line[i][0] == 'C')
			assign_camera(scene, line[i]);
		if (line[i][0] == 'c')
			assign_cylinder(scene, line[i]);
		else if (line[i][0] == 's')
			assign_sphere(scene, line[i]);
		else if (line[i][0] == 'p')
			assign_plane(scene, line[i]);
		else if (line[i][0] == 'L')
			assign_light(scene, line[i]);
	}
	ft_printf("done\n");
}
