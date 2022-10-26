/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:58:42 by aboehm            #+#    #+#             */
/*   Updated: 2022/10/26 10:58:44 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	**get_file(char *path)
{
	int		i;
	int		fd;
	char	**line;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("failed to read file\n");
		exit(0);
	}
	line = malloc(1000);
	i = -1;
	while (1)
	{
		line[++i] = get_next_line(fd);
		if (!line[i])
			break ;
	}
	return (line);
}

void	get_n_obs(char **line, t_scene *scene)
{
	int	i;
	int	num;

	num = 0;
	(void)num;
	i = -1;
	ft_printf("getting num of objs...");
	scene->n_spheres = 0;
	scene->n_planes = 0;
	scene->n_cylinders = 0;
	scene->n_lights = 0;
	while (line[++i])
	{
		if (line[i][0] == 's')
			scene->n_spheres++;
		if (line[i][0] == 'p')
			scene->n_planes++;
		if (line[i][0] == 'c')
			scene->n_cylinders++;
		if (line[i][0] == 'L')
			scene->n_lights++;
	}
	ft_printf("done\n");
}

int	assign_light(t_scene *scene, char *line)
{
	int			i;
	static int	j = 0;

	if (!check_line(line, 7))
		return (0);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->lights[j].pos);
	i += get_double(&line[i], &scene->lights[j].brightness);
	i += get_rgba(&line[i], &scene->lights[j].colour);
	j++;
	return (1);
}

int	get_double(char *str, double *d)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	*d = atof(&str[i]);
	while (!ft_isspace(str[i]))
		i++;
	return (i);
}

void	cy_utils(t_cy *cy)
{
	cy->radius2 = cy->diameter * cy->diameter;
	cy->pos2 = add_vec(cy->pos, scale_vec(cy->dir, cy->height));
}
