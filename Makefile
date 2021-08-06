# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 17:53:03 by jsankari          #+#    #+#              #
#    Updated: 2021/05/25 16:14:21 by esormune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_FILES = w3d_main.c \
w3d_errors.c \
w3d_draw.c \
w3d_maps.c \
w3d_lines.c \
w3d_key_events.c \
w3d_create_image.c \
w3d_check_horizontal.c \
w3d_check_vertical.c \
w3d_textures.c \
w3d_texture_parse.c \
w3d_validate.c \
w3d_walls.c \
w3d_player.c

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC_DIR = ./srcs/
INC_DIR = ./includes/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(BUILD_DIR), $(OBJ_FILES))

LIBFT = libft/libft.a

GFLAGS = -Wall -Wextra -Werror -g

INCLUDE = -I ./libsdl/include/ -I $(INC_DIR)

SDL_CFLAGS = `$(BUILD_DIR)/libsdl/bin/sdl2-config --cflags`

SDL_LDFLAGS = `$(BUILD_DIR)/libsdl/bin/sdl2-config --libs`

SDL = $(BUILD_DIR)/libsdl/lib/libSDL2.a

BUILD_DIR = build/

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc $(GFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(SDL_LDFLAGS) $(INCLUDE)
	@echo "[ Wolf3d executable compiled ]"

$(OBJ) : $(SRC) $(SDL) | $(BUILD_DIR) $(LIBFT)
	@gcc $(GFLAGS) $(INCLUDE) -c $(SRC) $(SDL_CFLAGS)
	@mv	$(OBJ_FILES) $(BUILD_DIR)
$(LIBFT) :
	@$(MAKE) -C libft
	@echo "[ Libft compiled ]"

$(BUILD_DIR) :
	@mkdir $(BUILD_DIR)

$(SDL) : | $(BUILD_DIR)
	cd libsdl && ./configure --prefix=$(abspath $(BUILD_DIR)libsdl)
	$(MAKE) -C libsdl --jobs=24
	$(MAKE) -C libsdl install

clean :
	@$(MAKE) clean -C libft
	@rm -f $(OBJ)
	@if test -f libsdl/Makefile; then $(MAKE) AUTOMAKE=: -C libsdl clean; fi
	@echo "[ Wolf3d objects deleted ]"

fclean : clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)
	@if test -f libsdl/Makefile; then $(MAKE) AUTOMAKE=: -C libsdl distclean; fi
	@rm -rf $(BUILD_DIR)
	@echo [ Wolf3d executable deleted ]

re : fclean all
	@$(MAKE) re -C libft

.PHONY = all clean fclean re
