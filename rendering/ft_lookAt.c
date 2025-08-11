/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lookAt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:47:45 by  souaguen         #+#    #+#             */
/*   Updated: 2024/11/06 04:43:23 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ft_cross_product(t_vec3 a, t_vec3 b)
{
        t_vec3  v;

        v.x = (a.y * b.z) - (a.z * b.y);
        v.y = (a.z * b.x) - (a.x * b.z);
        v.z = (a.x * b.y) - (a.y * b.x);
        return (v);
}

t_vec3	ft_vec3(double x, double y, double z)
{
	t_vec3	v;
	
	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	ft_sub(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3	ft_product(t_vec3 a, double n)
{
	a.x *= n;
	a.y *= n;
	a.z *= n;
	return (a);
}

float   ft_qrsqrt(float nbr)
{
        long    i;
        float   y;
        float   x;
        float   threehalf;

        threehalf = 1.5f;
        x = nbr * 0.5f;
        y = nbr;
        i = *(long *) &y;
        i = 0x5f3759df - (i >> 1);
        y = *(float *) &i;
        y = y * (threehalf - (x * y * y));
        return (fabs(y));
}

t_vec3  ft_normalize(t_vec3 v)
{
        float   nbr;

        nbr = fabs(ft_dot(v, v));
        //printf("%f %f\n", 1 / sqrt(nbr), ft_qrsqrt(nbr));
        return (ft_product(v, ft_qrsqrt(nbr)));
}


double	ft_dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

void	ft_lookAt(t_vec3 matrix[3], t_vec3 forward)
{
	t_vec3	randup;
	t_vec3	right;
	t_vec3	up;
	t_vec3	transform;
	t_vec3	position;

	randup = ft_vec3(0, -1, 0);
	right = ft_normalize(ft_cross_product(forward, randup));
	up = ft_normalize(ft_cross_product(right, forward));

	//position = ft_vec3(1, 1, 1);

	//transform = ft_vec3(ft_dot(position, right), ft_dot(position, up), ft_dot(position, forward));
	
	matrix[0] = right;
	matrix[1] = up;
	matrix[2] = ft_normalize(forward);
}

int	main()
{
	t_vec3	matrix[3];

	t_vec3	forward = ft_vec3(0, 1, 0);
	t_vec3	ray = ft_normalize(ft_vec3(1, 1, 1));

	ft_lookAt(matrix, forward);

	printf("%f %f %f\n", ft_dot(ray, matrix[0]), ft_dot(ray, matrix[1]), ft_dot(ray, matrix[2]));
	return (0);
}
