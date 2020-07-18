NAME := doom-nukem

ifdef COUNT
T := $(shell $(MAKE) $(NAME) --no-print-directory -nrR PROGRESS="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
PROGRESS = [`expr $C '*' 100 / $T`%%]
endif

PWD = $(shell pwd)
OS = $(shell uname)

# directories

SRC_DIR = srcs/
OBJ_DIR = objs/
HDR_DIR = includes/

# libft

LFT_DIR = libft/
LFT = $(LFT_DIR)libft.a
LFT_HDRS = $(LFT_DIR)hdrs/
LFT_HDRS_FLAG = -I $(LFT_HDRS)
LFT_FLG = -L$(LFT_DIR) -lft

# libmySDL2

MY_SDL_DIR = mysdl2/
MY_SDL = $(MY_SDL_DIR)libmySDL2.a
MY_SDL_HDRS = $(MY_SDL_DIR)include/
MY_SDL_HDRS_FLAG = -I $(MY_SDL_HDRS)
MY_SDL_FLG = -L$(MY_SDL_DIR) -lmySDL2

# libmysndal

MY_SNDAL_DIR = mysndal/
MY_SNDAL = $(MY_SNDAL_DIR)libmysndal.a
MY_SNDAL_HDRS = $(MY_SNDAL_DIR)includes/
MY_SNDAL_HDRS_FLAG = -I $(MY_SNDAL_HDRS)
MY_SNDAL_FLG = -L $(MY_SNDAL_DIR) -lmysndal

# sdl2 framework

SDL2_MAIN_DIR = ~/Library/Frameworks/
SDL2_HDR = $(SDL2_MAIN_DIR)SDL2.framework/Headers
SDL2_FLG =	-framework SDL2			\
			-framework SDL2_ttf
SDL2_FRAM_HDRS =	-I $(SDL2_HDR)
SDL2_FRAM_FLAGS =	-F $(SDL2_MAIN_DIR) $(SDL2_FLG)
SDL2_FRAM_PATH = -rpath $(SDL2_MAIN_DIR)

# sdl2 homebrew

BREW_MAIN_DIR = $(shell brew --prefix)
BREW_LIB_DIR = $(BREW_MAIN_DIR)/lib/
BREW_HDR_DIR = $(BREW_MAIN_DIR)/include/
SDL2_BREW_HDRS_FLAG =	-I $(BREW_HDR_DIR)
SDL2_BREW_FLAGS =	-L $(BREW_LIB_DIR)	\
					$(SDL2_LIB_FLAGS)
SDL2_LIB_FLAGS =	-lSDL2		\
					-lSDL2_ttf

OPENAL_BREW_DIR = $(BREW_MAIN_DIR)/opt/openal-soft/
OPENAL_BREW_HDRS_FLAG = -I $(OPENAL_BREW_DIR)include/
MY_SNDAL_BREW_FLAGS =	-L $(OPENAL_BREW_DIR)lib/ -lopenal	\
						-L $(BREW_LIB_DIR) -lsndfile
MY_SNDAL_LIB_FLAGS =	-lopenal	\
						-lsndfile

# Librairies

ifeq ($(OS), Linux)
	LIB_FLG = -Wl,-\( $(LFT_FLG) $(MY_SDL_FLG) $(SDL2_LIB_FLAGS) $(MY_SNDAL_FLG) $(MY_SNDAL_LIB_FLAGS) -lm -lpthread -Wl,-\)
	LIB_HDRS = $(LFT_HDRS_FLAG) $(MY_SDL_HDRS_FLAG) $(MY_SNDAL_HDRS_FLAG)
else
	LIB_FLG = $(LFT_FLG) $(MY_SDL_FLG) $(SDL2_BREW_FLAGS) $(MY_SNDAL_FLG) $(MY_SNDAL_BREW_FLAGS) -lm
	LIB_HDRS = $(LFT_HDRS_FLAG) $(MY_SDL_HDRS_FLAG) $(SDL2_BREW_HDRS_FLAG) $(MY_SNDAL_HDRS_FLAG) $(OPENAL_BREW_HDRS_FLAG)
endif

# Sources

SRCDIR_COLLIDER =	colider/

SRCS_COLIDER =	capsule_collider.c	\
				check_triangle.c	\
				project_point.c

SRCDIR_EVENTS =	events/

SRCS_EVENTS =	add_level_point.c		\
				add_pickup_object.c		\
				add_point.c				\
				add_sector_p2.c			\
				add_sector.c			\
				cancel_sector.c			\
				clear_event.c			\
				delete_level_point.c	\
				delete_pickup_object.c	\
				delete_point_utils.c	\
				delete_point.c			\
				delete_sector_p2.c		\
				delete_sector_p3.c		\
				delete_sector.c			\
				display_events.c		\
				editor_event_init.c		\
				free_all_event.c		\
				history_p3.c			\
				history_p2.c			\
				history.c				\
				insert_point.c			\
				move_level_point.c		\
				move_point.c			\
				record_event.c			\
				redo_point.c

SRCDIR_GAME_OVER =	game_over/

SRCS_GAME_OVER =	game_over.c				\
					game_over_functions.c	\
					game_over_menu.c

SRCDIR_WIN =	win/

SRCS_WIN =	update_win_menu.c	\
			win_menu.c			\
			win_menu_function.c	\
			win_state.c

SRCDIR_LEVELS =	levels/

SRCS_LEVELS =	draw_level.c			\
				level_point_utils.c		\
				level_point.c			\
				level_update.c			\
				levels_checks.c			\
				levels_other_utils.c	\
				levels_utils.c			\
				levels.c

SRCDIR_PHYSICS =	physics/

SRCS_PHYSICS =	check_collision.c		\
				check_collision_p2.c	\
				check_collision_p3.c	\
				update_gravity.c		\
				physics_loop.c

SRCDIR_RENDER =	render/

SRCS_RENDER =	pvs_p4.c 			\
				pvs_p3.c 			\
				pvs_p2.c 			\
				pvs.c 				\
				compute_all_pvs.c

SRCDIR_SCENE =	scene/

SRCDIR_EDITOR =	editor/

SRCS_EDITOR =	add_point_tmp_p2.c		\
				add_point_tmp.c			\
				check_multi_point.c		\
				delete_point_p2.c		\
				delete_point.c			\
				delete_sector.c			\
				draw_3d_editor.c		\
				draw_3d_editor_p2.c		\
				draw_3d_sector_floor.c	\
				draw_editor.c			\
				draw_grid.c				\
				draw_new_sector.c		\
				draw_sector_highlight.c	\
				draw_sector.c			\
				editor_scene.c			\
				free_point.c			\
				get_closest_wall.c		\
				insert_point.c			\
				sector_point.c			\
				select_3d_p2.c			\
				select_3d_p3.c			\
				select_3d.c				\
				show_pvs.c				\
				snap_point.c			\
				update_editor.c			\
				update_height.c			\
				utils_p2.c				\
				utils.c					\
				zoom.c

SRCDIR_GAME =	game/

SRCS_GAME = draw_game.c		\
			game_scene.c	\
			game_struct.c	\
			update_game.c

SRCDIR_MAIN_MENU =	main_menu/

SRCS_MAIN_MENU =	gui_main_menu_p3.c	\
					gui_main_menu_p2.c	\
					gui_main_menu.c		\
					main_menu_scene.c

SRCS_SCENE =	$(addprefix $(SRCDIR_EDITOR), $(SRCS_EDITOR))		\
				$(addprefix $(SRCDIR_GAME), $(SRCS_GAME))			\
				$(addprefix $(SRCDIR_MAIN_MENU), $(SRCS_MAIN_MENU))	\
				scene_manager_p2.c									\
				scene_manager.c

SRCDIR_SETTINGS =	settings/

SRCDIR_SETTINGS_OPTIONS =	options/

SRCS_SETTINGS_OPTIONS =	audio_options_p2.c		\
						audio_options_p3.c		\
						audio_options_p4.c		\
						audio_options_p5.c		\
						audio_options_p6.c		\
						audio_options_p7.c		\
						audio_options.c			\
						controls_options_p2.c	\
						controls_options_p3.c	\
						controls_options_p4.c	\
						controls_options_p5.c	\
						controls_options_p6.c	\
						controls_options.c		\
						other_options_p2.c		\
						other_options_p3.c		\
						other_options.c

SRCS_SETTINGS =	$(addprefix $(SRCDIR_SETTINGS_OPTIONS), $(SRCS_SETTINGS_OPTIONS))	\
				settings_menu_functions.c											\
				settings_menu_p2.c													\
				settings_menu.c

SRCDIR_SOUNDS =	sounds/

SRCS_SOUNDS =	ambient.c				\
				audio.c					\
				class_functions_p2.c	\
				class_functions.c		\
				gui.c					\
				objects.c				\
				sound_manager.c

SRCDIR_UPDATE_INPUT =	update_input/

SRCDIR_EDITOR_INPUTS =	editor_inputs/

SRCS_EDITOR_INPUTS =	basic_inputs.c			\
						button_left_input_p2.c	\
						button_left_input.c		\
						button_right_input.c	\
						change_mode_inputs.c	\
						delete_inputs.c			\
						display_gui_input.c		\
						drag_input.c			\
						game_input.c			\
						global_editor_inputs.c	\
						history_input.c			\
						insert_input.c			\
						manage_inputs.c			\
						pause_editor_inputs.c	\
						quit_input.c			\
						rotation_input.c		\
						save_input.c

SRCDIR_GAME_INPUTS =	game_inputs/

SRCS_GAME_INPUTS =	global_game_inputs.c	\
					hud_input.c				\
					pause_game_inputs.c		\
					player_inputs.c			\
					rotation_inputs.c

SRCDIR_GAME_OVER_INPUTS =	game_over_inputs/

SRCS_GAME_OVER_INPUTS =	game_over_inputs.c

SRCDIR_MAIN_MENU_INPUTS =	main_menu_inputs/

SRCS_MAIN_MENU_INPUTS =	global_main_menu_inputs.c

SRCDIR_SETTINGS_INPUTS =	settings_inputs/

SRCS_SETTINGS_INPUTS =	global_settings_inputs.c

SRCS_UPDATE_INPUT =	$(addprefix $(SRCDIR_EDITOR_INPUTS), $(SRCS_EDITOR_INPUTS))			\
					$(addprefix $(SRCDIR_GAME_INPUTS), $(SRCS_GAME_INPUTS))				\
					$(addprefix $(SRCDIR_GAME_OVER_INPUTS), $(SRCS_GAME_OVER_INPUTS))	\
					$(addprefix $(SRCDIR_MAIN_MENU_INPUTS), $(SRCS_MAIN_MENU_INPUTS))	\
					$(addprefix $(SRCDIR_SETTINGS_INPUTS), $(SRCS_SETTINGS_INPUTS))		\
					update_input.c

SRCS =	$(addprefix $(SRCDIR_COLLIDER), $(SRCS_COLIDER))			\
		$(addprefix $(SRCDIR_EVENTS), $(SRCS_EVENTS))				\
		$(addprefix $(SRCDIR_GAME_OVER), $(SRCS_GAME_OVER))			\
		$(addprefix $(SRCDIR_WIN), $(SRCS_WIN))						\
		$(addprefix $(SRCDIR_LEVELS), $(SRCS_LEVELS))				\
		$(addprefix $(SRCDIR_PHYSICS), $(SRCS_PHYSICS))				\
		$(addprefix $(SRCDIR_RENDER), $(SRCS_RENDER))				\
		$(addprefix $(SRCDIR_SCENE), $(SRCS_SCENE))					\
		$(addprefix $(SRCDIR_SETTINGS), $(SRCS_SETTINGS))			\
		$(addprefix $(SRCDIR_SOUNDS), $(SRCS_SOUNDS))				\
		$(addprefix $(SRCDIR_UPDATE_INPUT), $(SRCS_UPDATE_INPUT))	\
		aabb.c														\
		app_p2.c													\
		app_p3.c													\
		app_p4.c													\
		app_p5.c													\
		app.c														\
		check_valid_map.c											\
		clockwise_dir.c												\
		compute_triangulation.c										\
		compute_triangulation_p2.c									\
		convert_sector_p2.c											\
		convert_sector_p3.c											\
		convert_sector.c											\
		drag_point.c												\
		editor_game_state.c											\
		env.c														\
		env3d.c														\
		error.c														\
		export_p2.c													\
		export_p3.c													\
		export.c													\
		file_name.c													\
		flip_wall.c													\
		fonts.c														\
		free_all_scene.c											\
		game_pause_menu.c											\
		game_pause_menu_functions.c									\
		game_pause_menu_p2.c										\
		game_pause_menu_p3.c										\
		get_random_color.c											\
		global_mesh.c												\
		image_gui.c													\
		import_p2.c													\
		import_p3.c													\
		import_p4.c													\
		import_p5.c													\
		import.c													\
		init_texture_selection_p2.c									\
		init_texture_selection_p3.c									\
		init_texture_selection.c									\
		input_button.c												\
		input_button_p2.c											\
		inside.c													\
		levels_menu_p2.c											\
		levels_menu_p3.c											\
		levels_menu_p4.c											\
		levels_menu_p5.c											\
		levels_menu_p6.c											\
		levels_menu_p7.c											\
		levels_menu.c												\
		levels_selection_p2.c										\
		levels_selection.c											\
		main.c														\
		map_p2.c													\
		map.c														\
		material_preview_p2.c										\
		material_preview.c											\
		neighbor.c													\
		notify.c													\
		objects_manager.c											\
		pause_menu_functions.c										\
		pause_menu_internal.c										\
		pause_menu_p2.c												\
		pause_menu.c												\
		pickup_object.c												\
		pickup_object_utils.c										\
		point.c														\
		print_debug.c												\
		print_hud.c													\
		print_hud_p2.c												\
		recorded_insert_point.c										\
		recorded_insert_point_p2.c									\
		remaining_objects.c											\
		remap_point_id.c											\
		sector.c													\
		sector_internal.c											\
		sector_menu.c												\
		sector_menu_internal.c										\
		sector_menu_internal_p2.c									\
		sector_p2.c													\
		sector2.c													\
		select.c													\
		shortcut_input.c											\
		shortcuts.c													\
		shortcuts_p2.c												\
		shortcuts_p3.c												\
		teleport.c													\
		texture_menu_p2.c											\
		texture_menu_p3.c											\
		texture_menu_p4.c											\
		texture_menu_p5.c											\
		texture_menu.c												\
		texture_selection_p2.c										\
		texture_selection_p3.c										\
		texture_selection_p4.c										\
		texture_selection.c											\
		triangulate_polygon.c										\
		triangulation_internal_p2.c									\
		triangulation_internal_p3.c									\
		triangulation_internal.c									\
		user_inputs.c												\
		wall_menu.c													\
		wall.c

# Headers

HDRS =	collider.h						\
		collision_internal.h			\
		delete_sector_internal.h		\
		doom_nukem.h					\
		draw_editor_internal.h			\
		editor.h						\
		export_internal.h				\
		game.h							\
		game_over_internal.h			\
		gui_main_menu_internal.h		\
		history_internal.h				\
		import_internal.h				\
		inputs.h						\
		internal_handler.h				\
		levels_menu_internal.h			\
		levels_selection_internal.h		\
		material_preview_internal.h		\
		pause_menu_internal.h			\
		physics.h						\
		pvs_internal.h					\
		render.h						\
		scene_manager.h					\
		sector_internal.h				\
		sector_menu_internal.h			\
		select_3d_internal.h			\
		texture_menu_internal.h			\
		texture_selection_internal.h	\
		triangulation_internal.h

# Final files

OBJDIRS :=	$(OBJ_DIR)													\
			$(OBJ_DIR)$(SRCDIR_COLLIDER)								\
			$(OBJ_DIR)$(SRCDIR_EVENTS)									\
			$(OBJ_DIR)$(SRCDIR_GAME_OVER)								\
			$(OBJ_DIR)$(SRCDIR_WIN)										\
			$(OBJ_DIR)$(SRCDIR_LEVELS)									\
			$(OBJ_DIR)$(SRCDIR_PHYSICS)									\
			$(OBJ_DIR)$(SRCDIR_RENDER)									\
			$(OBJ_DIR)$(SRCDIR_SCENE)									\
			$(OBJ_DIR)$(SRCDIR_SCENE)$(SRCDIR_EDITOR)					\
			$(OBJ_DIR)$(SRCDIR_SCENE)$(SRCDIR_GAME)						\
			$(OBJ_DIR)$(SRCDIR_SCENE)$(SRCDIR_MAIN_MENU)				\
			$(OBJ_DIR)$(SRCDIR_SETTINGS)								\
			$(OBJ_DIR)$(SRCDIR_SETTINGS)$(SRCDIR_SETTINGS_OPTIONS)		\
			$(OBJ_DIR)$(SRCDIR_SOUNDS)									\
			$(OBJ_DIR)$(SRCDIR_UPDATE_INPUT)							\
			$(OBJ_DIR)$(SRCDIR_UPDATE_INPUT)$(SRCDIR_EDITOR_INPUTS)		\
			$(OBJ_DIR)$(SRCDIR_UPDATE_INPUT)$(SRCDIR_GAME_INPUTS)		\
			$(OBJ_DIR)$(SRCDIR_UPDATE_INPUT)$(SRCDIR_GAME_OVER_INPUTS)	\
			$(OBJ_DIR)$(SRCDIR_UPDATE_INPUT)$(SRCDIR_MAIN_MENU_INPUTS)	\
			$(OBJ_DIR)$(SRCDIR_UPDATE_INPUT)$(SRCDIR_SETTINGS_INPUTS)

OBJS :=	$(addprefix $(OBJ_DIR),$(SRCS:.c=.o))

SRCS :=	$(addprefix $(SRC_DIR),$(SRCS))

HDRS :=	$(addprefix $(HDR_DIR),$(HDRS))

FULL_HDRS :=	-I $(HDR_DIR)	\
				$(LIB_HDRS)

# Display

HIDE_CURSOR := \e[?25l
SHOW_CURSOR := \e[?25h
CURSOR_LEFT := \e[1000D
ERASE_ENDLINE := \e[K
ERASE_FULLLINE := \e[2K

# Global variable (compiler / shell)

CC = clang
RAN = ar rcs
RM = /bin/rm -rf
PRINT = printf
CFLAGS = -Wall -Wextra -Werror

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

# Rules

all: premake

premake: $(OBJDIRS) libmake_other
	@$(MAKE) -s $(NAME) --no-print-directory COUNT=1 OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG)

libmake_libft:
	@cd $(LFT_DIR) && $(MAKE) -s OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG)

libmake_other: libmake_libft
	@cd $(MY_SDL_DIR) && $(MAKE) -s OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG) PACKAGE_INSTALL=$(PACKAGE_INSTALL)
	@cd $(MY_SNDAL_DIR) && $(MAKE) -s OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG) PACKAGE_INSTALL=$(PACKAGE_INSTALL)

libclean:
	@cd $(LFT_DIR) && $(MAKE) -s clean
	@cd $(MY_SDL_DIR) && $(MAKE) -s clean
	@cd $(MY_SNDAL_DIR) && $(MAKE) -s clean

libfclean:
	@cd $(LFT_DIR) && $(MAKE) -s fclean
	@cd $(MY_SDL_DIR) && $(MAKE) -s fclean
	@cd $(MY_SNDAL_DIR) && $(MAKE) -s fclean

$(OBJDIRS):
	@mkdir -p $@

$(NAME): $(OBJS) $(HDRS) $(LFT) $(MY_SDL) $(MY_SNDAL)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_FLG)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n$(SHOW_CURSOR)" "$(NAME)" "Compilation $@"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS) $(LFT) $(MY_SDL) $(MY_SNDAL)
	@$(CC) $(CFLAGS) -c $(FULL_HDRS) -o $@ $<
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m$(PROGRESS)\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Compilation"

clean: libclean
	@@$(RM) $(OBJDIRS)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning objs"

clean2:
	@$(RM) $(OBJDIRS)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning objs"

fclean: clean2 libfclean
	@$(RM) $(NAME)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "$(NAME)" "Cleaning $(NAME)"

re: fclean all

show_cursor:
	@printf "\033[38;2;0;255;0mThe cursor just came back ...\033[0m$(SHOW_CURSOR)\n"

.PHONY: all clean clean2 fclean re libmake libclean libfclean sdl2_brew sdl2_prebuild sdl2_postbuild sdl2_build debug show_cursor test
