/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:35:21 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:35:23 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	**get_file(char *path)
{
	int		i;
	int		fd;
	char	**line;

	ft_printf("opening scene..");
	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("failed to read file\n");
		exit(0);
	}
	ft_printf(".%d\n", fd);
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

void	set_vec(t_vec *vec, char *line, int *j)
{
	vec->x = ft_atof(&line[*j]);
	while (line[(*j)++] != ',')
		;
	vec->y = ft_atof(&line[*j]);
	while (line[(*j)++] != ',')
		;
	vec->z = ft_atof(&line[*j]);
}

void	next_num(char *line, int *j)
{
	while (!ft_isspace(line[*j]))
		(*j)++;
	while (ft_isspace(line[*j]))
		(*j)++;
}

void	get_n_obs(char **line, t_scene *scene)
{
	int	i;
	int	num;

	num = 0;
	(void)num;
	i = -1;
	ft_printf("getting num of objs");
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
	ft_printf("...done\n");
}
