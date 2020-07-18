/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysndal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:27:13 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:29:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSNDAL_H
# define MYSNDAL_H

# include <AL/al.h>
# include <AL/alc.h>
# include <sndfile.h>
# include "libft.h"

typedef enum		e_source_state
{
	SRC_REWIND,
	SRC_PLAY,
	SRC_PAUSE,
	SRC_STOP
}					t_source_state;

typedef struct		s_sound_file
{
	ALsizei	nb_samples;
	ALshort	*samples;
	ALenum	format;
	ALsizei	sample_rate;
	ALsizei	channels;
	ALsizei	frames;
}					t_sound_file;

typedef struct		s_sound_player
{
	t_map	*sounds_list;
	size_t	unique_id;
}					t_sound_player;

typedef struct		s_default_master
{
	ALCdevice			*device;
	ALCcontext			*context;
	t_sound_player		*library;
}					t_default_master;

/*
**	buffer
*/

bool				add_sound_to_buffer(ALuint *buffer, t_sound_file *sound);
ALuint				*init_buffers(size_t num_of_buffers);
bool				destroy_buffers(ALuint *buffers, size_t num_of_buffers,
	bool need_free);
int					get_buffer_length_in_samples(ALuint *buffer);
float				get_buffer_duration_in_seconds(ALuint *buffer);

/*
**	context
*/

ALCcontext			*init_audio_context(ALCdevice *device);
bool				destroy_context(ALCcontext *context);
bool				destroy_current_context(void);

/*
**	device
*/

ALCdevice			*init_device(char *device_name);
bool				destroy_device(ALCdevice *device);
ALCdevice			*get_context_device(ALCcontext *context);
void				show_devices(void);

/*
**	error
*/

ALenum				catch_error(void);
bool				verify_error(void);

/*
**	listener
*/

bool				set_listener_position(t_vec3f position);
bool				set_listener_velocity(t_vec3f velocity);
bool				set_listener_orientation(t_vec3f forward, t_vec3f up);
bool				get_listener_vec3f(ALenum param, t_vec3f *dst);

/*
**	master
*/

bool				destroy_default_master(t_default_master *master);
t_default_master	*init_default_master(void);
size_t				add_sound_to_library(t_default_master *master,
	char *file_name, ALenum format);

/*
**	player
*/

bool				destroy_sound_player(t_sound_player *player);
t_sound_player		*init_sound_player(void);
size_t				add_buffer_to_player(t_sound_player *player,
	ALuint *buffer);
size_t				create_player_buffer(t_sound_player *player);

/*
**	sound
*/

t_sound_file		*load_sound(char *file_name);
void				delete_sound(t_sound_file *sound);

bool				change_sound_to_mono(t_sound_file *sound);
bool				change_sound_to_stereo(t_sound_file *sound);

/*
**	source
*/

bool				attach_buffer_to_source(ALuint *source, ALuint *buffer);
ALuint				*init_sources(size_t num_of_sources);
bool				destroy_sources(ALuint *sources, size_t num_of_sources,
	bool need_free);

bool				set_source_position(ALuint source, t_vec3f position);
bool				set_source_velocity(ALuint source, t_vec3f velocity);
bool				set_source_orientation(ALuint source, t_vec3f forward,
	t_vec3f up);
bool				get_source_vec3f(ALuint source, ALenum param, t_vec3f *src);

bool				set_source_beginning(ALuint source, float seconds);
bool				set_source_amplitude(ALuint source, float gain);
bool				set_source_rollof(ALuint source, float gain);
bool				set_source_ref_dist(ALuint source, float gain);
bool				set_source_max_dist(ALuint source, float gain);

bool				set_source_relative(ALuint source, int rel);
bool				set_source_loop(ALuint source, int loop);

bool				change_source_state(ALuint source, t_source_state state);
bool				change_sources_state(ALuint *sources,
	ALsizei num_of_sources, t_source_state state);

/*
**	state
*/

bool				set_distance_model(ALenum model);

#endif
