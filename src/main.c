#include "../includes/minirt.h"
#include <fcntl.h>

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

void set_vector3(t_vector3 *vec, char *line, int *j)
{
	vec->x = ft_atof(&line[*j]);
	while (line[(*j)++] != ',')
		;
	vec->y = ft_atof(&line[*j]);
	while (line[(*j)++] != ',')
		;
	vec->z = ft_atof(&line[*j]);
}

void next_num(char *line, int *j)
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
	ft_printf("	n_spheres = %d\n", scene->n_spheres);
	ft_printf("	n_planes = %d\n", scene->n_planes);
	ft_printf("	n_cylinders = %d\n", scene->n_cylinders);
	ft_printf("	n_lights = %d\n", scene->n_lights);
}

void	assign_ambient_light(t_scene *scene, char *line)
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


	scene->ambient_light.color.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->ambient_light.color.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->ambient_light.color.b = ft_atoi(&line[j]);
	ft_printf("...done\n");
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
	while (ft_isspace(line[j]))
		j++;
	
	
	scene->camera.rot.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->camera.rot.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->camera.rot.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;

	scene->camera.fov = ft_atof(&line[j]);
	ft_printf("...done\n");
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
	while (ft_isspace(line[j]))
		j++;


	scene->spheres[i].diameter = ft_atof(&line[j]);


	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;

	scene->spheres[i].color.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->spheres[i].color.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->spheres[i].color.b = ft_atoi(&line[j]);
	i++;
	ft_printf("...done\n");
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

	
	scene->cylinders[i].rot.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].rot.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].rot.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;


	scene->cylinders[i].diameter = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;

	
	scene->cylinders[i].height = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;

	scene->cylinders[i].color.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].color.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->cylinders[i].color.b = ft_atoi(&line[j]);
	i++;
	ft_printf("...done\n");
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
	while (ft_isspace(line[j]))
		j++;

	
	scene->planes[i].rot.x = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[i].rot.y = ft_atof(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[i].rot.z = ft_atof(&line[j]);
	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;


	scene->planes[i].color.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[i].color.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->planes[i].color.b = ft_atoi(&line[j]);
	i++;
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
	while (ft_isspace(line[j]))
		j++;


	scene->lights[i].brightness = ft_atof(&line[j]);


	while (!ft_isspace(line[j]))
		j++;
	while (ft_isspace(line[j]))
		j++;

	scene->lights[i].color.r = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->lights[i].color.g = ft_atoi(&line[j]);
	while (line[j++] != ',')
		;
	scene->lights[i].color.b = ft_atoi(&line[j]);
	i++;
	ft_printf("...done\n");
}

void	malloc_objs(t_scene *scene)
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


void	printf_ambient_light(t_ambient_light *ambient_light)
{
	printf("ambient_light value = %f\n", ambient_light->ambient);
	printf("ambient_light R = %u\n", ambient_light->color.r);
	printf("ambient_light G = %u\n", ambient_light->color.g);
	printf("ambient_light B = %u\n", ambient_light->color.b);
	printf("\n");
}

void	printf_cam(t_camera *camera)
{
	printf("cam pos x = %f\n", camera->pos.x);
	printf("cam pos y = %f\n", camera->pos.y);
	printf("cam pos z = %f\n", camera->pos.z);
	printf("cam rot x = %f\n", camera->rot.x);
	printf("cam rot y = %f\n", camera->rot.y);
	printf("cam rot z = %f\n", camera->rot.z);
	printf("cam fov = %f\n", camera->fov);
	printf("\n");
}

void	printf_sphere(t_sp *sphere)
{
	printf("sphere pos x = %f\n", sphere->pos.x);
	printf("sphere pos y = %f\n", sphere->pos.y);
	printf("sphere pos z = %f\n", sphere->pos.z);
	printf("sphere diameter = %f\n", sphere->diameter);
	printf("sphere R = %u\n", sphere->color.r);
	printf("sphere G = %u\n", sphere->color.g);
	printf("sphere B = %u\n", sphere->color.b);
	printf("\n");
}

void	printf_cylinder(t_cy *cylinder)
{
	printf("cylinder pos x = %f\n", cylinder->pos.x);
	printf("cylinder pos y = %f\n", cylinder->pos.y);
	printf("cylinder pos z = %f\n", cylinder->pos.z);
	printf("cylinder rot x = %f\n", cylinder->rot.x);
	printf("cylinder rot y = %f\n", cylinder->rot.y);
	printf("cylinder rot z = %f\n", cylinder->rot.z);
	printf("cylinder diameter = %f\n", cylinder->diameter);
	printf("cylinder height = %f\n", cylinder->height);
	printf("cylinder R = %u\n", cylinder->color.r);
	printf("cylinder G = %u\n", cylinder->color.g);
	printf("cylinder B = %u\n", cylinder->color.b);
	printf("\n");
}

void	printf_plane(t_pl *plane)
{
	printf("plane pos x = %f\n", plane->pos.x);
	printf("plane pos y = %f\n", plane->pos.y);
	printf("plane pos z = %f\n", plane->pos.z);
	printf("plane rot x = %f\n", plane->rot.x);
	printf("plane rot y = %f\n", plane->rot.y);
	printf("plane rot z = %f\n", plane->rot.z);
	printf("plane R = %u\n", plane->color.r);
	printf("plane G = %u\n", plane->color.g);
	printf("plane B = %u\n", plane->color.b);
	printf("\n");
}

void	printf_light(t_L *light)
{
	printf("light pos x = %f\n", light->pos.x);
	printf("light pos y = %f\n", light->pos.y);
	printf("light pos z = %f\n", light->pos.z);
	printf("light brightness = %f\n", light->brightness);
	printf("light R = %u\n", light->color.r);
	printf("light G = %u\n", light->color.g);
	printf("light B = %u\n", light->color.b);
	printf("\n");
}

void	printf_scene(t_scene *scene)
{
	int	i;

	printf_ambient_light(&scene->ambient_light);
	printf_cam(&scene->camera);
	i = -1;
	while (++i < scene->n_spheres)
		printf_sphere(&scene->spheres[i]);
	i = -1;
	while (++i < scene->n_cylinders)
		printf_cylinder(&scene->cylinders[i]);
	i = -1;
	while (++i < scene->n_planes)
		printf_plane(&scene->planes[i]);
	i = -1;
	while (++i < scene->n_lights)
		printf_light(&scene->lights[i]);
	i = -1;
}

int	main(void)
{
	char	**line;
	t_scene	scene;

	line = get_file("scenes/1.rt");
	assign_scene(&scene, line);
	calculate_viewport_vectors(scene.camera);
	//ray_tracer();
	//render_image_on_mlx(colour_image);
	printf_scene(&scene);
	ft_printf("done.exe\n");





	t_vector3 v1;
	v1.x = 19;
	v1.y = 420;
	v1.z = 5;

	t_vector3 v2;
	v2.x = 16;
	v2.y = 52;
	v2.z = 91;


	printf("rad is = %lf\n", get_coord_rad_vector3(&v1, &v2));
	printf("deg is = %lf\n", get_coord_deg_vector3(&v1, &v2));





}