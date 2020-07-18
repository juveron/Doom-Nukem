/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 23:04:32 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 12:34:22 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW3D_H
# define DRAW3D_H

# include "libft.h"
# include <SDL2/SDL.h>
# include <math.h>

# define WORKER_THREAD 8

# define TILE_SIZE 64

# define WIDTH_ 1600
# define HEIGHT_ 800

typedef struct	s_matrix4
{
	double	m[4][4];
}				t_matrix4;

typedef struct	s_texture
{
	t_u64		id;
	char		*name;
	SDL_Surface	*surface;
	t_vector	materials;
}				t_texture;

typedef struct	s_material
{
	t_texture	*diffuse_texture;
	t_u32		diffuse_color;
	t_vec2f		uv_pos;
	t_vec2f		uv_scale;
	float		angle;
	bool		use_advenced_movement;
	t_vec2f		step;
}				t_material;

typedef struct	s_transform
{
	t_vec3f		rotation;
	t_vec3f		position;
	t_vec3f		scale;
	t_matrix4	rot_pos;
	t_matrix4	rot_pos_scale;
}				t_transform;

typedef struct	s_object
{
	char		*name;
	t_transform	transform;
}				t_object;

typedef struct	s_obb
{
	t_vec3f	pos;
	t_vec3f	half_size;
}				t_obb;

typedef struct	s_mesh
{
	char		*name;
	t_obb		obb;
	t_vector	vertex;
	t_material	*default_material;
	t_vector	render_objects;
}				t_mesh;

typedef struct	s_render_object
{
	char		*name;
	t_transform	transform;
	t_mesh		*mesh;
	bool		has_custom_material;
	t_material	*custom_material;
}				t_render_object;

typedef struct	s_fragment_data
{
	t_material	*material;
	t_vec2i		pos;
	t_vec3f		normal;
	t_vec2f		tex_coord;
	t_u32		frag_color;
	t_mesh		*mesh;
	t_vec3f		w;
	t_u32		color;
	bool		debug_clip;
}				t_fragment_data;

typedef struct	s_obj_file
{
	t_vector	v;
	t_vector	vt;
	t_vector	vn;
	t_vector	tris;
}				t_obj_file;

typedef struct	s_triangle_index
{
	t_s32	v_index[3];
	t_s32	v_tex_index[3];
	t_s32	v_norm_index[3];
	t_u32	color;
}				t_triangle_index;

typedef struct	s_obj_utils
{
	t_triangle_index	*p_tris;
	t_vec3f				*p_v;
	t_vec2f				*p_vt;
	t_vec3f				*p_vn;
}				t_obj_utils;

typedef struct	s_vertex
{
	t_vec3f	v;
	t_vec2f	v_texture;
}				t_vertex;

typedef struct	s_vertex_raster
{
	t_vec4f	v;
	t_vec3f	v_texture;
}				t_vertex_raster;

typedef struct	s_triangle
{
	t_vertex	vertex[3];
	t_u32		color;
}				t_triangle;

typedef struct	s_triangle_raster
{
	t_vertex_raster	vertex[3];
	t_u32			color;
	t_material		*material;
}				t_triangle_raster;

typedef struct	s_camera
{
	char		*name;
	t_transform transform;
	t_matrix4	m_invert;
	t_matrix4	m_proj;
	t_matrix4	m_proj_inv;
	float		*depth_buffer;
	float		z_far;
	float		z_near;
	float		fov;
	float		aspect_ratio;
}				t_camera;

typedef struct	s_frame
{
	t_u32	*pixels;
	t_vec2i	size;
}				t_frame;

typedef struct	s_screen_coordinates
{
	float	top;
	float	bottom;
	float	left;
	float	right;
}				t_screen_coordianate;

typedef struct	s_tile
{
	t_u16		x_min;
	t_u16		x_max;
	t_u16		y_min;
	t_u16		y_max;
	t_vector	triangle_array;
}				t_tile;

typedef struct	s_render_screen
{
	SDL_Surface	*surface;
	t_u16		width;
	t_u16		height;
	t_tile		*tiles;
	t_u16		tile_x;
	t_u16		tile_y;
	t_camera	*active_camera;
}				t_render_screen;

/*
**	edge
*/

typedef union	u_m128
{
	__m128	sse;
	float	bytes[4];
	int		ibytes[4];
}				t_m128;

typedef struct	s_edges
{
	t_m128	w;
	t_m128	step_x;
	t_m128	step_y;
	t_m128	w_row;
}				t_edges;

/*
**	Rasterizer worker
*/

typedef struct	s_rasterizer_worker
{
	pthread_t				thread;
	t_u32					id;
	bool					active;
}				t_rasterizer_worker;

typedef struct	s_context_3d
{
	t_rasterizer_worker	workers[WORKER_THREAD];
	t_material			*material;
	t_render_screen		render_screen;
	t_camera			*camera;
	t_vector			triangle;
	bool				is_waiting;
	bool				is_active;
	t_u16				finish;
	pthread_mutex_t		mtx_wait;
	pthread_cond_t		cond_wait;
	pthread_mutex_t		mtx_work;
	pthread_cond_t		cond_work;
	t_u16				current_tile;
	t_u16				tile_max;
	bool				is_alive;
	bool				debug_clip;
	t_u64				n_tri;
	bool				use_depthbuffer;
	t_u64				n_tile_skiped;
}				t_context_3d;

typedef struct	s_line
{
	t_transform transform;
	t_vec3f		end;
	t_u32		color;
}				t_line;

typedef struct	s_plane
{
	t_vec4f	p;
	t_vec4f n;
}				t_plane;

t_triangle		triangle(t_vec3f p1, t_vec3f p2, t_vec3f p3);
void			mul_matrix4_vec3f(t_vec3f *i, t_vec3f *o, t_matrix4 *mat);
void			mul_matrix4_vec4f(t_vec4f *i, t_vec4f *o, t_matrix4 *mat);
float			edge_function(t_vec4f *a, t_vec4f *b, t_vec4f *c);
t_mesh			create_mesh_from_obj_file(char *str);

t_mesh			*open_obj_file(char *filepath, char *mesh_name);

/*
**	matrix_identity.c
*/

void			matrix_identity(t_matrix4 *out);

/*
**	matrix_multiply.c
*/

t_matrix4		matrix_multiply(t_matrix4 *in1, t_matrix4 *in2);
void			matrix_multiply2(t_matrix4 *in1, t_matrix4 *in2,
	t_matrix4 *out);

/*
**	matrix_rotation.c
*/

void			matrix_rotation(float x, float y, float z, t_matrix4 *out);
void			matrix_rotation_z(float rad, t_matrix4 *out);
void			matrix_rotation_y(float rad, t_matrix4 *out);
void			matrix_rotation_x(float rad, t_matrix4 *out);

/*
**	matrix_translation.c
*/

void			matrix_translation(float x, float y, float z, t_matrix4 *out);

/*
**	matrix_scale.c
*/

void			matrix_scale(float x, float y, float z, t_matrix4 *out);

/*
**	matrix_perspective.c
*/

t_matrix4		matrix_perspective_fov(float fov, float aspect_ration,
	float z_near, float z_far);

/*
**	matrix_invert.c
*/

t_matrix4		matrix_invert(t_matrix4 *in);
t_matrix4		matrix_invert2(t_matrix4 in);

/*
**	matrix_point_at.c
*/

void			matrix_point_at(t_vec3f *pos, t_vec3f *target, t_vec3f *up);

/*
**	transform.c
*/

void			update_transform(t_transform *transform);

/*
**	camera.c
*/

void			update_camera(t_camera *camera);

/*
**	mesh.c
*/

void			render_mesh(t_mesh *mesh, t_camera *camera);
void			draw_triangle(t_triangle *triangle, t_camera *camera,
	SDL_Surface *surface);

/*
**	worker.c
*/

bool			init_rasterizer_worker(void);
void			destroy_rasterizer_workers(void);
void			active_worker(void);
void			worker_wait(void);

void			*rasterizer_worker(void *args);

void			draw_triangle_tile(t_triangle_raster *triangle, t_tile *tile,
	t_render_screen *render_screen);
bool			draw_tile(t_tile *tile);
bool			add_triangle_to_tiles(t_triangle_raster *triangle,
	t_material *material);
bool			build_tile_array(void);
void			free_tiles_array(void);

/*
**	vertex.c
*/

void			process_vertex(t_vertex *vertex, size_t vertex_count,
	t_matrix4 *model_matrix);
void			vertex_function(t_triangle *triangle, t_matrix4 *m_mv,
	t_matrix4 *m_p);

/*
**	draw_array.c
*/

void			draw_array(t_u32 first, t_u32 count);
void			vertex_shader(t_u32 vertex_start, t_u16 vertex_end);

t_edges			init_edges(t_vertex_raster *vertices, t_vec4f *vec, float area);
void			edges_update_column(t_edges *edges);
void			edges_update_row(t_edges *edges);

/*
**	material.c
*/

t_material		*mtl_clone(t_material *src);
t_material		*mtl_create(void);
void			mtl_destroy(t_material **material);

/*
**	mtl_diffuse.c
*/

bool			mtl_add_diffuse_texture(t_material *material,
	t_texture *diffuse_texture);
bool			mtl_remove_diffuse_texture(t_material *material);
void			mtl_change_diffuse_color(t_material *material,
	t_u32 diffuse_color);

void			destroy_mesh(t_mesh **mesh);

bool			draw_render_object(t_render_object *obj);
bool			force_draw_render_object(t_render_object *obj);
void			render_all_triangle(void);

t_u32			triangle_clip_plane(t_plane *plane,
	t_triangle_raster *in, t_triangle_raster out[2]);

/*
**	render_object.c
*/

t_render_object	*create_render_object(char *name, t_mesh *mesh,
	bool has_custom_material, t_material *custom_material);
void			destroy_render_object(t_render_object **render_object);

void			enable_depthbuffer(bool enable);

void			destroy_texture(t_texture **texture);
t_texture		*create_texture(const char *name, SDL_Surface *surface,
	const t_u64 id);
bool			remove_material_from_texture(t_texture *texture,
	t_material *material);
bool			add_material_to_texture(t_texture *texture,
	t_material *material);

t_vec3f			matrix_vector_forward(t_matrix4 *matrix);
t_vec3f			matrix_vector_up(t_matrix4 *matrix);
t_vec3f			matrix_vector_left(t_matrix4 *matrix);
t_vec3f			camera_forward(t_camera *camera);
t_vec3f			camera_left(t_camera *camera);
t_vec3f			camera_up(t_camera *camera);

#endif
