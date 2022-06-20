#include "../includes/minirt.h"
#include <fcntl.h>

#define isdigit(c) (c >= '0' && c <= '9')

double atof(const char *s)
{
  double a = 0.0;
  int e = 0;
  int c;
    int sign = 1;
  if (s[0] == '-')
	sign = -1;
  while ((c = *s++) != '\0' && isdigit(c)) {
    a = a*10.0 + (c - '0');
  }
  if (c == '.') {
    while ((c = *s++) != '\0' && isdigit(c)) {
      a = a*10.0 + (c - '0');
      e = e-1;
    }
  }
  if (c == 'e' || c == 'E') 
  {
    int i = 0;
    c = *s++;
    if (c == '+')
      c = *s++;
    else if (c == '-') {
      c = *s++;
      sign = -1;
    }
    while (isdigit(c)) {
      i = i*10 + (c - '0');
      c = *s++;
    }
    e += i*sign;
  }
  while (e > 0) {
    a *= 10.0;
    e--;
  }
  while (e < 0) {
    a *= 0.1;
    e++;
  }
  return a;
}


char **get_file(char *path)
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
	while(1)
	{
		line[++i] = get_next_line(fd);
		if (!line[i])
			break ;
	}
	return (line);
}

int	get_n_obs(char **line)
{
	int	i;
	int	num;

	num = 0;
	i = -1;
	ft_printf("getting num of objs");
	while (line[++i])
	{
		if (line[i][0] == 's')
			num++;
		if (line[i][0] == 'p')
			num++;
		if (line[i][0] == 'c')
			num++;
	}
	ft_printf("...%d\n", num);
	return (num);
}

void	assign_scene(t_scene *scene, char **line)
{
	int	i;
	int	j;
	//char **current_line;
	//char **vals;

	i = -1;
	ft_printf("assigning objs\n");
	while (line[++i])
	{
		j = 0;
		// if (line[i][0] == 'A')
		// {
		// 	while (!ft_isspace(line[i][j]))
		// 		j++;
		// 	current_line = ft_split_on_whitespace(line[i] + 2);
		// 	while(*current_line + 2)
		// 	{
		// 		scene->light->ambient =  atof(*current_line);
		// 		vals = ft_split(*current_line++, ',');
		// 		if(*vals)
		// 		{
		// 			scene->light->color.r =  atof(*vals);
		// 			vals++;
		// 			scene->light->color.r =  atof(*vals);
		// 			vals++;
		// 			scene->light->color.r =  atof(*vals);
		// 			vals++;
		// 		}
		// 	}
		// }
		if (line[i][0] == 'C')
		{
			j = 2;
			while (ft_isspace(line[i][j]))
				j++;
				
			printf("%s\n", &line[i][j]);
			scene->camera.pos.x = atof(&line[i][j]);
			scene->camera.pos.x = atof("-50");
			while (line[i][j++] != ',')
				;
			printf("%s\n", &line[i][j]);
			scene->camera.pos.y = atof(&line[i][j]);
			while (line[i][j++] != ',')
				;
			printf("%s\n", &line[i][j]);
			scene->camera.pos.z = atof(&line[i][j]);


			while (!ft_isspace(line[i][j]))
				j++;
			while (ft_isspace(line[i][j]))
				j++;

			
			printf("%s\n", &line[i][j]);
			scene->camera.rot.x = atof(&line[i][j]);
			while (line[i][j++] != ',')
				;
			printf("%s\n", &line[i][j]);
			scene->camera.rot.y = atof(&line[i][j]);
			while (line[i][j++] != ',')
				;
			printf("%s\n", &line[i][j]);
			scene->camera.rot.z = atof(&line[i][j]);


			while (!ft_isspace(line[i][j]))
				j++;
			while (ft_isspace(line[i][j]))
				j++;

			
			printf("%s\n", &line[i][j]);
			scene->camera.fov = atof(&line[i][j]);
		}
		// if (line[i][0] == 'L')
		// if (line[i][0] == 's')
		// if (line[i][0] == 'p')
		// if (line[i][0] == 'c')
	}
	ft_printf("...done\n");
}

void	printf_cam(t_scene *s)
{
	printf("cam pos x = %f\n", s->camera.pos.x);
	printf("cam pos y = %f\n", s->camera.pos.y);
	printf("cam pos z = %f\n", s->camera.pos.z);
	printf("cam rot x = %f\n", s->camera.rot.x);
	printf("cam rot y = %f\n", s->camera.rot.y);
	printf("cam rot z = %f\n", s->camera.rot.z);
	printf("cam fov = %f\n", s->camera.fov);
}


int	main(void)
{
	char	**line;
	int		n_obs;
	t_scene *scene;


	line = get_file("scenes/1.rt");
	n_obs = get_n_obs(line);
	scene = malloc(sizeof(t_scene));

	scene->obj = malloc(sizeof(t_obj) * n_obs + 1);
	assign_scene(scene, line);
	printf_cam(scene);
	
	ft_printf("done.exe\n");
}