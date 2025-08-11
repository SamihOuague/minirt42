/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:29:58 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:17:40 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 800
# define HEIGHT 800

# include "libft.h"
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <X11/X.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	direction;
	double	aspect_ratio;
	int		fov;
}	t_cam;

typedef struct s_light
{
	t_vec3	origin;
	t_vec3	color;
	double	intensity;
}	t_light;

typedef struct s_hitpoint
{
	t_vec3	direction;
	t_vec3	normal;
	double	distance;
	t_vec3	pixel;
	void	*shape_addr;
}	t_hitpoint;

typedef struct s_ray
{
	t_hitpoint	hit;
	t_vec3		from;
	t_vec3		direction;	
	int			has_hit;
}	t_ray;

typedef struct s_shape
{
	void	*object;
	t_vec3	color;
	int		(*has_inter)(void *, t_ray *);
}	t_shape;

typedef struct s_sphere
{
	t_vec3	origin;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	direction;
	t_vec3	point;
}	t_plane;

typedef struct s_cylinder
{
	double	height;	
	double	radius;
	t_vec3	axis;
	t_vec3	origin;
}	t_cylinder;

typedef struct s_scene
{
	t_list	*shapes;
	t_cam	camera;
	t_light	light;
	double	ambient;
	t_vec3	color;
	int		error;	
	int		cla[3];
}	t_scene;

typedef struct s_elt
{
	void	*mlx;
	void	*win;
	t_scene	scene;
	void	*img_ptr;
	char	*data_addr;	
	double	aspect_r;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_elt;

t_sphere	ft_sphere(t_vec3 origin, double radius);
void		ft_run_loop(t_elt *params, int width, int height);
void		ft_init_ray(t_ray *ray, t_vec3 dir, t_cam camera);
void		ft_lookat(t_vec3 matrix[3], t_vec3 forward);
void		ft_pixel_put(char **data_addr,
				int x, int y, int s_line, int bpp, int pixel);
void		close_n_clean(t_elt *param);
void		ft_extract_line(char *line, t_scene *scene);
void		ft_init_scene(int fd, t_scene *scene);
void		ft_set_scene(t_scene *scene);
void		ft_free_content(void *content);
void		ft_insert_object(t_shape *shape, t_scene *scene);
void		ft_sphere_shape(t_shape **shape);
void		ft_cylinder_shape(t_shape **shape);
void		ft_plane_shape(t_shape **shape);
void		ft_shapes_alloc(void **object,
				t_shape **shape, unsigned int obj_size);
void		ft_shape_init(t_shape **shape,
				void *obj,
				t_vec3 color,
				void (f)(t_shape **));
double		ft_radian(double angle);
double		ft_to_double(char *nbr);
double		ft_dot(t_vec3 a, t_vec3 b);
char		*ft_to_space(char *str);
char		*get_next_line(int fd);
char		**ft_fast_split(char *str);
int			ft_get_rgb(int r, int g, int b);
int			ft_is_shadow(t_ray ray, t_vec3 light, t_list *shapes);
int			ft_light(t_ray *ray, t_scene *scene);
int			ft_has_intersection(t_list *shapes, t_ray *ray, void *exclude);
int			hook(t_elt *param);
int			key_hook_ptr(int key, t_elt *param);
int			ft_minirt_init(char *filename, t_elt *params);
int			ft_coords_checker(char *coord);
int			ft_coords_float_checker(char **split);
int			ft_color_checker(char **split);
int			ft_float_checker(char *nbr);
int			ft_init_elements(char **split, t_scene *scene);
int			ft_len(char **split);
int			ft_length_checker(t_vec3 axis);
int			ft_isnumeric(char *str);
int			ft_init_camera(char **split, t_scene *scene);
int			ft_init_light(char **split, t_scene *scene);
int			ft_init_ambient(char **split, t_scene *scene);
int			ft_init_sphere(char **split, t_scene *scene);
int			ft_init_cylinder(char **split, t_scene *scene);
int			ft_init_plan(char **split, t_scene *scene);
int			ft_space_to_null(char *str, int *size);
int			ft_sphere_intersection(void *sphere, t_ray *ray);
int			ft_plane_intersection(void *plane, t_ray *ray);
int			ft_cylinder_intersection(void *cylinder, t_ray *ray);
t_vec3		transform_ray(t_vec3 vector, t_vec3 matrix[3]);
t_vec3		ft_vec3(double x, double y, double z);
t_vec3		ft_sum(t_vec3 a, t_vec3 b);
t_vec3		ft_sub(t_vec3 a, t_vec3 b);
t_vec3		ft_product(t_vec3 a, double n);
t_vec3		ft_normalize(t_vec3 v);
t_vec3		ft_cross_product(t_vec3 a, t_vec3 b);
t_shape		*ft_create_sphere(t_vec3 origin, double radius, t_vec3 color);
t_shape		*ft_create_plane(t_vec3 axis, t_vec3 point, t_vec3 color);
t_shape		*ft_create_cylinder(t_vec3 base,
				t_vec3 axis,
				double size[2],
				t_vec3 color);
t_plane		ft_plane(t_vec3 direction, t_vec3 point);
t_cylinder	ft_cylinder(t_vec3 origin,
				t_vec3 axis,
				double height,
				double radius);
#endif
