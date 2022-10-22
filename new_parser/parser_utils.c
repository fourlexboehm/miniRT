#include "parser.h"

int is_inchar(char c)
{
	if (c == ' ' || c == '	' || c == '.' || c == ',' || (c >= '0' && c <= '9'))
		return (1);
    return (0);
}

int num_count(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            j++;
            while (str[i] == '.' || (str[i] >= '0' && str[i] <= '9') && str[i + 1])
                i++;
        }
        i++;
    }
    return (j);
}

int check_line(char *str, int num)
{
    int i;

    i = 0;
    while(str[i])
    {
		    if(!is_inchar(str[i]))
			{
				printf("failed char\n")	;
            	return(0);
			}
			i++;
	}
	if (num_count(str) != num)
	{
		printf("failed numcheck of num = %d numcheck = %d\n", num, num_count(str));
		return(0);
	}
	return (1);
}

int get_vector(char *str, t_vec *vec)
{
    int i;

    i = 0;
    while (!ft_isspace(str[i]))
        i++;
    vec->x = atof(&str[i]);
    while (str[i] != ',' || ft_isspace(str[i]))
        i++;
    vec->y = atof(&str[++i]);
    while (str[i] != ',' || ft_isspace(str[i]))
        i++;
    vec->z = atof(&str[++i]);
    while (!ft_isspace(str[i]))
        i++;
    return (++i);
}

int get_rgba(char *str, t_rgba *rgba)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    r = atoi(&str[i]);
    while (str[i] != ',' || ft_isspace(str[i]))
        i++;
    g = atoi(&str[++i]);
    while (str[i] != ',' || ft_isspace(str[i]))
        i++;
    b = atoi(&str[++i]);
    while (str[i] != ',' || ft_isspace(str[i]))
        i++;
    if (r > 255 || g > 255 || b > 255 ||
            r < 0 || g < 0 || b < 0)
            return (-1);
    rgba->r = r;
    rgba->g = g;
    rgba->b = b;
    return (i);
}

int get_double(char *str, double *d)
{
    int i;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    *d = atof(&str[i]);
    while (!ft_isspace(str[i]))
        i++;
    return (i);
}
