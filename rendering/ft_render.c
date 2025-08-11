/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:52:26 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:17:16 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_run_loop(t_elt *params, int width, int height)
{
	mlx_put_image_to_window((*params).mlx,
		(*params).win,
		(*params).img_ptr, 0, 0);
	mlx_hook((*params).win, ClientMessage, NoEventMask, hook, params);
	mlx_loop_hook((*params).win, NULL, params);
	mlx_key_hook((*params).win, &key_hook_ptr, params);
	mlx_loop((*params).mlx);
}

double	ft_radian(double angle)
{
	return (angle * M_PI / 180.0f);
}

void	ft_init_ray(t_ray *ray, t_vec3 dir, t_cam camera)
{
	(*ray).has_hit = 0;
	(*ray).from = camera.origin;
	(*ray).hit.distance = 0;
	(*ray).hit.shape_addr = NULL;
	(*ray).direction = dir;
}

void	ft_lookat(t_vec3 matrix[3], t_vec3 forward)
{
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;

	world_up = ft_vec3(0, 1, 0);
	forward = ft_normalize(forward);
	if (fabs(ft_dot(forward, world_up)) > 0.999)
		world_up = ft_vec3(0, 0, 1);
	right = ft_normalize(ft_cross_product(world_up, forward));
	up = ft_cross_product(forward, right);
	matrix[0] = right;
	matrix[1] = up;
	matrix[2] = forward;
}

t_vec3	transform_ray(t_vec3 vector, t_vec3 matrix[3])
{
	t_vec3	world_ray;

	world_ray.x = vector.x * matrix[0].x
		+ vector.y * matrix[1].x
		+ vector.z * matrix[2].x;
	world_ray.y = vector.x * matrix[0].y
		+ vector.y * matrix[1].y
		+ vector.z * matrix[2].y;
	world_ray.z = vector.x * matrix[0].z
		+ vector.y * matrix[1].z
		+ vector.z * matrix[2].z;
	return (ft_normalize(world_ray));
}
