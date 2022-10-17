/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_and_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:34:19 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:34:26 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	assign_more_sphere(const t_scene *scene,
		const char *line, int j, int *i)
{
	while (ft_isspace(line[j]))
		j++;
	scene->spheres[*i].diameter = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->spheres[*i].colour.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->spheres[*i].colour.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->spheres[*i].colour.b = ft_atoi(&line[j]);
	(*i)++;
}

void	assign_sphere(t_scene *scene, char *line)
{
	int			j;
	static int	i = 0;

	j = 2;
	ft_printf("	assign_sphere");
	while (ft_isspace(line[j]))
		j++;
	scene->spheres[i].pos.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->spheres[i].pos.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->spheres[i].pos.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	assign_more_sphere(scene, line, j, &i);
	ft_printf("...done\n");
}

static void	assign_more_cyl(t_scene *scene, const char *line, int j, int *i)
{
	scene->cylinders[*i].dir.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->cylinders[*i].diameter = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->cylinders[*i].height = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->cylinders[*i].colour.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[*i].colour.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[*i].colour.b = ft_atoi(&line[j]);
	(*i)++;
}

void	assign_cylinder(t_scene *scene, char *line)
{
	int			j;
	static int	i = 0;

	j = 2;
	ft_printf("	assign_cylinder");
	while (ft_isspace(line[j]))
		j++;
	scene->cylinders[i].pos.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].pos.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].pos.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->cylinders[i].dir.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].dir.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	assign_more_cyl(scene, line, j, &i);
}
