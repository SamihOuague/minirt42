/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:12:11 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/13 02:36:32 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ft_ray_direction(t_vec3 xy, t_elt *params)
{
	double	x;
	double	y;
	double	fov;

	fov = (*params).scene.camera.fov;
	x = (*params).aspect_r * (((xy.x + 0.5) / (*params).width) * 2 - 1);
	x = x * tan(ft_radian(fov / 2));
	y = ((xy.y + 0.5f) / (*params).height * 2.0f - 1.0f);
	y = y * tan(ft_radian(fov / 2.0f));
	return (ft_vec3(x, y, 1));
}

int	ft_compute_ray(t_vec3 matrix[3], int k, t_elt *params)
{
	t_vec3	xy;
	t_vec3	vector;
	t_ray	ray;	
	int		pixel;

	pixel = 0;
	xy.x = k % (*params).width;
	xy.y = k / (*params).width;
	vector = transform_ray(ft_ray_direction(xy, params), matrix);
	ft_init_ray(&ray, vector, (*params).scene.camera);
	if (ft_has_intersection((*params).scene.shapes, &ray, NULL))
		pixel = ft_light(&ray, &(*params).scene);
	return (pixel);
}

int	ft_error_checker(char *filename, t_elt *params)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL || ft_strncmp(".rt", dot, 4) != 0)
	{
		printf("Error : bad file format\n");
		return (1);
	}
	if (ft_minirt_init(filename, params))
		return (1);
	if ((*params).scene.cla[0] == 0)
	{
		printf("Error : camera not detected\n");
		return (1);
	}
	(*params).mlx = mlx_init();
	if ((*params).mlx == NULL)
	{
		printf("Error : mlx init failed\n");
		return (1);
	}
	return (0);
}

void	run(t_elt *params)
{
	(*params).win = mlx_new_window((*params).mlx,
			(*params).width, (*params).height, "MiniRT");
	(*params).img_ptr = mlx_new_image((*params).mlx,
			(*params).width, (*params).height);
	if ((*params).win == NULL || (*params).img_ptr == NULL)
		close_n_clean(params);
	(*params).data_addr = mlx_get_data_addr((*params).img_ptr,
			&(*params).bpp, &(*params).size_line, &(*params).endian);
	ft_create_image(params);
	ft_run_loop(params);
}

int	main(int argc, char **argv)
{
	t_elt	params;

	params.width = WIDTH;
	params.height = HEIGHT;
	params.scene.shapes = NULL;
	if (params.width <= 0 || params.height <= 0)
		return (1);
	params.aspect_r = (double)params.width / (double)params.height;
	if (argc != 2)
	{
		printf("Usage: ./miniRT scene.rt");
		return (1);
	}
	if (ft_error_checker(argv[1], &params))
	{
		ft_lstclear(&params.scene.shapes, &ft_free_content);
		return (1);
	}
	run(&params);
	return (0);
}
