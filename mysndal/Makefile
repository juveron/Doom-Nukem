# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thboura <thboura@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/05 16:22:48 by kuibout           #+#    #+#              #
#    Updated: 2020/04/30 19:03:04 by thboura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libmysndal.a

ifdef COUNT
T := $(shell $(MAKE) $(NAME) --no-print-directory \
-nrR PROGRESS="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
PROGRESS = `expr $C '*' 100 / $T`%
endif

OS = $(shell uname)

# directories

SRC_DIR = srcs/
OBJ_DIR = objs/
HDR_DIR = includes/

# libft

LFT_DIR = ../libft/
LFT = $(LFT_DIR)libft.a
LFT_HDRS = $(LFT_DIR)hdrs/
LFT_HDRS_FLAG = -I $(LFT_HDRS)
LFT_FLG = -L $(LFT_DIR) -lft

# brew directories

BREW_MAIN_DIR = $(shell brew --prefix)
BREW_LIB_DIR = $(BREW_MAIN_DIR)/lib/
BREW_HDR_DIR = $(BREW_MAIN_DIR)/include/

# libsndfile

SNDFILE_BREW_HDRS =	-I $(BREW_HDR_DIR)
SNDFILE_BREW_FLAGS =	-L $(BREW_LIB_DIR)		\
						$(SNDFILE_LIB_FLAGS)
SNDFILE_LIB_FLAGS =	-lsndfile

# openal (soft)

OPENAL_BREW_MAIN_DIR = $(BREW_MAIN_DIR)/opt/openal-soft/
OPENAL_BREW_HDR_DIR = $(OPENAL_BREW_MAIN_DIR)include/
OPENAL_BREW_LIB_DIR = $(OPENAL_BREW_MAIN_DIR)lib/
OPENAL_BREW_HDRS =	-I $(OPENAL_BREW_HDR_DIR)
OPENAL_BREW_FLAGS =	-L $(OPENAL_BREW_LIB_DIR)	\
					$(OPENAL_LIB_FLAGS)
OPENAL_LIB_FLAGS =	-lopenal

# librairies

ifeq ($(OS), Linux)
	LIB_FLG = $(LFT_FLG) $(SNDFILE_LIB_FLAGS) $(OPENAL_LIB_FLAGS)
	LIB_HDRS = $(LFT_HDRS_FLAG)
else
	LIB_FLG = $(LFT_FLG) $(SNDFILE_BREW_FLAGS) $(OPENAL_BREW_FLAGS)
	LIB_HDRS = $(LFT_HDRS_FLAG) $(SNDFILE_BREW_HDRS) $(OPENAL_BREW_HDRS)
endif

# sources

SRCS =	buffer.c				\
		change_sound.c			\
		context.c				\
		device.c				\
		error.c					\
		listener.c				\
		load_sound.c			\
		master.c				\
		sound_player.c			\
		source_basics_float.c	\
		source_basics_int.c		\
		source_basics_vec3f.c	\
		source_state.c			\
		source.c				\
		state.c

# headers

HDRS =	mysndal.h

# final files

OBJDIRS :=	$(OBJ_DIR)
OBJS :=	$(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
SRCS :=	$(addprefix $(SRC_DIR),$(SRCS))
HDRS :=	$(addprefix $(HDR_DIR),$(HDRS))
FULL_HDRS :=	-I $(HDR_DIR)	\
				$(LIB_HDRS)

# display

HIDE_CURSOR := \e[?25l
SHOW_CURSOR := \e[?25h
CURSOR_LEFT := \e[1000D
ERASE_ENDLINE := \e[K
ERASE_FULLLINE := \e[2K

# global rules (compiler / shell)

CC = clang
RAN = ar rcs
RM = /bin/rm -rf
PRINT = printf
MAIN = test.c
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
	@sudo apt-get install -y libopenal-dev libalut-dev libsndfile-dev

brew_dependencies: brew_prebuild brew_postbuild

brew_prebuild:
	@$(info > Starting brew dependencies download. Wait for all objects to install...)

brew_postbuild: brew_build
	@$(info > All brew build rules are terminated.)

brew_build:
	@brew install openal-soft
	@brew link openal-soft
	@brew install libsndfile
	@brew link libsndfile

premake: $(OBJDIRS)
	@$(MAKE) -s $(NAME) --no-print-directory COUNT=1 OPTI=$(OPTI) FS=$(FS) DEBUG=$(DEBUG)

$(NAME): $(OBJS) $(HDRS) $(LFT)
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Compilation $(NAME)" "..."
	@$(RAN) $(NAME) $(OBJS)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(SHOW_CURSOR)\n" "$(NAME)" "Compilation $(NAME)" "OK"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS) $(LFT)
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Compilation" "$(PROGRESS)"
	@$(CC) $(CFLAGS) -c $(FULL_HDRS) -o $@ $<

$(OBJDIRS):
	@mkdir -p $@

clean:
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Cleaning objects" "..."
	@$(RM) $(OBJDIRS)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(SHOW_CURSOR)\n" "$(NAME)" "Cleaning objects" "OK"

fclean: clean
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "$(NAME)" "Cleaning $(NAME)" "..."
	@$(RM) $(NAME)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[%s]\033[0m$(SHOW_CURSOR)\n" "$(NAME)" "Cleaning $(NAME)" "OK"

re: fclean all

show_cursor:
	@$(MAKE) -s -C $(LFT_DIR) show_cursor

.PHONY: all clean fclean re test show_cursor brew_dependencies brew_prebuild brew_postbuild brew_build dependencies apt_dependencies apt_prebuild apt_postbuild apt_build premake
