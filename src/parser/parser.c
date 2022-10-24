#include "../../includes/minirt.h"

int	is_inchar(char c)
{
	if (c == ' ' || c == '	' || c == '.' || c == ',' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	assign_ambient_light(t_scene *scene, char *line)
{
    int i;

	if (!check_line(line + 1, 4))
		return(0);
    i = 1;
    while (ft_isspace(line[i]))
		i++;
    i += get_double(&line[i], &scene->ambient_light.ambient);
    while (ft_isspace(line[i]))
		i++;
    get_rgba(&line[i], &scene->ambient_light.colour);
	return (1);
}

int	assign_camera(t_scene *scene, char *line)
{
	int i;

	if (!check_line(line + 1, 7))
		return(0);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->camera.pos);
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->camera.dir);
	i += get_double(&line[i], &scene->camera.fov);
	return (1);
}

int	assign_cylinder(t_scene *scene, char *line)
{
	int i;
	static int j = 0;

	if (!check_line(line + 2, 11))
		return(0);
	i = 1;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->cylinders[j].pos) - 1;
	i += get_vector(&line[i], &scene->cylinders[j].dir);
	i += get_double(&line[i], &scene->cylinders[j].diameter);
	i += get_double(&line[i], &scene->cylinders[j].height);
	i += get_rgba(&line[i], &scene->cylinders[j].colour);
	j++;
	return (1);
}

int	assign_sphere(t_scene *scene, char *line)
{
	int	i;
	static int	j = 0;

	if (!check_line(line + 2, 7))
		return(0);
	i = 1;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->spheres[j].pos);
	i += get_double(&line[i], &scene->spheres[j].diameter);
	i += get_rgba(&line[i], &scene->spheres[j].colour);
	j++;
	return (1);
}

int	assign_plane(t_scene *scene, char *line)
{
	int			i;
	static int	j = 0;

	if (!check_line(line + 2, 9))
		return(0);
	i = 1;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->planes[j].pos) - 1;
	i += get_vector(&line[i], &scene->planes[j].dir);
	i += get_rgba(&line[i], &scene->planes[j].colour);
	j++;
	return (1);
}