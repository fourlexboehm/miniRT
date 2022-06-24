#include "../includes/minirt.h"
#include <math.h>

void	add_vector3(t_vector3 *v1, t_vector3 *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
	v1->y += v2->z;
}


void	subtract_vector3(t_vector3 *v1, t_vector3 *v2)
{
	v1->x += v2->x * -1;
	v1->y += v2->y * -1;
	v1->y += v2->z * -1;
}

void	multi_vector3(t_vector3 *v1, t_vector3 *v2)
{
	v1->x *= v2->x;
	v1->y *= v2->y;
	v1->y *= v2->z;
}

void	scalar_vector3(t_vector3 *v1, double scalar)
{
	v1->x *= scalar;
	v1->y *= scalar;
	v1->y *= scalar;
}

double get_distance_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return(sqrt(pow(v2->x - v1->x, 2)
			  + pow(v2->y - v1->y, 2)
			  + pow(v2->z + v1->z, 2)));
}

double get_distance_vector2(t_vector3 *v1, t_vector3 *v2)
{
	return(sqrt(pow(v2->x - v1->x, 2)
			  + pow(v2->y - v1->y, 2)));
}

double get_coord_rad_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return (acos((v1->x * v2->x + v1->y * v2->y + v1->z * v2->z)
			/ ( sqrt( pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2))
			* sqrt( pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2)))));
}

double get_coord_deg_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return (get_coord_rad_vector3(v1, v2) * (180 / 3.141592));
}