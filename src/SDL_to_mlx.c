#include "../includes/minirt.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

//------------------------------------------------------------------------ Vector Math ------------------------------------------------------


//--------------------------------------------------------------------------------- sphere colliders ---------------------------------------------


//--------------------------------------------------------------------------------------------------- ray color / reflect ------------------------------------


//--------------------------------------------------------------------------------------------------- Frame Render

void	pixel_put(t_data *r, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

void render_frame(t_data* img)
{

	t_cam cam;
	cam.O.x = 0;
	cam.O.y = 0;
	cam.O.z = -60;
	cam.Dx = 0;
	cam.Dy = 0;
	cam.fov = 20;

	t_ray ray;
	ray.O.x = cam.O.x;
	ray.O.y = cam.O.y;
	ray.O.z = cam.O.z;
	ray.D.z = 0;
	ray.t = 1000;
	t_vector3 color;

	double aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	t_vector3 origin; init_vec3(&origin, 0, 0, 0);
	t_vector3 horizontal; init_vec3(&horizontal, viewport_width, 0, 0);
	t_vector3 vertical; init_vec3(&vertical, 0, viewport_height, 0);
	t_vector3 focal; init_vec3(&focal, 0, 0, focal_length);
	t_vector3 lower_left_corner = subtract_vector3(subtract_vector3(origin, scale_vector3(horizontal, 0.5)), subtract_vector3(scale_vector3(vertical, 0.5), focal));

	static double movex = 3;
	static double movez = 3;
	for (int y = SCREEN_HEIGHT; y >= 0; --y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			double u = (double)x / SCREEN_WIDTH;
			double v = (double)y / SCREEN_HEIGHT;

			ray.D = subtract_vector3(add_vector3(add_vector3(lower_left_corner, scale_vector3(horizontal, u)), scale_vector3(vertical, v)), origin);
			color = ray_color(&ray, movex, movez);
			pixel_put(img, x, y, create_trgb(0, color.x, color.y, color.z));
		}
	}
	static double angle = 0;
	movex = 3 * cos(angle);
	movez = 3 * sin(angle) + 3;
	angle -= 0.2;
	printf("movex = %lf\n", movex);
	printf("movez = %lf\n\n", movez);
}

//--------------------------------------------------------------------------------------------------- mlx functions ---------------------------------------------

static int	key_hook(int keycode)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
void	pixel_put(t_data *r, int x, int y, int color)
{
	char	*dst;

	dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

typedef struct s_sce
{
	t_cam	*cam;
	t_vars	*vars;
	double	t;
} t_sce;


int	next_frame(t_vars *v)
{
	int		endian;
	t_data	img;
	img.img = mlx_new_image(v->mlx, SCREEN_HEIGHT + 1, SCREEN_WIDTH + 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &endian);


	render_frame(&img);
	mlx_put_image_to_window(v->mlx, v->win, img.img, 0, 0);
	mlx_destroy_image(v->mlx, img.img);
	return(1);
}

int main(void)
{
	t_vars	v;

	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, MLX_TITLE);

	mlx_loop_hook(v.mlx, next_frame, &v);
	mlx_key_hook(v.win, key_hook, &v);
	mlx_loop(v.mlx);
}