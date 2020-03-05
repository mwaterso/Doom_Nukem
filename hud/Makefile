# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: calin <calin@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/12/11 16:17:05 by calin        #+#   ##    ##    #+#        #
#    Updated: 2020/02/03 19:58:00 by calin       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = doom-nukem

SRCS = hud/main.c\
		hud/hud.c\
		hud/timer.c\
		hud/init_function.c\
		hud/health_bar.c\
		hud/display_hud.c\
		hud/display_weapon.c\
		hud/event.c\
		hud/check_event.c\

OBJ = $(SRCS:%.c=%.o)

INC = doom.h

FLAGS =  -Wall -Wextra -Werror

LIBFT = libft/libft.a

LIBMLX = minilibx_macos/libmlx.a

OPENGL = -framework OpenGL -framework AppKit

all: lib $(NAME)

$(NAME): $(LIBMLX) $(OBJ)
		gcc $(FLAGS) $(LIBMLX) $(OBJ) $(OPENGL) -o $(NAME) -g $(LIBFT)

%.o: %.c $(INC)
		gcc $(FLAGS) -c $< -o $@

lib:
		make -C libft/

$(LIBMLX):
		make -C minilibx_macos/

clean:
		make clean -C libft/
		make clean -C minilibx_macos/
		rm -rf $(OBJ)

fclean: clean
		make fclean -C libft/
		rm -rf $(NAME)

re: fclean all
		make re -C minilibx_macos/