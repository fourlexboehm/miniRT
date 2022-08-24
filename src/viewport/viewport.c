#include "../../includes/minirt.h"

/**
 * Normalize the vector to a unit vector
 */
static t_vector3	vector_to_unit(t_vector3 v)
{
	t_vector3	unit;
	double		mag;

	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	//TODO SHOULD THIS BE A NORMALIZED VECTOR
//	if (mag == 0.0)
//	{
//		printf("Invalid input file: Camera vector is 0\n");
//		exit (99);
//	}
	unit.x = v.x / mag;
	unit.y = v.y / mag;
	unit.z = v.z / mag;
	return (unit);
}

/**
 * converts the fov from degrees to radians, then calculate the
 * coordinates for each axis of each corner
 * @param fov		in degrees
 */
static t_corners	calculate_corners(t_vector3 unit_v, t_vector3 unit_q, \
t_vector3 a, double fov)
{
	t_corners	corn;
	double		ang_tan;
	t_vector3	scaled_q;
	t_vector3	scaled_v_x_tan;

	ang_tan = tanf((fov / 2.0) * M_PI / 180.0);
	scaled_v_x_tan = scale_vector3(a, ang_tan * (9.0 / 16.0));
	scaled_q = scale_vector3(unit_q, ang_tan);
	corn.tl = unit_vector3(add_vector3(subtract_vector3(unit_v, scaled_q), scaled_v_x_tan));
	corn.tr = unit_vector3(add_vector3(add_vector3(unit_v, scaled_q), scaled_v_x_tan));
	corn.bl = unit_vector3(subtract_vector3(subtract_vector3(unit_v, scaled_q),
			scaled_v_x_tan));
	corn.br = unit_vector3(subtract_vector3(add_vector3(unit_v, scaled_q), scaled_v_x_tan));
	return (corn);
}

static t_vector3	get_unit_q(t_vector3 unit_v)
{
	t_vector3	q;
	t_vector3	unit_q;
	double		mag;

	q.x = -unit_v.z;
	q.y = 0.0;
	q.z = unit_v.x;
	mag = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
	if (mag)
	{
		unit_q.x = q.x / mag;
		unit_q.z = q.z / mag;
	}
	else
	{
		unit_q.x = 1.0;
		unit_q.z = 0.0;
	}
	unit_q.y = 0.0;
	return (unit_q);
}

t_vector3	**calculate_viewport_vectors(t_camera cam)
{
	t_vector3	unit_v;
	t_vector3	unit_q;
	t_vector3	a;
	t_corners	corners;

	unit_v = vector_to_unit(cam.rot);
	unit_q = get_unit_q(unit_v);
	a.x = -unit_q.z * unit_v.y;
	a.y = +unit_v.x * unit_q.z - unit_q.x * unit_v.z;
	a.z = unit_q.x * unit_v.y;
	corners = calculate_corners(unit_v, unit_q, a, cam.fov);
	return (set_cam_vectors(corners));
}