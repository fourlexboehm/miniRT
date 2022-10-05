#include "../../includes/minirt.h"

double	dot(t_vector3 v1, t_vector3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	length_squared(t_vector3 const v3)
{
	return (v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
}

double	length(t_vector3 const v3)
{
	return sqrt(length_squared(v3));
}

t_vector3	new_vector3(double x, double y, double z)
{
	t_vector3	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}
