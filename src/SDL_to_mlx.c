
#define PI 3.14
#include "../includes/minirt.h"

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
} t_vector3;

typedef	struct s_sp
{
	t_vector3	pos;
	double		diameter;
}	t_sp;

typedef struct s_ray
{
	t_vector3	O;
	t_vector3	D;
	int			t;
} t_ray;

typedef struct s_cam
{
	t_vector3	O;
	double		Dx;
	double		Dy;
	double		fov;
} t_cam;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
}	t_data;

typedef struct s_vars{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_vars;

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_window(vars);
	return (0);
}

void render_frame(t_data* renderer, t_sp *sp, t_cam *cam)
{
	t_ray ray;
	ray.O.x = cam->O.x;
	ray.O.y = cam->O.y;
	ray.O.z = cam->O.z;
	ray.D.z = 0;
	ray.D.y = cam->Dy - (cam->fov * .5);
	ray.t = 1000;

	for (int y = 0; y < 1000; y++)
	{
		ray.D.x = cam->Dx - (cam->fov * .5);
		for (int x = 0; x < 1000; x++)
		{
			SDL_SetRenderDrawColor(renderer, 0, collide_sphere_3D(&ray, sp, renderer), 0, 0);
			ray.D.x += cam->fov / 1000;
		}
		ray.D.y += cam->fov / 1000;
		printf("\rprogress...%d%%", y / 10 + 1);
	}
	printf("\nrender done\n");
}

int main(void)
{
	t_vars	v;
	int		endian;

    t_cam cam;
	cam.O.x = 0;
	cam.O.y = 0;
	cam.O.z = 0;
	cam.Dx = 0;
	cam.Dy = 0;
	cam.fov = 45;

	t_sp sp;
	sp.pos.x = 0;
	sp.pos.y = 0;
	sp.pos.z = 4;
	sp.diameter = 10000;

	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, WIN_WIDTH, WIN_HEIGHT, MLX_TITLE);
	v.img.img = mlx_new_image(v.mlx, WIN_WIDTH, WIN_HEIGHT);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bits_per_pixel,
			&v.img.line_length, &endian);
	// render_frame(&v.img, &sp, &cam);
	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
	mlx_key_hook(v.win, key_hook, &v);
	mlx_hook(v.win, 17, 1L << 17, close_window, &v);
	mlx_loop(v.mlx);
}