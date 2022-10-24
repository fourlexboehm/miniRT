#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int ft_isspace(char c)
{
	if (c == ' ' || c == '	')
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
    printf("A B:%lf   r:%i g:%i b:%i\n",
	scene->ambient_light.ambient,
	scene->ambient_light.colour.r,
	scene->ambient_light.colour.g,
	scene->ambient_light.colour.b);
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
	printf("C x:%lf	y:%lf	z:%lf	dx:%lf	dy:%lf	dz:%lf	fov:%lf\n",
	scene->camera.pos.x,
	scene->camera.pos.y,
	scene->camera.pos.z,
	scene->camera.dir.x,
	scene->camera.dir.y,
	scene->camera.dir.z,
	scene->camera.fov);
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
	printf("cy x:%lf y:%lf z:%lf	dx:%lf dy:%lf dz:%lf	dia:%lf, hei:%lf	r:%i g:%i b:%i\n",
	scene->cylinders[j].pos.x,
	scene->cylinders[j].pos.y,
	scene->cylinders[j].pos.z,
	scene->cylinders[j].dir.x,
	scene->cylinders[j].dir.y,
	scene->cylinders[j].dir.z,
	scene->cylinders[j].diameter,
	scene->cylinders[j].height,
	scene->cylinders[j].colour.r,
	scene->cylinders[j].colour.g,
	scene->cylinders[j].colour.b);
	j++;
	return (1);
}

int	assign_sphere(t_scene *scene, char *line)
{
	int i;
	static int j = 0;

	if (!check_line(line + 2, 7))
		return(0);
	i = 1;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->spheres[j].pos);
	i += get_double(&line[i], &scene->spheres[j].diameter);
	i += get_rgba(&line[i], &scene->spheres[j].colour);
	printf("sp x:%lf y:%lf z:%lf	dia:%lf	r:%i g:%i b:%i\n",
	scene->spheres[j].pos.x,
	scene->spheres[j].pos.y,
	scene->spheres[j].pos.z,
	scene->spheres[j].diameter,
	scene->spheres[j].colour.r,
	scene->spheres[j].colour.g,
	scene->spheres[j].colour.b);
	j++;
	return (1);
}

int	assign_plane(t_scene *scene, char *line)
{
	int i;
	static int j = 0;

	if (!check_line(line + 2, 9))
		return(0);
	i = 1;
	while (ft_isspace(line[i]))
		i++;
	i += get_vector(&line[i], &scene->planes[j].pos) - 1;
	i += get_vector(&line[i], &scene->planes[j].dir);
	i += get_rgba(&line[i], &scene->planes[j].colour);
	printf("pl x:%lf y:%lf z:%lf	dx:%lf dy:%lf dz:%lf	r:%i g:%i b:%i\n",
	scene->planes[j].pos.x,
	scene->planes[j].pos.y,
	scene->planes[j].pos.z,
	scene->planes[j].dir.x,
	scene->planes[j].dir.y,
	scene->planes[j].dir.z,
	scene->planes[j].colour.r,
	scene->planes[j].colour.g,
	scene->planes[j].colour.b);
	j++;
	return (1);
}

int	assign_light(t_scene *scene, char *line)
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
	printf("L x:%lf y:%lf z:%lf	bri:%lf	r:%i g:%i b:%i\n",
	scene->lights[j].pos.x,
	scene->lights[j].pos.y,
	scene->lights[j].pos.z,
	scene->lights[j].brightness,
	scene->lights[j].colour.r,
	scene->lights[j].colour.g,
	scene->lights[j].colour.b);
	j++;
	return (1);
}

int main(void)
{
	t_scene scene;
	scene.cylinders = malloc(sizeof(t_cy));
	scene.spheres = malloc(sizeof(t_sp));
	scene.planes = malloc(sizeof(t_pl));
	scene.lights = malloc(sizeof(t_L));
	
	char *A = "A 1	2,3,4";
	char *C = "C 1 ,	2	, 3 4,5,6 7";
	char *cy = "cy 1,2,3 4,5,6 7 8 9,10,11";
	char *sp = "sp 1,2,3 4 5,6,7";
	char *pl = "pl 1,2,3 4,5,6 7,	8 , 9";
	char *L = "L 1,2,3	4	5,6,7";

	if (assign_ambient_light(&scene, A)
	&& assign_camera(&scene, C)
	&& assign_cylinder(&scene, cy)
	&& assign_sphere(&scene, sp)
	&& assign_plane(&scene, pl)
	&& assign_light(&scene, L))
		printf("all objects assigned!\n");
	else
	 printf("parser detected a miss config of an object\n");
}