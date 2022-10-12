#include "../../includes/minirt.h"

/**
 * returns dot product of two vectors
 */
double dot(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/**
 * returns length SQUARED product of a vector
 */
double length_squared(t_vec const v3)
{
	return (v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
}

/**
 * returns length product of a vector
 */
double length(t_vec const v3)
{
	return sqrt(length_squared(v3));
}

t_vec	new_vector3(double x, double y, double z)
{
	t_vec	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}
