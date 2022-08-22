#include "../includes/minirt.h"

int	main(void)
{
	char		**line;
	t_scene		scene;
	t_vector3	**v_matrix;
	int			**c_matrix;

	line = get_file("scenes/2.rt");
	assign_scene(&scene, line);
	v_matrix = calculate_viewport_vectors(scene.camera);
	c_matrix = set_colour_matrix(v_matrix, scene);
	//free v_matrix
	render_image_on_mlx(c_matrix);
//	ft_printf("done.exe\n");
//	t_vector3 v1;
//	v1.x = 19;
//	v1.y = 420;
//	v1.z = 5;
//
//	t_vector3 v2;
//	v2.x = 16;
//	v2.y = 52;
//	v2.z = 91;
//	printf("rad is = %lf\n", get_coord_rad_vector3(&v1, &v2));
//	printf("deg is = %lf\n", get_coord_deg_vector3(&v1, &v2));
}