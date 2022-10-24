#include "../../includes/minirt.h"

char	**get_file(char *path)
{
	int i;
	int fd;
	char **line;

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
}
