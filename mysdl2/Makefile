# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thboura <thboura@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/22 11:38:41 by kguibout          #+#    #+#              #
#    Updated: 2020/07/14 16:14:45 by thboura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_PATH = ../libft

####################### DO NOT MODIFY AFTER THIS COMMENT #######################

NAME = libmySDL2.a

ifdef COUNT
T := $(shell $(MAKE) $(NAME) --no-print-directory \
      -nrR \
      PROGRESS="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
PROGRESS = [`expr $C '*' 100 / $T`%%]
endif

CC = clang
CFLAGS = -Wall -Werror -Wextra

# Flags

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(FS), 1)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

ifneq ($(OPTI), 0)
	CFLAGS += -O3
endif

PWD = $(shell pwd)
OS = $(shell uname)

RM = /bin/rm -rf
PRINT = printf

# libft

LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_HDRS = $(LIBFT_PATH)/hdrs/

# sdl2 homebrew

BREW_LIB_DIR = $(BREW_PREFIX)/lib/
BREW_HDR_DIR = $(BREW_PREFIX)/include/
SDL2_BREW_HDRS =	-I $(BREW_HDR_DIR)

INCLUDEDIR = include/

INCLUDE_FILE =	bmp.h						\
				clipping_internal.h			\
				color.h						\
				container.h					\
				context.h					\
				draw.h						\
				draw3d.h					\
				elipse.h					\
				event.h						\
				event_handle.h				\
				event_p2.h					\
				free_all.h					\
				gui.h						\
				gui_button.h				\
				gui_trigger.h				\
				handle_state.h				\
				input.h						\
				line.h						\
				matrix_invert_internal.h	\
				mysdl2.h					\
				open_obj_internal.h			\
				pixel.h						\
				rasterizer.h				\
				text.h						\
				textfield_internal.h		\
				tga.h						\
				window.h

INCLUDE_FILE := $(addprefix $(INCLUDEDIR), $(INCLUDE_FILE))

ifeq ($(OS), Linux)
	INCLUDE =	-I $(INCLUDEDIR) \
				-I $(LIBFT_HDRS)
else
	BREW_PREFIX := $(shell brew --prefix)
	INCLUDE =	-I $(INCLUDEDIR)			\
				-I $(LIBFT_HDRS)			\
				$(SDL2_BREW_HDRS)
endif

SRCDIR = src/

SRCDIR_3D = 3D/

SRCDIR_MATRIX =	matrix/

SRCDIR_MATERIAL =	material/

SRCDIR_GUI = gui/

SRCDIR_RASTERIZER = rasterizer/

SRCDIR_TGA = tga/

SRCS_MATRIX =	matrix_identity.c			\
				matrix_invert_internal.c	\
				matrix_invert.c				\
				matrix_multiply.c			\
				matrix_perspective.c		\
				matrix_rotation.c			\
				matrix_scale.c				\
				matrix_translation.c		\
				matrix_vector_direction.c	\
				mul_matrix4_vec3f.c			\
				mul_matrix4_vec4f.c

SRCS_MATERIAL =	material.c		\
				mtl_diffuse.c

SRCS_RASTERIZER =	draw_triangle.c	\
					fragment.c		\
					set_color.c

SRCS_3D =	$(addprefix $(SRCDIR_MATRIX), $(SRCS_MATRIX))			\
			$(addprefix $(SRCDIR_MATERIAL), $(SRCS_MATERIAL))		\
			$(addprefix $(SRCDIR_RASTERIZER), $(SRCS_RASTERIZER))	\
			build_tile_array.c										\
			camera.c												\
			camera_direction.c										\
			clip_screen.c											\
			clip_triangle.c											\
			clipping.c												\
			clipping_p2.c											\
			depth_buffer.c											\
			edge.c													\
			env3d.c													\
			mesh.c													\
			mesh_p2.c												\
			open_obj_file.c											\
			open_obj_file_p2.c										\
			open_obj_file_p3.c										\
			render_object.c											\
			texture.c												\
			tile_p2.c												\
			tile.c													\
			transform.c												\
			vertex.c												\
			worker_p2.c												\
			worker.c

SRCS_GUI =	button_p2.c			\
			button.c			\
			check_box.c			\
			component.c			\
			container_p2.c		\
			container_p3.c		\
			container.c			\
			component_p2.c		\
			component.c			\
			custom_window_p2.c	\
			custom_window.c		\
			draw_gui.c			\
			fslider_p2.c		\
			fslider.c			\
			label_p2.c			\
			label.c				\
			main_container.c	\
			textfield_p2.c		\
			textfield_p3.c		\
			textfield.c			\
			update_gui.c

SRCS_TGA =	tga.c		\
			tga_p2.c	\
			tga_p3.c	\
			tga_p4.c

SRCS =	$(addprefix $(SRCDIR_3D), $(SRCS_3D))	\
		$(addprefix $(SRCDIR_GUI), $(SRCS_GUI))	\
		$(addprefix $(SRCDIR_TGA), $(SRCS_TGA))	\
		background.c							\
		blit_surface.c							\
		context.c								\
		custom_event_handle.c					\
		draw_elipse.c							\
		draw_line_clip.c						\
		draw_line.c								\
		draw_rectangle.c						\
		drop.c									\
		error.c									\
		event_handler_p2.c						\
		event_handle.c							\
		event_p2.c								\
		event.c									\
		fps_counter.c							\
		free_all.c								\
		handle_state_p2.c						\
		handle_state.c							\
		input_p2.c								\
		input_p3.c								\
		input.c									\
		pixel.c									\
		rect.c									\
		save_bmp.c								\
		text.c									\
		window_p2.c								\
		window.c

OBJDIR =	obj/

OBJDIRS =	$(OBJDIR)									\
			$(OBJDIR)$(SRCDIR_3D)						\
			$(OBJDIR)$(SRCDIR_3D)$(SRCDIR_MATRIX)		\
			$(OBJDIR)$(SRCDIR_3D)$(SRCDIR_MATERIAL)		\
			$(OBJDIR)$(SRCDIR_3D)$(SRCDIR_RASTERIZER)	\
			$(OBJDIR)$(SRCDIR_GUI)						\
			$(OBJDIR)$(SRCDIR_TGA)

OBJS := $(addprefix $(OBJDIR), $(SRCS:.c=.o))

# display

HIDE_CURSOR := \e[?25l
SHOW_CURSOR := \e[?25h
CURSOR_LEFT := \e[1000D
ERASE_ENDLINE := \e[K
ERASE_FULLLINE := \e[2K

all: dependencies premake

ifdef PACKAGE_INSTALL
ifeq ($(OS), Linux)
dependencies: apt_dependencies
else
dependencies: brew_dependencies
endif
else
dependencies:
endif

apt_dependencies: apt_prebuild apt_postbuild

apt_prebuild:
	@$(info > Starting apt dependencies download. Wait for all objects to install...)

apt_postbuild: apt_build
	@$(info > All apt build rules are terminated.)

apt_build:
	@sudo apt install -y libsdl2-dev libsdl2-ttf-dev

brew_dependencies: brew_prebuild brew_postbuild

brew_prebuild:
	@$(info > Starting brew dependencies download. Wait for all objects to install...)

brew_postbuild: brew_build
	@$(info > All brew build rules are terminated.)

brew_build:
	@brew install sdl2 || brew upgrade sdl2
	@brew install sdl2_ttf || brew upgrade sdl2_ttf

premake: $(OBJDIRS)
	@$(MAKE) -s $(NAME) --no-print-directory COUNT=1 OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG)

$(OBJDIRS):
	@mkdir -p $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n$(SHOW_CURSOR)" "$(NAME)" "Compilation $@"

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCLUDE_FILE) $(LIBFT)
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m$(PROGRESS)\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Compilation"

clean clean_analyze:
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning objs"
	@$(RM) $(OBJDIR)

fclean fclean_analyze: clean
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning $(NAME)"
	@$(RM) $(NAME)

re: fclean all

show_cursor:
	@$(MAKE) -s -C $(LFT_DIR) show_cursor

.PHONY: re clean fclean all analyze clean_analyze fclean_analyze show_cursor brew_dependencies brew_prebuild brew_postbuild brew_build dependencies apt_dependencies apt_prebuild apt_postbuild apt_build premake
