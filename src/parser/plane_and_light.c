#include "../../includes/minirt.h"

void	assign_more_plane(const t_scene *scene, const char *line, int j, int *i)
{
	while (line[j++] != ',')
		;
	scene->planes[*i].dir.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[*i].dir.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->planes[*i].colour.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[*i].colour.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[*i].colour.b = ft_atoi(&line[j]);
	(*i)++;
}

void	assign_plane(t_scene *scene, char *line)
{
	int			j;
	static int	i = 0;

	j = 2;
	ft_printf("	assign_plane");
	while (ft_isspace(line[j]))
		j++;
	scene->planes[i].pos.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[i].pos.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[i].pos.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	scene->planes[i].dir.x = ft_atof(&line[j]);
	assign_more_plane(scene, line, j, &i);
	ft_printf("...done\n");
}

void	assign_more_light(const t_scene *scene, const char *line, int j, int *i)
{
	while (ft_isspace(line[j]))
		j++;
	scene->lights[*i].brightness = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;
	scene->lights[*i].colour.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->lights[*i].colour.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->lights[*i].colour.b = ft_atoi(&line[j]);
	(*i)++;
	ft_printf("...done\n");
}

void	assign_light(t_scene *scene, char *line)
{
	int			j;
	static int	i = 0;

	j = 1;
	ft_printf("	assign_light");
	while (ft_isspace(line[j]))
		j++;
	scene->lights[i].pos.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->lights[i].pos.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->lights[i].pos.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	assign_more_light(scene, line, j, &i);
}
