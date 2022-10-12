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

//void	printf_ambient_light(t_ambient_light *ambient_light)
//{
//	printf("ambient_light value = %f\n", ambient_light->ambient);
//	printf("ambient_light R = %u\n", ambient_light->colour.r);
//	printf("ambient_light G = %u\n", ambient_light->colour.g);
//	printf("ambient_light B = %u\n", ambient_light->colour.b);
//	printf("\n");
//}
//
//void	printf_cam(t_camera *camera)
//{
//	printf("cam pos x = %f\n", camera->pos.x);
//	printf("cam pos y = %f\n", camera->pos.y);
//	printf("cam pos z = %f\n", camera->pos.z);
//	printf("cam dir x = %f\n", camera->dir.x);
//	printf("cam dir y = %f\n", camera->dir.y);
//	printf("cam dir z = %f\n", camera->dir.z);
//	printf("cam fov = %f\n", camera->fov);
//	printf("\n");
//}
//
//void	printf_sphere(t_sp *sphere)
//{
//	printf("sphere pos x = %f\n", sphere->pos.x);
//	printf("sphere pos y = %f\n", sphere->pos.y);
//	printf("sphere pos z = %f\n", sphere->pos.z);
//	printf("sphere diameter = %f\n", sphere->diameter);
//	printf("sphere R = %u\n", sphere->colour.r);
//	printf("sphere G = %u\n", sphere->colour.g);
//	printf("sphere B = %u\n", sphere->colour.b);
//	printf("\n");
//}
//
//void	printf_cylinder(t_cy *cylinder)
//{
//	printf("cylinder pos x = %f\n", cylinder->pos.x);
//	printf("cylinder pos y = %f\n", cylinder->pos.y);
//	printf("cylinder pos z = %f\n", cylinder->pos.z);
//	printf("cylinder dir x = %f\n", cylinder->dir.x);
//	printf("cylinder dir y = %f\n", cylinder->dir.y);
//	printf("cylinder dir z = %f\n", cylinder->dir.z);
//	printf("cylinder diameter = %f\n", cylinder->diameter);
//	printf("cylinder height = %f\n", cylinder->height);
//	printf("cylinder R = %u\n", cylinder->colour.r);
//	printf("cylinder G = %u\n", cylinder->colour.g);
//	printf("cylinder B = %u\n", cylinder->colour.b);
//	printf("\n");
//}
//
//void	printf_plane(t_pl *plane)
//{
//	printf("plane pos x = %f\n", plane->pos.x);
//	printf("plane pos y = %f\n", plane->pos.y);
//	printf("plane pos z = %f\n", plane->pos.z);
//	printf("plane dir x = %f\n", plane->dir.x);
//	printf("plane dir y = %f\n", plane->dir.y);
//	printf("plane dir z = %f\n", plane->dir.z);
//	printf("plane R = %u\n", plane->colour.r);
//	printf("plane G = %u\n", plane->colour.g);
//	printf("plane B = %u\n", plane->colour.b);
//	printf("\n");
//}
//
//void	printf_light(t_L *light)
//{
//	printf("light pos x = %f\n", light->pos.x);
//	printf("light pos y = %f\n", light->pos.y);
//	printf("light pos z = %f\n", light->pos.z);
//	printf("light brightness = %f\n", light->brightness);
//	printf("light R = %u\n", light->colour.r);
//	printf("light G = %u\n", light->colour.g);
//	printf("light B = %u\n", light->colour.b);
//	printf("\n");
//}
//
//void	printf_scene(t_scene *scene)
//{
//	int	i;
//
//	printf_ambient_light(&scene->ambient_light);
//	printf_cam(&scene->camera);
//	i = -1;
//	while (++i < scene->n_spheres)
//		printf_sphere(&scene->spheres[i]);
//	i = -1;
//	while (++i < scene->n_cylinders)
//		printf_cylinder(&scene->cylinders[i]);
//	i = -1;
//	while (++i < scene->n_planes)
//		printf_plane(&scene->planes[i]);
//	i = -1;
//	while (++i < scene->n_lights)
//		printf_light(&scene->lights[i]);
//	i = -1;
//}
